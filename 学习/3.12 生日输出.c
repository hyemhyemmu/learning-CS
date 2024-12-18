#define _CRT_SECURE_NO_WARNINGS
//输入描述：
//输入只有一行，出生日期，包括年月日，年月日之间的数字没有分隔符。
//输出描述：
//三行，第一行为出生年份，第二行为出生月份，第三行为出生日期。输出时如果月份或天数为1位数，需要在1位数前面补0。

#include <stdio.h>

int main()
{
	int year = 0, month = 0, date = 0;
	scanf("%4d%2d%2d", &year, &month, &date);
	printf("year=%d\n", year);
	printf("month=%02d\n", month);
	printf("date=%02d\n", date);

	return 0;
}