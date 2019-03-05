#include <stdio.h>
#include <string.h>

#define magic_number 12138
#define buff_size 20

int main(int argc, char* argv[])
{
	const char *passwd = "123456";

	int count = 0;
	int pass = 0;

	while(count < 3)
	{
		char input[buff_size];

		printf("input password:");
		fgets(input, buff_size, stdin);

		for(int i = 0; i < buff_size ; ++i)
		{ if(input[i] == '\n') input[i] = '\0';}

		if(strcmp(input, passwd) == 0)
		{
			pass = magic_number;
			break;
		}
		else
		{
			printf("error. input again\n");
			++count;
		}
	}

	if(pass == magic_number)
	{
		printf("pass\n");
	}
	else
	{
		printf("over\n");
	}

	return 0;
}

