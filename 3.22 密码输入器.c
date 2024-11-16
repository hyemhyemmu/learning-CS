#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>

int main()
{
	//assume that password is abcdef
	//can only enter 3 times,or the program will auto-stop

	int i = 0;
	{
		char password[100] = { 0 };
		for (i = 0; i < 3; i++)
		{
			printf("Please enter you password:>");
			scanf("%s", password);
			while (getchar() != '\n'); //clear \n right after print anything

			if (strcmp(password, "abcdef") == 0)
			{
				printf("login!");
				break;
			}
			else
			{
				printf("wrong password!\n");
			}
		}

		if (i == 3)
		{
			printf("Exit....You used up all chances!\n");
		}

		return 0;
	}
}