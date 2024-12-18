#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 使用函数迭代的形式获得斐波那契数(不考虑溢出）
int fib(int n)
{
    if (n == 1 || n == 2) // 对 n = 1 或 n = 2 的特殊处理
    {
        return 1;
    }

    int a = 1, b = 1, c = 0;

    for (int i = 3; i <= n; i++) // 从第 3 项开始计算
    {
        c = a + b;
        a = b;
        b = c;
    }

    return c; // 返回第 n 项的结果
}

int main()
{
    int n = 0;
    printf("你想要第几位的斐波那契数？> ");
    while (scanf("%d", &n) != 1 || n <= 0) // 输入验证
    {
        printf("\n错误输入！请重试：>");
        while (getchar() != '\n'); // 清空缓冲区
    }

    printf("整个斐波那契数列为: ");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", fib(i)); // 输出斐波那契数列的每一项
    }

    int output = fib(n); // 只计算一次 fib(n)
    printf("\n第%d个的斐波那契数为%d\n", n, output);

    return 0;
}
