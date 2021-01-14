/*
 * 输入第一行为运算子，压栈
 * 输入第二行为运算符，压栈
 * 
 * 计算顺序：
 * 1. 从运算子堆栈中按顺序弹出 n1, n2
 * 2. 从运算符中弹出 op
 * 3. 计算 n2 op n1 压入堆栈
 * 
 * 触发要检查被除数，如果为零则报错 ERROR: %d/0 并退出程序
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int num_stack[64] = {0};
int *num_sp = num_stack;
char op_stack[64] = {0};
char *op_sp = op_stack;

#define sempty(pf) (pf##_sp == pf##_stack)
#define spush(pf, value) (*(++pf##_sp) = value)
#define spop(pf) (*(pf##_sp--))

int main()
{
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i)
    {
        int num;
        scanf("%d", &num);
        spush(num, num);
    }

    for(int i = 0; i < N - 1; ++i)
    {
        char c;
        while(!ispunct((c = getchar())));
        spush(op, c);
    }

    for(int i = 0; i < N - 1; ++i)
    {
        int n1 = spop(num);
        int n2 = spop(num);
        int result;
        switch(spop(op))
        {
            case '+': result = n2 + n1; break;
            case '-': result = n2 - n1; break;
            case '*': result = n2 * n1; break;
            case '/':
                if(n1 == 0)
                {
                    printf("ERROR: %d/0", n2);
                    exit(0);
                }
                result = n2 / n1;
                break;
        }
        spush(num, result);
    }

    printf("%d", spop(num));

    return 0;
}