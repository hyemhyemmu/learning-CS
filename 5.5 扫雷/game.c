#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set; //初始化棋盘
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("------扫雷游戏-----\n");
	
	for (j = 0; j <= col; j++) //打印列号
	{
		printf("%d ", j);
	}
	printf("\n");

	for (i = 1; i <= row; i++) //这里的打印是从1开始，到row结束，因为第0行和第0列是空的
	{	
		printf("%d ", i); //打印行号
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("------扫雷游戏-----\n");
}	

void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = EASY_COUNT;
	int i = 0, j = 0;
	while (count) //只要雷的个数没到就进入循环
	{
		i = rand() % row + 1; //+1是因为得到的是0-8，但我们要1-9
		j = rand() % col + 1;

		if (board[i][j] == '0') //首先判断点位是否被布置过
		{
			board[i][j] = '1';
			count--;
		}
	}
}

int get_mine_count(char board[ROWS][COLS], int x, int y)
{
	return (board[x - 1][y] + board[x - 1][y - 1] + board[x - 1][y + 1] + board[x][y - 1] + board[x][y + 1] + board[x + 1][y - 1] + board[x + 1][y] + board[x + 1][y + 1] - 8 * '0');
}

void Expand(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y)
{
	// 如果超出边界、已经被显示或者有雷，则停止展开
	if (x < 1 || x > row || y < 1 || y > col || show[x][y] != '*')
		return;

	// 获取当前格子周围雷的数量
	int count = get_mine_count(mine, x, y);
	if (count > 0)
	{
		// 如果周围有雷，显示雷的数量并停止递归
		show[x][y] = count + '0'; // 转换为字符
		return;
	}

	// 如果周围没有雷，将当前格子标记为空格并递归展开
	show[x][y] = ' ';

	// 递归检查周围的 8 个格子
	Expand(mine, show, row, col, x - 1, y - 1);
	Expand(mine, show, row, col, x - 1, y);
	Expand(mine, show, row, col, x - 1, y + 1);
	Expand(mine, show, row, col, x, y - 1);
	Expand(mine, show, row, col, x, y + 1);
	Expand(mine, show, row, col, x + 1, y - 1);
	Expand(mine, show, row, col, x + 1, y);
	Expand(mine, show, row, col, x + 1, y + 1);
}




void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0, y = 0;
	int win = 0;
	

	while (win<row*col-EASY_COUNT)
	{
		printf("请输入要排查的坐标:> ");
		scanf("%d %d", &x, &y);
		while (getchar() != '\n');
		if (x >= 1 && x <= row && y >= 1 && y <= col) //检查是否越界
		{
			if (mine[x][y] == '1')  //踩中地雷
			{
				printf("踩中地雷了！！\n");
				printf("看看地雷都在哪里吧：\n");
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else if (show[x][y] != '*') //已经排查过了
				printf("这个位置已经排查过了！\n");
			else  //没踩中地雷 //重要的点在于里面存放的是字符的ASCII值，因此不能直接相加。但由于1和0的ASCII值恰好相差1，因此可以考虑字符相减
			{
				win++; //没踩中地雷就可以认为次数+1
				int count = get_mine_count(mine, x, y);
				if (count > 0)//如果周围有雷，那么就要展示周围雷的个数
				{
					show[x][y] = count + '0'; //巧妙地将数字转换为字符（ASCII码）
					
				}
				else if(count==0) //周围没有雷，就要展开一片
				{
					Expand(mine, show, row, col, x, y);
				}
				DisplayBoard(show, ROW, COL); //选择在每一次排查后展示棋盘
			
			}
		}
		else
			printf("\n输入错误!");
	}
	if (win == row * col - EASY_COUNT)
	{
		printf("恭喜你，排雷成功！\n");
		DisplayBoard(mine, ROW, COL);
	}
		
	
}