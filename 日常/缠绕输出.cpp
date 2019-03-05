#include <iostream>
#include <algorithm> //max, min
#include <stdio.h>

int N = 0;

//从外到内第几层
int shell(int i, int j)
{
	int ii = std::min(i, N - i + 1);
	int jj = std::min(j, N - j + 1);

	return std::min(ii, jj);
}

//某层元素个数
int shell_sum(int i)
{
	return 4 * i - 4;
}

int main()
{
	printf("N:");
	scanf_s("%d", &N);
	printf("\n");

	//坐标迭代
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			//最后要输出的数字
			int r = 0;

			//外层元素求和
			for (int a = 1; a < shell(i, j); ++a) //语句2
			{
				r += shell_sum(N - (   (a - 1) * 2)   ); //语句1
			}

			//坐标变换
			//内层元素变换到(0,0)位置
			int x = i - shell(i, j) + 1;
			int y = j - shell(i, j) + 1;

			if (j < i)
			{
				//复杂的情况
				//语句一 减去 语句三 （其中a = 语句二中的shell(i,j)）
				std::swap(x, y); //尝试变换到第一个情况
				//然后用该层总数减去简单情况的个数。。。
				r += (shell_sum(N - ((shell(i,j) - 1) * 2))) - (y + (x - 1)) + 2;
				//最后的+2我也不知道为什么，反正是偏置，然后符合要求了。。。
			}
			else
			{
				//简单的情况
				//根据坐标求该层缠绕顺序第几个元素
				r += y + (x - 1); //语句三
			}
			printf("%d\t", r); //输出
		}

		printf("\n"); //换行
	}

	return 0;
}