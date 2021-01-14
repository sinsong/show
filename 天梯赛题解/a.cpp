#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>

struct record
{
    std::string name;
    std::string id;
    int status;
    int hh;
    int mm;
};

int main()
{
    int D, //day
        P; //split day
    scanf("%d%d", &D, &P);

    std::vector<record> records;
    // D block
    for(int d = 0; d < D; ++d)
    {
        int T, S;
        scanf("%d%d", &T, &S);
        //record
        for(int t = 0; t < T; ++t)
        {
            std::string line;
            std::getline(std::cin, line);

            record r;

            size_t space1 = line.find(' ');
            r.name = line.substr(0, space1);
            line = line.substr(space1, line.size());

            size_t space2 = line.find(' ');
            r.id = line.substr(0, space2);
            line = line.substr(space2, line.size());

            sscanf(line.c_str(), "%d %d:%d", &r.status, &r.hh, &r.mm);

            //-----
            #define p(var) {std::cout << #var << " : " << var << std::endl;}
            p(r.name);
            p(r.id);
            p(r.status);
            p(r.hh);
            p(r.mm);
        }
    }
}