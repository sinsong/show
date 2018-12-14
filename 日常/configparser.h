#pragma once //头文件保护符

#include <string>
#include <istream>
#include <map>

class config_parser
{
public:
	config_parser() = default;

	void parse(std::istream &ifs);
	std::string query(const std::string key);

private:
	std::map<std::string, std::string> kw;
	void rmspace(std::string &s);
};

//-------------------------------------------------------------

void config_parser::parse(std::istream &ifs)
{
	unsigned LINE = 1;
	std::string read_line;
	while (ifs.good())
	{
		std::getline(ifs, read_line);
		if (read_line.empty())
		{
			continue; //空行就不要当作错误了(但是没考虑到全是空格的行)
		}
		
		size_t fpos = read_line.find_first_of(':');
		if (fpos != std::string::npos)
		{
			//找到
			std::string key = read_line.substr(0, fpos);
			std::string value = read_line.substr(fpos + 1, read_line.size() - fpos);

			rmspace(key);
			rmspace(value);

			this->kw[key] = value; //std::map的operator[]是可以插入和更新的。
		}
		else
		{
			//没找到
			//LINE就是当前行，这里选择忽略（不需要这个功能的话，把LINE变量删掉）
		}
		++LINE;
	}
}

std::string config_parser::query(std::string key)
{
	auto ret = kw.find(key);
	if (ret == kw.end())
	{
		//没找到
		return std::string(); //返回空字符串表示没找到
	}
	else
	{
		return ret->second;
	}
}

void config_parser::rmspace(std::string &s)
{
	//删除首部空格
	size_t count = 0;
	while (s[count] == ' ' && count < s.size())
		++count;
	s.erase(0, count);

	//删除尾部空格
	size_t pos = s.size();
	while (pos >= 0 && s[pos - 1] == ' ')
		--pos;
	s.erase(pos, s.size() - pos);
}