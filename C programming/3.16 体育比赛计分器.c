#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
/*你正在为一个体育赛事编写一个计分程序。在这个赛事中，每次运动员完成一项比赛项目时，会获得一定的分数。每个项目的分数分为两个部分：

基本得分：每次比赛，运动员都会获得固定的 5 分。
累积得分：每次运动员完成项目后，累积得分会增加，初始值为 10，每次完成一个项目后累积得分增加 3 分。
要求：
编写一个 calculate_total_score 函数，计算每次运动员完成比赛后的总得分。
使用 static 变量来存储 累积得分，保证每次项目完成时累积得分增加，直到所有项目完成。
在 main 函数中使用一个循环模拟运动员连续完成 6 个项目，输出每次完成项目后的总得分。*/

int calculate_total_score(int base)
{
	int basic = 5;
	static int bonus = 10;

	bonus += 3;
	return(base + basic + bonus);
}



int main()
{
	int i;
	int base = 0;

	for (i = 1; i < 7; i++)
	{
		printf("After completing level %d,your score is %d\n", i, calculate_total_score(base));
	}
}