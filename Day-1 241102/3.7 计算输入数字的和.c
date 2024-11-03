//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
////练习：编写一个程序，使用 while 循环让用户输入数字，
//// 如果输入为负数，使用 continue 跳过该数字并继续下一次输入，
//// 直到用户输入0为止。程序应在结束时打印正数的总和。
//
//int main()
//{
//	int num = 0,sum=0;
//	
//
//	while (1) //无限循环
//	{
//		printf("Enter a number (0 to stop):");
//		scanf("%d", &num); //提示框放在里面才能无限循环
//		if (num == 0)
//			break;
//		if (num < 0)
//			continue;
//
//		sum += num;
//		
//	}
//	printf("The sum is %d", sum);
//
//
//
//	return 0;
//}