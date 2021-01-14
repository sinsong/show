/*
 * 你将得到一些聊天记录，一行一个。整行为英文句点 . 表示结束
 * 输出的第一行为聊天记录条数
 * 输出的第二行为空格隔开的：第一次出现 "chi1 huo3 guo1" 的序号，一共多少条消息出现了 "chi1 huo3 guo1"
 * 如果没有出现，则输出表情包 -_-#
 */

#include <iostream>
#include <string>

int main()
{
    std::string line;
    bool find = false;
    int count = 0;
    int fcount = 0;
    int first = 0;
    while(true)
    {
        std::getline(std::cin, line);
        if(line == ".")
            break;
        ++count;
        if(line.find("chi1 huo3 guo1") != -1)
        {
            if(fcount == 0)
            {
                first = count;
            }
            ++fcount;
        }
    }

    std::cout << count << std::endl;
    if(fcount > 0)
    {
        std::cout << first << " " << fcount << std::endl;
    }
    else
    {
        std::cout << "-_-#" << std::endl;
    }
    return 0;
}