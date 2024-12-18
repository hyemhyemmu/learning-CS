#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*项目说明：数字炸弹游戏
游戏规则：
系统随机生成一个数字炸弹（例如 1-100）。
玩家轮流猜测这个数字。(1-4人)
每次玩家输入一个数字：
如果数字太大或太小，提示玩家。
如果玩家猜中了，系统宣布谁获胜。
如果猜测次数超过限制（例如 10 次），游戏自动结束，并显示答案。
游戏结束后，玩家可以选择重新开始或退出。*/

void menu()
{
	printf("******************************\n");
	printf("***** 1. Play  0. Exit  ******\n");
	printf("******************************\n");
}

void game()
{
	int players = 1;
	int turn = 1;
	int maxGuesses = 10;
	int guess = 0;
	int currentplayer = 1;
	printf("How many players do you have?>");
	while (scanf("%d", &players) != 1 || players < 1 || players>4)
	{
		printf("Invalid input. Try again!");
		while (getchar() != '\n');
	} //ensure valid input

	int num = rand() % 100 + 1; //generate random #bombs

	printf("A random bomb number has been generated (1-100). Guess it!\n");

	for (turn = 1; turn <= maxGuesses; turn++)
	{
        printf("Player %d, What is your guess:>", currentplayer);
		while (scanf("%d", &guess) != 1 || guess < 1 || guess>100)
		{
			printf("invalid input. try again!");
			while (getchar() != '\n');
		}

		if (guess > num)
		{
			printf("Too big!\n");
		}
		else if (guess < num)
		{
			printf("Too small!\n");
		}
		else
		{
			printf("Congrats! Player #%d, You made it!\n",currentplayer);
			return; //exit game
		}

		currentplayer = (currentplayer + 1) % players;
	}
	printf("out of chance! The bomb was %d. Game over!\n", num);

}

int main()
{
	srand((unsigned int)time(NULL)); //initial for rand
		int choice = 0;
	
	do // as least display menu once, will exit when input 0
	{
		menu();
		printf("Choose next step:>");
		while (scanf("%d", &choice) != 1 || (choice != 0 && choice != 1)) //ensure valid input
			{
				printf("Invalid input. Enter again!");
				while (getchar() != '\n'); //clear buffer
			}

		switch (choice)
		{
		case 1:
			printf("Let's start!");
			game();
			break;
		case 0:
			printf("Goodbye!");
			return;
		}

			
	} while (choice != 0);

	return 0;
}