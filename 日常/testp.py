import sys
import re

def main():
	# 打开文件 读取整个文件
	with open(sys.argv[1], 'rb')as f:
		text = str(f.read(), 'utf8')
	
	# 预处理 按行分割
	content = text.split('\r\n')
	
	script = []
	term = []
	
	# 分析
	for line in content:
		if len(line) == 0:
			if len(term) == 0: # 跳过连续空行
				continue
			script.append(term)
			term = []
		else:
			term.append(line)
	if len(term) != 0:
		script.append(term)
	
	#---------------------------------
	# 打印结果
	#for m in script:
	#	print(m, '\n\n')
	
	# 匹配人名
	rename = re.compile(R"【(.+)】")
	
	code = []
	for t in script:
		if rename.match(t[0]):
			code.append({'role': rename.match(t[0]).group(1), 'words': "".join(t[1:])})
		else:
			code.append({'role': None, 'words': "".join(t)})
	
	for c in code:
		if c['role'] == None:
			print('"' + c['words'] + '"')
			continue
		print('%s "%s"' % (c['role'], c['words']))

if __name__ == '__main__':
	main()