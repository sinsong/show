import sys
import requests
import html5lib
import base64
import urllib
import xml
import re
import logging

logging.basicConfig(level=logging.DEBUG, format='%(lineno)-3d [%(levelname)-7s] %(funcName)s: %(message)s', filename='html-cook.log')
logger = logging.getLogger(__name__)

formatter=logging.Formatter('%(lineno)-3d [%(levelname)-7s] %(funcName)s: %(message)s')
#handler = logging.FileHandler('html_cook.log')
#handler.setLevel(logging.DEBUG)
#handler.setFormatter(formatter)

console = logging.StreamHandler(sys.stdout)
console.setLevel(logging.DEBUG)
console.setFormatter(formatter)

#logger.addHandler(handler)
logger.addHandler(console)


def data_url_gen(base64str, mime='text/plain'):
	logger.debug('data scheme url generated')
	return r'data:' + mime + r';base64,' + base64str

def css_re_replace(match):
	logger.debug('match url -> %s' % match.group(1))
	src = urllib.parse.urlparse(match.group(1).strip(r'"'))
	if src.scheme == 'data':
		logger.debug('match data scheme url -> %s' % match.group(1).strip(r'"'))
		return r'url(' + match.group(1) + r')'
	logger.debug('HTTP GET')
	request_url = urllib.parse.urlunparse(('https', src.netloc, src.path, src.params, src.query, src.fragment))
	
	resource = requests.get(request_url)
	b64str = str(base64.b64encode(resource.content), 'utf-8')
	return r'url(' + data_url_gen(b64str, resource.headers['Content-Type']) + r')'
	
def cook_css(csstext):
	logger.debug('cook css')
	cooked_css = re.sub(r'url\((\S+)\)', css_re_replace, csstext)
	logger.debug('cooked css')
	return cooked_css

def cook_script_tag(elem):
	logger.debug('cook <script> src -> %s' % elem.attrib['src'])
	mime = 'text/javascript'
	if 'type' in elem.attrib:
		mime = elem.attrib['type']
	
	src = urllib.parse.urlparse(elem.attrib['src'])
	logger.debug('HTTP GET')
	request_url = urllib.parse.urlunparse(('https', src.netloc, src.path, src.params, src.query, src.fragment))
	
	resource = requests.get(request_url)
	b64str = str(base64.b64encode(resource.content), 'utf-8')
	
	elem.attrib['src'] = data_url_gen(b64str, mime=mime)
	logger.debug('cooked <script>')

def cook_css_tag(elem):
	logger.debug('cook css -> %s' % elem.attrib['href'])
	mime = 'text/css'
	
	src = urllib.parse.urlparse(elem.attrib['href'])
	logger.debug('HTTP GET')
	request_url = urllib.parse.urlunparse(('https', src.netloc, src.path, src.params, src.query, src.fragment))
	
	resource = requests.get(request_url)
	cooked_css = cook_css(resource.text)
	b64str = str(base64.b64encode(cooked_css.encode('utf-8')), 'utf-8')
	
	elem.attrib['href'] = data_url_gen(b64str, mime=mime)
	logger.debug('cooked css')

def cook_img_tag(elem):
	logger.debug('cook <img> src -> %s' % elem.attrib['src'])
	src = urllib.parse.urlparse(elem.attrib['src'])
	if len(src.netloc) == 0:
		logger.warning('wrong url -> %s' % elem.attrib['src'])
		logger.debug('urllib.parse.urlparse ->', src)
		return None
	logger.debug('HTTP GET')
	request_url = urllib.parse.urlunparse(('https', src.netloc, src.path, src.params, src.query, src.fragment))
	
	resource = requests.get(request_url)
	b64str = str(base64.b64encode(resource.content), 'utf-8')
	
	elem.attrib['src'] = data_url_gen(b64str, mime=resource.headers['Content-Type'])
	logger.debug('cooked <img>')

def cook_html(document):
	for elem in document.iter(tag='script'):
		if 'src' in elem.attrib:
			logger.debug('find script')
			cook_script_tag(elem)
	for elem in document.iter(tag='link'):
		if 'rel' in elem.attrib and elem.attrib['rel'] == 'stylesheet':
			logger.debug('find stylesheet')
			cook_css_tag(elem)
	for elem in document.iter(tag='img'):
		if 'src' in elem.attrib:
			logger.debug('find img')
			cook_img_tag(elem)

def main(url):
	if url == None:
		exit(0)
	
	logger.info('html_cook')
	logger.info('cook webpage -> %s' % url)
	
	logger.info('HTTP GET %s' % url)
	res = requests.get(url)
	text = res.text
	logger.info('HTTP response %d' % res.status_code)
	
	logger.info('html5lib parse')
	document = html5lib.parse(text, treebuilder='etree', namespaceHTMLElements=False)
	
	logger.info('cook_html')
	cook_html(document)
	
	logger.info('generage output')
	output = xml.etree.ElementTree.tostring(document, encoding='utf8', method='html')
	#print(str(output, 'utf-8'))
	logger.info('write output -> output.html')
	with open('output.html', 'wb') as f:
		f.write(output)
	
	logger.info('DONE')

if __name__ == '__main__':
	if len(sys.argv) > 1:
		main(sys.argv[1])
	else:
		main(None)