import requests
import threading
from time import sleep
import sys

homepage_url    = 'http://jwgl.xawl.edu.cn'
check_code_url  = 'http://jwgl.xawl.edu.cn/CheckCode.aspx'

user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win32; x32) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/64.0.3282.140'

proxies = {
'http': '183.230.177.116:8060',
'http': '117.177.243.7:80',
'http': '110.52.235.248:9999',
'http': '119.101.113.184:9999',
'http': '120.198.230.15:8080',
'http': '103.59.132.50:38590',
'http': '111.177.185.145:9999'
}

homepage_headers = {
'Accept': '*/*',
'Accept-Encoding':'deflate',
'Accept-Language': 'zh-Hans-CN, zh-Hans; q=0.8, en-US; q=0.5, en; q=0.3',
'Cache-Control': 'no-cache',
'Connection': 'Keep-Alive',
'Host': 'jwgl.xawl.edu.cn',
'User-Agent': user_agent
}

check_code_headers = {
'Accept': 'image/png, image/svg+xml, image/*; q=0.8, */*; q=0.5',
'Accept-Encoding':'deflate',
'Accept-Language': 'zh-Hans-CN, zh-Hans; q=0.8, en-US; q=0.5, en; q=0.3',
'Cache-Control': 'max-age=0',
'Connection': 'Keep-Alive',
'Host': 'jwgl.xawl.edu.cn',
'Referer': 'http://jwgl.xawl.edu.cn/',
'User-Agent': user_agent
}

def conn(num):
	s = requests.Session()
	#s.proxies = proxies
	# HTTP GET!
	homepage_res = s.get(homepage_url, headers=homepage_headers)
	print('[%2d] GET /' % num)
	print('[%2d] /               response -> %d' % (num, homepage_res.status_code))
	print('[%2d] (cookie)ASP.NET_SessionId = %s' % (num, homepage_res.cookies['ASP.NET_SessionId']))
	# HTTP GET!
	check_code_res = s.get(check_code_url, headers=check_code_headers)
	print('[%2d] GET /CheckCode.aspx' % num)
	print('[%2d] /CheckCode.aspx response -> %d' % (num, check_code_res.status_code))
	print('[%2d] !sleepd!' % num)
	sleep(86400)

threads = []
threads_max = 100

if __name__ == '__main__':
	if(len(sys.argv) > 1):
		threads_max = int(sys.argv[1])

	# create & start threads
	for i in range(1, threads_max + 1):
		t = threading.Thread(target=conn, args=(i,))
		threads.append(t)
		t.start()
		sleep(1)