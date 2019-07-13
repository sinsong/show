// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

int main()
{
	// test.txt里描述的大小，一次写那么多，剩下的再写剩下的那么多，数据出来处理画图
	// 研究一次写多少比较好

	FILE* origin = fopen("origin.bin", "rb");
	if (!origin)
	{
		perror("无法打开\"origin.bin\"");
		exit(1);
	}

	setbuf(origin, NULL);

	FILE* logfile = fopen("test_result.txt", "w");
	if (!logfile)
	{
		perror("我不信日志输出打不开？");
		exit(1);
	}

	size_t buffsize = 500;
	char copyfilename[20] = { 0 };

	std::vector<size_t> buffsizes = { 500,   595,   691,   787,   883,   979,  1075,  1171,  1267,
		1363,  1459,  1555,  1651,  1747,  1843,  1939,  2035,  2131,
		2227,  2323,  2419,  2515,  2611,  2707,  2803,  2898,  2994,
		3090,  3186,  3282,  3378,  3474,  3570,  3666,  3762,  3858,
		3954,  4050,  4146,  4242,  4338,  4434,  4530,  4626,  4722,
		4818,  4914,  5010,  5106,  5202,  5297,  5393,  5489,  5585,
		5681,  5777,  5873,  5969,  6065,  6161,  6257,  6353,  6449,
		6545,  6641,  6737,  6833,  6929,  7025,  7121,  7217,  7313,
		7409,  7505,  7601,  7696,  7792,  7888,  7984,  8080,  8176,
		8272,  8368,  8464,  8560,  8656,  8752,  8848,  8944,  9040,
		9136,  9232,  9328,  9424,  9520,  9616,  9712,  9808,  9904,
	   10000 };
	for(size_t buffsize : buffsizes)
	{
		printf("[test %d] run...\n", buffsize);
		memset(copyfilename, 0, 20);
		sprintf(copyfilename, "test_%d.bin", buffsize);
		rewind(origin);
		FILE* outfile = fopen(copyfilename, "wb"); //不检查了
		setbuf(outfile, NULL);
		time_t begin = time(NULL);
		//---
		void* buff = malloc(buffsize); // 不检查了
		if (!buff)
		{
			fprintf(logfile, "[test %d] malloc failed", buffsize);
			continue;
		}

		while (1)
		{
			if (fread(buff, buffsize, 1, origin) != 1)
			{
				break;
			}
			if (fwrite(buff, buffsize, 1, outfile) != 1)
			{
				fprintf(logfile, "[test %d] fwrite excetpion\n", buffsize);
				break;
			}
		}

		int rest = fread(buff, 1, buffsize, origin);
		if (fwrite(buff, rest, 1, outfile) != rest)
		{
			fprintf(logfile, "[test %d] fwrite excetpion\n", buffsize);
		}

		free(buff);
		//---
		time_t end = time(NULL);
		fclose(outfile);
		remove(copyfilename);

		// regex: \[test (\d+)\] time: (\d+).*
		fprintf(logfile, "[test %d] time: %lf\n", buffsize, difftime(end, begin));
	}

	fclose(origin);
	fclose(logfile);

	return 0;
}