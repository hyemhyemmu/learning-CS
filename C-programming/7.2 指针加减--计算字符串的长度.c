#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//1.传统的直接判断法
int mystrlen1(char* str) 
{
	int count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}


//2. 递归的版本
int mystrlen2(char* str)
{
	/*	mystrlen("abc")
		1+mystrlen("bc")
		1+1+mystrlen("c")
		1+1+1+mystrlen("")
		1+1+1+0
	*/

	if (*str != '\0')
		return 1 + mystrlen2(str + 1);
	else
		return 0;
}

//3. 指针减法计算
int mystrlen3(char* str)
{
	char* start = str; 
	while (*str != '\0')
	{
		str++;
	}
	return str - start;
}


int main()
{
	int len_1 = mystrlen1("abcdef");
	int len_2 = mystrlen2("abcdef");
	int len_3 = mystrlen3("abcdef");

	printf("%d\n%d\n%d", len_1, len_2, len_3);

	return 0;
}