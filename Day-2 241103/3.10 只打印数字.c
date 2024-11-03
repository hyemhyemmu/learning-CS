#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//only print numbers
int main()
{
	char ch = '0';
	while ((ch = getchar()) != EOF)
	{
		if (ch < '0' || ch>'9')
			continue;
		putchar(ch);
	}

	return 0;
}