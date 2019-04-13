// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <chrono>

#pragma fenv_access (on)

int main(int argc, char *argv[])
{
	//ShellExecute(NULL, L"open", L"https://github.com", L"", L"", SW_SHOWNORMAL);

	if (argc < 2) return 0;

	FILE *file = fopen(argv[1], "rb");
	unsigned int len = 0;
	int c = 0;
	
	puts("\n\n");
	//1
	auto start1 = std::chrono::high_resolution_clock::now();
	while ((c = fgetc(file)) != EOF)
	{
		++len;
	}
	auto end1 = std::chrono::high_resolution_clock::now();
	std::cout << "1: " << std::chrono::duration<double>{end1 - start1}.count() << "ints" << std::endl;
	printf("len1: %d\n", len);

	rewind(file);
	len = 0;

	//2
	auto start2 = std::chrono::high_resolution_clock::now();
	while (!feof(file))
	{
		c = fgetc(file);
		if (c == EOF) break;
		++len;
	}
	auto end2 = std::chrono::high_resolution_clock::now();
	std::cout << "1: " << std::chrono::duration<double>{end2 - start2}.count() << "ints" << std::endl;
	printf("len2: %d\n", len);

	rewind(file);
	len = 0;

	//3
	unsigned char *buff = (unsigned char *) malloc(4096);
	memset(buff, 0, 4096);
	size_t readret = 0;
	long pos;
	auto start3 = std::chrono::high_resolution_clock::now();
	while (true)
	{
		pos = ftell(file);
		readret = fread(buff, 4096, 1, file);
		if (readret == 1)
		{
			len += 4096;
		}
		else
		{
			break;
		}
	}
	fseek(file, pos, SEEK_SET);
	while (true)
	{
		readret = fread(buff, 1, 1, file);
		if (readret)
		{
			++len;
		}
		else
		{
			if (feof(file))
			{
				break;
			}
			if (ferror(file))
			{
				clearerr(file);
			}
		}
	}
	auto end3 = std::chrono::high_resolution_clock::now();
	std::cout << "1: " << std::chrono::duration<double>{end3 - start3}.count() << "ints" << std::endl;
	printf("len3: %d\n\n", len);

	return 0;
}