#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
 假设你在一个 n × m 的迷宫中，需要从左上角的起点（坐标 (0, 0)）
 走到右下角的终点（坐标 (n-1, m-1)）。
 你只能向下或向右移动，并且不能走出迷宫的边界。
 请你写一个递归函数，求从起点到终点有多少种不同的路径。

具体要求：
输入：迷宫的大小 m × n，其中 n 和 m 都为正整数。
输出：从起点到终点的路径数量。
*/


//f(m,n)=f(m-1,n)+f(m,n-1)
int route(int m, int n)
{
	if (m==1||n==1) 
	{
		return 1;
	}

	else
	{
		return route(m - 1, n) + route(m, n - 1);
	}

}




int main()
{
	int m = 0, n = 0;
	int output = 0;
	printf("How big? >");
	while (scanf("%d %d", &m, &n) != 2 || m <= 0||n<=0)
	{
		printf("invalid input!");
		while (getchar() != '\n');
	} //ensure valid input

	output = route(m, n);
	printf("%d", output);


	return 0;
}