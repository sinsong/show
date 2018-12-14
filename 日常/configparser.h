#pragma once //ͷ�ļ�������

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
			continue; //���оͲ�Ҫ����������(����û���ǵ�ȫ�ǿո����)
		}
		
		size_t fpos = read_line.find_first_of(':');
		if (fpos != std::string::npos)
		{
			//�ҵ�
			std::string key = read_line.substr(0, fpos);
			std::string value = read_line.substr(fpos + 1, read_line.size() - fpos);

			rmspace(key);
			rmspace(value);

			this->kw[key] = value; //std::map��operator[]�ǿ��Բ���͸��µġ�
		}
		else
		{
			//û�ҵ�
			//LINE���ǵ�ǰ�У�����ѡ����ԣ�����Ҫ������ܵĻ�����LINE����ɾ����
		}
		++LINE;
	}
}

std::string config_parser::query(std::string key)
{
	auto ret = kw.find(key);
	if (ret == kw.end())
	{
		//û�ҵ�
		return std::string(); //���ؿ��ַ�����ʾû�ҵ�
	}
	else
	{
		return ret->second;
	}
}

void config_parser::rmspace(std::string &s)
{
	//ɾ���ײ��ո�
	size_t count = 0;
	while (s[count] == ' ' && count < s.size())
		++count;
	s.erase(0, count);

	//ɾ��β���ո�
	size_t pos = s.size();
	while (pos >= 0 && s[pos - 1] == ' ')
		--pos;
	s.erase(pos, s.size() - pos);
}