/*
 * 有一些趣味问题为二叉树
 * 叶子节点从左到右按顺序编号
 * 输入第一行为 N 题目数量, M 参与人数
 * 接下来 M 行由 N 个 y/n 是否组成的字符串，表示二叉树中的选择
 * 输出对应的叶子编号
 * 
 *     y     *     n
 *  y  *  n     y  *  n
 * y* n   *     *     *
 * 1  2  3  4  5  6  7  8
 */

#include <iostream>
#include <string>

#define bset(var, idx) {var |= 0x1 << (idx);}
#define brst(var, idx) {var &= ~(0x1 << (idx));}

int main()
{
    int N, M;
    std::cin >> N >> M;
    int32_t result;
    std::string line;

    getchar();
    for(int i = 0; i < M; ++i)
    {
        std::getline(std::cin, line);
        result = 0;
        for(int j = 0; j < N; ++j)
        {
            if(line[j] == 'n')
            {
                bset(result, N - j - 1);
            }
        }

        printf("%d\n", result + 1);
    }


    return 0;
}