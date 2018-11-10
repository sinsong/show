//author:literal

#include <stdio.h>

//forward declation
void print_cal(int first_week, int days, int mon);

int main()
{
	int year = 0;

	printf("日历\n请输入年份（数字）:");
	scanf("%d", &year);

	int nday = (year - 1) * 365;
	for (int i = 1; i <= (year - 1); ++i)
	{
		if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		{
			++nday;
		}
	}
	int n_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (((year % 4 == 0)&&(year % 100 != 0))||(year % 400 == 0))
	{
		n_month[1] = 29;
	}

	for (int mon = 1; mon <= 12; ++mon)
	{
		int true_day = nday;
		int week = 0;

		for (int i = 1; i < mon; ++i)
		{
			true_day += n_month[i - 1];
		}

		week = true_day % 7;

		print_cal(week, n_month[mon - 1], mon);
	}

	getchar();
	getchar();

	return 0;
}

void print_cal(int first_week, int days, int mon)
{
	//日历头 - 月份
	switch (mon)
	{
	case 1:
		printf("一月");
		break;
	case 2:
		printf("二月");
		break;
	case 3:
		printf("三月");
		break;
	case 4:
		printf("四月");
		break;
	case 5:
		printf("五月");
		break;
	case 6:
		printf("六月");
		break;
	case 7:
		printf("七月");
		break;
	case 8:
		printf("八月");
		break;
	case 9:
		printf("九月");
		break;
	case 10:
		printf("十月");
		break;
	case 11:
		printf("十一月");
		break;
	case 12:
		printf("十二月");
		break;
	}
	printf("\n");

	printf(" Sun Mon Tue Wed Thu Fri Sat\n");

	first_week %= 7;

	//补空
	for (int c = 0; c < first_week; ++c)
	{
		printf("    ");
	}

	//开始日期
	int w = first_week;
	int n = 1;
	while (n <= days)
	{
		printf("%4d", n);
		if (w % 7 == 6)
		{
			printf("\n"); //周六换行
		}
		++n;
		++w;
	}

	printf("\n----------\n"); //打印一次日历换行
}
