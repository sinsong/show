// 帮同学写的
// 模仿他的思路，并且自己创造
//

#include <stdio.h>

int main()
{
	int y;
	int i; //y年以前的天数

	printf("请输入年份：");
	scanf("%d", &y);

	int n = 1; //循环变量
	while(n < y)
	{
		if((n % 400 == 0)||(n % 4 == 0 && n % 100 != 0))
		{//闰年
			i += 366 % 7;
		}
		else
		{//平年
			i += 365 % 7;
		}
		//至于为什么，这是模运算（求余）的性质
		
		n++;
	}

	//n TM的才是循环变量
	n = 1;
	while(n <= 12) //大循环：输出12个月的日历
	{
		int days = i % 7; //根据模运算性质

		int mday; //每个月的天数

		switch(n)
		{ //高能预警：前方代码有毒
		default:
			if(n == 1)
			{printf("一月");mday=31;break;}
			days += 31;
			if(n == 2)
			{printf("二月");mday=((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))?29:28;break;}
			if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
				days += 29;
			else
				days += 28;
			if(n == 3)
			{printf("三月");mday=31;break;}
			days += 31;
			if(n == 4)
			{printf("四月");mday=30;break;}
			days += 30;
			if(n == 5)
			{printf("五月");mday=31;break;}
			days += 31;
			if(n == 6)
			{printf("六月");mday=30;break;}
			days += 30;
			if(n == 7)
			{printf("七月");mday=31;break;}
			days += 31;
			if(n == 8)
			{printf("八月");mday=31;break;}
			days += 31;
			if(n == 9)
			{printf("九月");mday=30;break;}
			days += 30;
			if(n == 10)
			{printf("十月");mday=31;break;}
			days += 31;
			if(n == 11)
			{printf("十一月");mday=30;break;}
			days += 30;
			if(n == 12)
			{printf("十二月");mday=31;break;}
			//不用再加了
		}
		printf("\n"); //刚才打印了多少月么，换个行，对个齐

		days++; //当天
		int week = days % 7; //星期几就粗来了
		
		printf("Sun Mon Tue Wed Thu Fri Sat\n");

		for(int s = 0; s < week; ++s)
		{
			printf("    ");//补空位
		}

		int count = week;

		for (int p = 1; p <= mday; ++p)
		{
			printf("%4d", p);
			count++;
			if (count % 7 == 0)
			{
				printf("\n");
			}
		}
		
		//每个月结束后给个换行
		printf("\n");
		n++;//递增，玩下个月
	}

	return 0;
}
