#include <stdio.h>
#include <stdlib.h>

#define NDATA 15

int main(int argc, char* argv[])
{
	int data[NDATA] = { 0 };

	for (int i = 0; i < NDATA; ++i)
	{
		scanf("%d", &data[i]);
	}

	printf("\n");
	//---------------------------------------
	printf("\nfunction 1:\n");

	for (int i = 0; i < NDATA; ++i)
	{
		printf("%d ", data[i]);
	}

	printf("\n");
	//---------------------------------------
	printf("\nfunction 2:\n");

	for (int i = NDATA - 1; i >= 0; --i)
	{
		printf("%d ", data[i]);
	}

	printf("\n");
	//---------------------------------------
	printf("\nfunction 3:\n");

	int found = 0;
	for (int i = 0; i < NDATA; ++i)
	{
		if (data[i] == 100)
		{
			printf("find 100 at -> %d", i);
			found = 1;
			break;
		}
	}
	if (found != 1) printf("not find 100");

	printf("\n");
	//---------------------------------------
	printf("\nfunction 4:\n");

	int sum = 0;
	for (int i = 0; i < NDATA; ++i)
	{
		if (data[i] >= 90)
		{
			++sum;
		}
	}
	printf("”≈–„»À ˝: %d", sum);

	printf("\n");
	//---------------------------------------
	printf("\nfunction 5:\n");

	for (int i = 0; i < NDATA; ++i)
	{
		if (data[i] < 60)
		{
			data[i] = -1;
		}
	}

	while (1)
	{
		int n = 0, e = NDATA - 1;
		while (e > 0 && data[e] == -1) e--;
		while (n < NDATA && data[n] != -1) n++;
		if (n == e + 1)
		{
			break;
		}
		//swap n,e
		data[n] = data[e];
		data[e] = -1;
	}

	for (int i = 0; i < NDATA; ++i)
	{
		if (data[i] == -1)
			break;
		printf("%d ", data[i]);
	}

	printf("\n");
	//---------------------------------------
	printf("\nfunction: 6\n");

	int e = 0;
	while (e < NDATA && data[e] != -1)
		e++;

	for (int i = 0; i < e - 1; ++i)
	{
		for (int j = 0; j < e - i - 1; ++j)
		{
			if (data[j] < data[j + 1])
			{
				int temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < e; ++i)
	{
		printf("%d ", data[i]);
	}

	printf("\n");
	//---------------------------------------
	printf("\nfunction7 :\n");

	data[e] = 78;
	e++;

	for (int i = 0; i < e - 1; ++i)
	{
		for (int j = 0; j < e - i - 1; ++j)
		{
			if (data[j] < data[j + 1])
			{
				int temp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < e; ++i)
	{
		printf("%d ", data[i]);
	}

	return 0;
}

