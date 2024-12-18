#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//不创建临时变量，输出字符串长度

/*
my_strlen("abc")
1+my_strlen("bc")
1+1+my_strlen("c")
1+1+1+my_strlen("")
1+1+1+0
*/


int my_strlen(char* str) //传入的是指针
{

	if (*str != '\0') //解引用，获取指针所代表的具体值
		return 1 + my_strlen(str + 1); //调用下一位开始的地址
	else
		return 0;
}



int main()
{
	char arr[] = "abc";
	int len = my_strlen(arr);
	printf("%d", len);
	return 0;
}