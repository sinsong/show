// ��ͬѧд��
// ģ������˼·�������Լ�����
//

#include <stdio.h>

int main()
{
	int y;
	int i; //y����ǰ������

	printf("��������ݣ�");
	scanf("%d", &y);

	int n = 1; //ѭ������
	while(n < y)
	{
		if((n % 400 == 0)||(n % 4 == 0 && n % 100 != 0))
		{//����
			i += 366 % 7;
		}
		else
		{//ƽ��
			i += 365 % 7;
		}
		//����Ϊʲô������ģ���㣨���ࣩ������
		
		n++;
	}

	//n TM�Ĳ���ѭ������
	n = 1;
	while(n <= 12) //��ѭ�������12���µ�����
	{
		int days = i % 7; //����ģ��������

		int mday; //ÿ���µ�����

		switch(n)
		{ //����Ԥ����ǰ�������ж�
		default:
			if(n == 1)
			{printf("һ��");mday=31;break;}
			days += 31;
			if(n == 2)
			{printf("����");mday=((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))?29:28;break;}
			if((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
				days += 29;
			else
				days += 28;
			if(n == 3)
			{printf("����");mday=31;break;}
			days += 31;
			if(n == 4)
			{printf("����");mday=30;break;}
			days += 30;
			if(n == 5)
			{printf("����");mday=31;break;}
			days += 31;
			if(n == 6)
			{printf("����");mday=30;break;}
			days += 30;
			if(n == 7)
			{printf("����");mday=31;break;}
			days += 31;
			if(n == 8)
			{printf("����");mday=31;break;}
			days += 31;
			if(n == 9)
			{printf("����");mday=30;break;}
			days += 30;
			if(n == 10)
			{printf("ʮ��");mday=31;break;}
			days += 31;
			if(n == 11)
			{printf("ʮһ��");mday=30;break;}
			days += 30;
			if(n == 12)
			{printf("ʮ����");mday=31;break;}
			//�����ټ���
		}
		printf("\n"); //�ղŴ�ӡ�˶�����ô�������У��Ը���

		days++; //����
		int week = days % 7; //���ڼ��ʹ�����
		
		printf("Sun Mon Tue Wed Thu Fri Sat\n");

		for(int s = 0; s < week; ++s)
		{
			printf("    ");//����λ
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
		
		//ÿ���½������������
		printf("\n");
		n++;//���������¸���
	}

	return 0;
}
