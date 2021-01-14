/*
 * 首先输入一个 3 x 3 的方针，由 0 - 9 数字组成，其中 0 表示可以初始就能看到的数字
 * 接着输入三行 x y 坐标，表示第 x 行第 y 列的数字被刮开
 * 最后一行表示选择横着，竖着，或者斜着三个数字竞猜
 * 
 * 1-3表示第1行，第2行，第3行
 * 4-6表示列
 * 7表示左上到右下
 * 8表示右上到左下
 * 
 * 选出的三个数字综合按照得分表兑奖
 * 
 * 要求输出那三行坐标刮开的数字，接着输出一行为得到的奖金
 */

#include <iostream>
#include <string>
#include <algorithm>

int get(int *arr, int x, int y)
{
    return *(arr + (3 * (x - 1) + (y - 1)));
}

int sum(int *arr, int mode)
{
    switch(mode)
    {
    case 1: return arr[0] + arr[1] + arr[2];
    case 2: return arr[3] + arr[4] + arr[5];
    case 3: return arr[6] + arr[7] + arr[8];

    case 4: return arr[0] + arr[3] + arr[6];
    case 5: return arr[1] + arr[4] + arr[7];
    case 6: return arr[2] + arr[5] + arr[8];

    case 7: return arr[0] + arr[4] + arr[8];
    case 8: return arr[2] + arr[4] + arr[6];
    }
}

int scoretable[19] = {
    10000,36,720,360,80,252,108,72,54,180,72,180,119,36,306,1080,144,1800,3600
};
int score(int sum)
{
    return scoretable[sum - 6];
}

int main()
{
    int *arr = (int*)malloc(sizeof(int) * 9);
    scanf("%d%d%d", &arr[0], &arr[1], &arr[2]);
    scanf("%d%d%d", &arr[3], &arr[4], &arr[5]);
    scanf("%d%d%d", &arr[6], &arr[7], &arr[8]);
    int x1, y1, x2, y2, x3, y3;
    scanf("%d%d", &x1, &y1);
    scanf("%d%d", &x2, &y2);
    scanf("%d%d", &x3, &y3);
    int method;
    std::cin >> method;

    int *cur = arr;
    while(*cur != 0) ++cur;

    for(int i = 1; i <= 9; ++i)
    {
        auto r = std::find(arr, arr+9, i);
        if(r == arr+9)
        {
            *cur = i;
        }
    }

    std::cout << get(arr, x1, y1) << std::endl;
    std::cout << get(arr, x2, y2) << std::endl;
    std::cout << get(arr, x3, y3) << std::endl;
    std::cout << score(sum(arr, method)) << std::endl;
    return 0;
}