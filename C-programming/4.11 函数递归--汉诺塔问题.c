#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*函数递归
汉诺塔问题
有三根柱子（A柱、B柱、C柱）和n 个大小不等的圆盘（直径由小到大叠在一起，最小的在最上面）。
最初，所有圆盘都叠在 A 柱上。任务是将所有圆盘按照以下规则移动到 C 柱上：
1. 每次只能移动一个圆盘。
2. 圆盘只能从一个柱子移到另一个柱子上。
3. 在移动过程中，任何时候都必须保持每个柱子上的圆盘按从小到大的顺序排列（即大圆盘不能放在小圆盘上面）。

**目标：** 使用最少的步骤，将所有圆盘从 A 柱移动到 C 柱。
*/

void move(char pos1,char pos2) // function for moving
{
	printf("%c->%c ", pos1, pos2);
}


void hanoi(int n, char pos1, char pos2, char pos3) 
/*
main function for hanoi:
n --> nunmber of plates
pos1 --> starting pos
pos2 --> act as transfer pos
pos3 --> destination pos
*/
{
	if (n == 1)
	{
		move(pos1, pos3); //if only one plate, we can just move it straightforwardly
	}
	else
	{
		hanoi(n - 1, pos1,pos3, pos2); // use hanoi function when need to transit lots of plates at once 
		move(pos1, pos3);
		hanoi(n - 1, pos2, pos1, pos3);
	}
}




int main()
{
	int n = 0;
	char pos1 = 'A';
	char pos2 = 'B';
	char pos3 = 'C';

	printf("How many plates do you have? >");
	while (scanf("%d", &n) != 1) //ensure valid input
	{
		printf("\ninvalid input, try again! >");
		while (getchar() != '\n');
	}
	hanoi(n,pos1,pos2,pos3); //start hanoi!!



	return 0;
}