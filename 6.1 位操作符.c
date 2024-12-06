#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int a = 8; // 00001000 (8)
	int a_1 = a << 1; // 00010000 (16)
	int a_2 = a >> 1; // 00000100 (4)
	printf("a= %d, a_1= %d, a_2= %d",a, a_1, a_2);

	printf("\n");

	int b = 7; //00000111 (7)
	int b_1 = b << 1; //00001110 (14)
	int b_2 = b >> 1; //00000011 (3)
	printf("b= %d, b_1= %d, b_2= %d",b, b_1, b_2);

	printf("\n");

	int c = -3; //原码：10000011 (-3) 补码：11111101
	int c_1 = c << 1; //补码：1111010 反码：1111001 原码：1000110 (-6) 相当与原码直接左移！
	int c_2 = c >> 1; //补码：1111110 反码：1111101 原码：1000010 (-2) 这里就不相当于原码直接右移了，所以需要注意
	printf("c= %d, c_1= %d, c_2= %d", c, c_1, c_2);

	printf("\n");


	return 0;
}