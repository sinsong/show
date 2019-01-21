# 登录器2

import requests
import re
from PIL import Image
from io import BytesIO

homepage_url    = 'http://jwgl.xawl.edu.cn'
check_code_url  = 'http://jwgl.xawl.edu.cn/CheckCode.aspx'

login_url       = 'http://jwgl.xawl.edu.cn/default2.aspx'

user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win32; x32) AppleWebKit/534.16 (KHTML, like Gecko) Chrome/64.0.3282.140'

# session 会话 保持一个会话
s = requests.Session()

# homepage

homepage_headers = {
'Accept': '*/*',
'Accept-Encoding':'deflate',
'Accept-Language': 'zh-Hans-CN, zh-Hans; q=0.8, en-US; q=0.5, en; q=0.3',
'Cache-Control': 'no-cache',
'Connection': 'Keep-Alive',
'Host': 'jwgl.xawl.edu.cn',
'User-Agent': user_agent
}

# HTTP GET!
homepage_res = s.get(homepage_url, headers=homepage_headers)

print('homepage cookie ->', homepage_res.cookies)

# check_code

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

# HTTP GET!
check_code_res = s.get(check_code_url, headers=check_code_headers)

# 本来觉得要缓存一下
#with open('check_code.gif', 'wb') as f:
#	f.write(check_code_res.content)
# 感谢requests官网的直接打开例子

i = Image.open(BytesIO(check_code_res.content))

print('check_code_res ->', check_code_res.status_code)

# login

studentid = '学号'
passwd = '密码'
# check_code = 'hehe' 成为历史吧！！！
i.show()
check_code = input('input check_code>>>>>')

login_headers = {
'Accept': 'text/html, application/xhtml+xml, application/xml; q=0.9, */*; q=0.8',
'Accept-Encoding': 'deflate',
'Accept-Language': 'zh-Hans-CN, zh-Hans; q=0.8, en-US; q=0.5, en; q=0.3',
'Cache-Control': 'max-age=0',
'Connection': 'Keep-Alive',
'Content-Type': 'application/x-www-form-urlencoded',
'User-Agent': user_agent,
'Host': 'jwgl.xawl.edu.cn',
'Referer': 'http://jwgl.xawl.edu.cn/',
'Upgrade-Insecure-Requests': '1'
}

login_data_VIEWSTATE = re.findall(r'name="__VIEWSTATE" value="(\S+)"', homepage_res.text)[0]
print('login_data_VIEWSTATE ->', login_data_VIEWSTATE)

payload = {
'__VIEWSTATE': login_data_VIEWSTATE,
'txtUserName': studentid,
'Textbox1': '',
'TextBox2': passwd,
'txtSecretCode': check_code,
'RadioButtonList1': b'\xd1\xa7\xc9\xfa',
'Button1': '',
'lbLanguage': '',
'hidPdrs': '',
'hidsc': ''
}

# HTTP POST
login_res = s.post(login_url, data=payload, headers=login_headers)

print('login_res ->', login_res.status_code)
print('--------------------')
print(login_res.text)