/*
 * 输入:
 *     a1 a2 a3 a4 amin aval
 * a1 - a4 为压力，amin 是最低压力 aval 是阈值
 * 
 * 正常输出 Normal
 * 
 * 1. 某个轮子的压力与其中最大值之间相差大于阈值报警 Warning: please check #x! (x 为第轮子编号)
 * 2. 只要有一个轮子压力低于最低压力也报警
 * 3. 两个以上轮子异常则要求检查所有轮子，报警 Warning: please check all the tires!
 */

#include <stdio.h>
#include <stdlib.h>

#define amax(var) do{ if(var > max) max = var; }while(0);
#define check(idx) do{                       \
    if(max - a##idx > aval || a##idx < amin) \
    {                                        \
                                             \
        if(idx_alert != -1)                  \
            f_multierr = 1;                  \
        idx_alert = idx;                     \
    }                                        \
                                             \
}while(0);

int main()
{
    int a1, a2, a3, a4, amin, aval;
    scanf("%d%d%d%d%d%d", &a1, &a2, &a3, &a4, &amin, &aval);

    //max
    int max = a1;
    amax(a2);
    amax(a3);
    amax(a4);

    int f_multierr = 0;
    int idx_alert = -1;

    check(1);
    check(2);
    check(3);
    check(4);

    if(idx_alert == -1)
    {
        printf("Normal");
    }
    else
    {
        if(f_multierr)
        {
            printf("Warning: please check all the tires!");
        }
        else
        {
            printf("Warning: please check #%d!", idx_alert);
        }
    }
    
    
    return 0;
}