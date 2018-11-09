#include <stdio.h>
void main()
{
	int i;
	char week[5][3]={"一","二","三","四","五"};
	for(i = 0; i <=9; i++)
	{
		printf("尾号为%d的车辆限行星期%s\n", i, week[(i % 5) == 0 ? 4 : (i % 5) - 1]);
	}
}
