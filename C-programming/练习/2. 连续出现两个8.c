#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//Return true if n has two eights in a row

int double_eight(char* str, int length)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if (str[i] && str[i + 1] == '8')
			return 1;
	}
	return 0;
}

int main()
{
	char str[100] = { 0 };
	printf("enter your number:>");
	gets(str);
	int length = strlen(str);
	if (double_eight(str, length))
		printf("Yes,there is two 8 in a row in your number!");
	else
		printf("There isn't two 8 in a row!");
	
	return 0;
}