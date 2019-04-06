// textp.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//


#include <stdio.h>
#include <ctype.h>

void bclear(int *buffer)
{
	for (int i = 0; i < 16; ++i)
	{
		buffer[i] = EOF;
	}
}

void bprint(int *buffer)
{
	for (int i = 0; i < 16; ++i)
	{
		putchar(isprint(buffer[i]) ? buffer[i] : '.');
	}
}

void bprint2(int *buffer)
{
	for (int i = 0; i < 16; ++i)
	{
		if (buffer[i] == EOF) return;
		putchar(isprint(buffer[i]) ? buffer[i] : '.');
	}
}

int main(int argc, char *argv[])
{
	FILE *file = fopen(argv[1], "rb");

	int c = 0;
	unsigned count = 1;
	int buffer[16] = { EOF };

	while ((c = getc(file)) != EOF)
	{
		printf("%02x", c);
		buffer[(count - 1) % 16] = c;
		if (count % 2 == 0) putchar(' ');
		if (count % 8 == 0) putchar(' ');
		if (count % 16 == 0)
		{
			printf("  ");
			bprint(buffer);
			bclear(buffer);
			putchar('\n');
		}
		++count;
	}

	// Not empty
	while (true)
	{
		printf("  ");
		if (count % 2 == 0) putchar(' ');
		if (count % 8 == 0) putchar(' ');
		if (count % 16 == 0)
		{
			printf("  ");
			bprint2(buffer);
			putchar('\n');
			break;
		}
		++count;
	}

	return 0;
}

