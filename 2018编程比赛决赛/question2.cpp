#include <cstdio>
#include <functional>

template<typename T>
inline T max(T x, T y)
{
	std::greater<T> oper;
	return (oper(x,y)) ? x : y ;
}

int num(int x, int y, int shell);
inline int num_impl_o(int x, int y, int shell);
inline int num_impl_j(int x, int y, int shell);

int main()
{
	int n;
	printf("Input N:");
	scanf("%d", &n);

	//print numbers
	for(int x = 1; x <= n; ++x )
	{
		for(int y = 1; y <= n; ++y )
		{
			int get_num = num(x, y, max(x, y));
			printf("%3d ", get_num);
		}
		printf("\n");
	}
}

//get the number
int num(int x, int y, int shell)
{
	if(shell % 2 == 0)
	{//ou
		return num_impl_o(x,y,shell);
	}
	else
	{//ji
		return num_impl_j(x,y,shell);
	}
}

inline int num_impl_o(int x, int y, int shell)
{
	int base = shell * shell;
	int baseb = (shell - 1) * (shell - 1);
	if( y >= x)
	{//simple
		return base - x + 1;
	}
	else
	{//hard
		return baseb + y;
	}
}
inline int num_impl_j(int x, int y, int shell)
{
	int base = shell * shell;
	int baseb = (shell - 1) * (shell - 1);
	if( y >= x)
	{//simple
		return baseb + x;
	}
	else
	{//hard
		return base - y + 1;
	}
}