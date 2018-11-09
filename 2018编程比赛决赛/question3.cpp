#include <cstdio>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <cstdlib>

struct status
{
	int pos;
	int last_mod;
};

struct node
{
	status s;
	std::shared_ptr<node> parents;
};

int main()
{
	node root;
	root.parents = nullptr;
	root.s.last_mod = 0;
	root.s.pos = 0;

	std::shared_ptr<node> result = nullptr;
	
	std::list<std::shared_ptr<node>> current;
	current.push_back(std::make_shared<node>(root));
	int bbk = 0; //break
	while(1)
	{
		if(bbk == 1)
		{
			break;
		}

		std::list<std::shared_ptr<node>> now;
		for(auto b = current.begin(); b != current.end(); ++b)
		{
			if((*b)->s.pos == 1)
			{
				result = *b;
				bbk = 1;
				break;
			}
		}

		for(auto b = current.begin(); b != current.end(); ++b)
		{
			std::shared_ptr<node> F = std::make_shared<node>();
			F->s.last_mod = 97;
			F->s.pos = (*b)->s.pos + 97;
			F->parents = *b;

			std::shared_ptr<node> B = std::make_shared<node>();
			B->s.last_mod = -127;
			B->s.pos = (*b)->s.pos - 127;
			B->parents = *b;

			if (abs(F->s.pos) > 500)
			{
				F.reset();
			}
			else
			{
				now.push_back(F);
			}

			if (abs(B->s.pos) > 500)
			{
				B.reset();
			}
			else
			{
				now.push_back(B);
			}
		}

		auto ub = std::unique(now.begin(), now.end(), [](std::shared_ptr<node> a,std::shared_ptr<node> b)->bool{
			return (a->s.pos == b->s.pos);
		});

		now.erase(ub, now.end());

		current = std::move(now);
	}


	std::shared_ptr<node> p = result;
	std::list<int> history;
	while(p != nullptr)
	{
		history.push_back(p->s.last_mod);
		p = p->parents;
	}

	int count = 1;
	int pos = 0;
	for(auto b = history.rbegin(); b != history.rend(); ++b)
	{
		switch(*b)
		{
		case 97:
			pos += 97;
			printf("第%3d步：前进 97米 - 位置：%3d\n", count, pos);
			break;
		case -127:
			pos -= 127;
			printf("第%3d步：后退127米 - 位置：%3d\n", count, pos);
			break;
		default:
			continue;
		}
		++count;
	}

	current.clear();
	
	return 0;
}
