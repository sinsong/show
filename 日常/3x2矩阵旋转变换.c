#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned char byte; // 辅助类型

byte origin[6] = { 1,2,3,4,5,6 };
byte ar[6] = { 2,5,3,1,4,6 }; // α 变换的逆变换
byte br[6] = { 1,3,6,4,2,5 }; // β 变换的逆变换

// 变换
void T(byte* x, byte* y, byte* type)
{
	for (int i = 0; i < 6; ++i)
	{
		y[i] = x[type[i] - 1];
	}
}

// 配置 -> unsigned int 的映射
unsigned key(byte* x)
{
	return x[0] * 100000u + x[1] * 10000u + x[2] * 1000u + x[3] * 100u + x[4] * 10u + x[5];
}

unsigned keyi(int* x)
{
	return x[0] * 100000 + x[1] * 10000 + x[2] * 1000 + x[3] * 100 + x[4] * 10 + x[5];
}

// 反向映射
void unkey(unsigned key, byte* x)
{
	x[0] = (key / 100000) % 10;
	x[1] = (key / 10000) % 10;
	x[2] = (key / 1000) % 10;
	x[3] = (key / 100) % 10;
	x[4] = (key / 10) % 10;
	x[5] = (key / 1) % 10;
}

// 未使用：输出配置
void pk(byte* x)
{
	printf("%u", key(x));
}

void h(int* hack)
{
	//unsigned insert = 0;
	for (unsigned ii = 0; ii < 4; ++ii) // 我猜4轮就够了
	{
		for (int i = 0; i < 999999u; ++i)
		{
			if (hack[i] != 0)
			{
				byte x[6] = { 0 };
				byte a[6] = { 0 };
				byte b[6] = { 0 };
				unkey(i, x);
				T(x, a, ar);
				T(x, b, br);
				if (hack[key(a)] == 0)
				{
					hack[key(a)] = hack[i] + 1;
					//++insert;
					//printf("round: %u | insert: %u\n", ii, insert);
				}
				if (hack[key(b)] == 0)
				{
					hack[key(b)] = hack[i] + 1;
					//++insert;
					//printf("round: %d | insert: %d\n", ii, insert);
				}
			}
		}
	}
}

int main()
{
	// 下标 -> 答案 的映射 0 表示不可能
	int *hack = (int *)malloc(sizeof(int) * 999999);

	if (hack == nullptr)
	{
		printf("malloc failed");
		exit(0);
	}
	memset(hack, 0, sizeof(int) * 999999);

	byte a1[6] = { 0 };
	byte b1[6] = { 0 };
	// 生成并插入第一轮结果
	T(origin, a1, ar);
	T(origin, b1, br);
	hack[key(a1)] = 1;
	hack[key(b1)] = 1;

	h(hack); // 反向遍历

	// 打印结果
	/*
	FILE *f = fopen("hack.txt", "w");
	unsigned count = 0;
	for (int i = 0; i < 999999u; ++i)
	{
		if (hack[i] != 0)
		{
			fprintf(f, "cfg: %d - answer: %d\n", i, hack[i]);
			++count;
		}
	}
	printf("count: %u", count);
	fclose(f);
	*/

	// 处理问题
	int num;
	scanf("%d", &num);
	int *inputs = (int*)malloc(sizeof(int) * num);
	for (unsigned i = 0; i < num; ++i)
	{
		int input[6] = { 0 };
		scanf("%d%d%d%d%d%d", &input[0], &input[1], &input[2], &input[3], &input[4], &input[5]);
		inputs[i] = keyi(input);
	}

	for (unsigned i = 0; i < num; ++i)
	{
		printf("%d\n", hack[inputs[i]]);
	}

	free(inputs);
	free(hack);

	return 0;
}