//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
////练习题 1：跳过偶数的求和
////编写一个程序，使用 while 循环从1到10遍历数字，跳过偶数，只打印奇数，并计算奇数的和。
//int main()
//{
//	int i = 1, sum = 0;
//	while (i <= 10)
//	{
//		
//		if (i % 2 == 0)
//		{
//			i++; //不能在判断之前就加1是因为会导致最后结果出现11
//			continue;
//		}
//
//		sum += i;
//		printf("%d\n", i);
//		i++;//打印之后再加1
//	}
//	printf("%d\n", sum);
//
//
//	return 0;
//}