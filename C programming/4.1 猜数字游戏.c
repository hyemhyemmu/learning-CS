#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu()
{
	printf("***********************\n");
	printf("*****  1.play  0.exit  *****\n");
	printf("***********************\n");
}


void game() //generate random number, then let the user to guess
{
	int ran = rand() % 100 + 1;
	int guess = 0;
	printf("Guess:>");
	scanf("%d", &guess); //get the number
	while (getchar() != '\n');

	do
	{
		if (guess < ran) 
		{
			printf("Too small! Try Again:\n");
		}
		else if (guess > ran)
		{
			printf("Too big! Try Again:\n");
		}
		else
		{
			printf("Congrate!!! You made it!!\n");
			break;
		}
		scanf("%d", &guess);
		while (getchar() != '\n'); 
		
	} while (1);
	
	
}

int main()
{
	int choice = 0;
	srand((unsigned int)time(NULL)); //set a starting point for random num.
	do  //show the menu first for choosing
	{
		
		menu();
		printf("Choose your next step:>");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("Guess numbers!\n");
			game(); //start the game
			break;
		case 0:
			printf("see you again...\n");
			break; 
		default:
			printf("You choose the wrong num! Try again\n");
		}
		break;
	} while (choice!=0); //allow user to try infinite time unless exit
	


	return 0;
}