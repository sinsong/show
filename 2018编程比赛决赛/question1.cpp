#include <stdio.h>
void main()
{
	int i;
	char week[5][3]={"һ","��","��","��","��"};
	for(i = 0; i <=9; i++)
	{
		printf("β��Ϊ%d�ĳ�����������%s\n", i, week[(i % 5) == 0 ? 4 : (i % 5) - 1]);
	}
}
