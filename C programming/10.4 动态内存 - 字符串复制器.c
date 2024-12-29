#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//字符串复制器
//要求：编写一个函数，接受一个字符串作为输入，动态分配内存来存储这个字符串的副本，
//并返回指向新字符串的指针。
//注意处理内存分配失败的情况。

#define MAX_INPUT 100

char* stringDup(const char* str)
{
	//传入的可能是空指针
	if (str == NULL)
	{
		return NULL;
	}

	//开辟内存
	int len = strlen(str) + 1;
	char* new_pstr = (char*)malloc(len * sizeof(char));

	//验证可行性
	if (new_pstr == NULL)
	{
		return NULL;
	}

	//复制字符串
	strcpy(new_pstr, str);
	return new_pstr;
}


int main()
{
	char str[MAX_INPUT];
	printf("请输入你想要存储的字符串（最多100个字符哦）:>");
	//接受字符并去除换行符
	fgets(str, MAX_INPUT, stdin);
	str[strcspn(str, "\n")] = 0;

	//主行为函数
	char* new_pstr=stringDup(str);

	if (new_pstr == NULL)
	{
		printf("复制失败！");
		return 1;
	}
	
	//输出
	printf("原始字符串：%s\n", str);
	printf("复制的字符串：%s\n", new_pstr);

	free(new_pstr);
	new_pstr = NULL;
	return 0;
}
