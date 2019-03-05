#include <iostream>
#include <algorithm> //max, min
#include <stdio.h>

int N = 0;

//���⵽�ڵڼ���
int shell(int i, int j)
{
	int ii = std::min(i, N - i + 1);
	int jj = std::min(j, N - j + 1);

	return std::min(ii, jj);
}

//ĳ��Ԫ�ظ���
int shell_sum(int i)
{
	return 4 * i - 4;
}

int main()
{
	printf("N:");
	scanf_s("%d", &N);
	printf("\n");

	//�������
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			//���Ҫ���������
			int r = 0;

			//���Ԫ�����
			for (int a = 1; a < shell(i, j); ++a) //���2
			{
				r += shell_sum(N - (   (a - 1) * 2)   ); //���1
			}

			//����任
			//�ڲ�Ԫ�ر任��(0,0)λ��
			int x = i - shell(i, j) + 1;
			int y = j - shell(i, j) + 1;

			if (j < i)
			{
				//���ӵ����
				//���һ ��ȥ ����� ������a = �����е�shell(i,j)��
				std::swap(x, y); //���Ա任����һ�����
				//Ȼ���øò�������ȥ������ĸ���������
				r += (shell_sum(N - ((shell(i,j) - 1) * 2))) - (y + (x - 1)) + 2;
				//����+2��Ҳ��֪��Ϊʲô��������ƫ�ã�Ȼ�����Ҫ���ˡ�����
			}
			else
			{
				//�򵥵����
				//����������ò����˳��ڼ���Ԫ��
				r += y + (x - 1); //�����
			}
			printf("%d\t", r); //���
		}

		printf("\n"); //����
	}

	return 0;
}