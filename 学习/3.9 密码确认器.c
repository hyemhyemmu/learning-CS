//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
//int main()
//{
//	char password[100] = { 0 };
//	int ch = 0,result=0;
//
//	while (1)
//	{
//		printf("请输入密码：> ");
//		scanf("%s", password);
//		while ((ch = getchar()) != '\n' && ch != EOF); //清除缓冲区中的\n和EOF
//
//		printf("请确认密码(Y/N):>  %s\n", password);
//		result = getchar();
//		while ((ch = getchar()) != '\n' && ch != EOF); //好习惯！get完就清空缓存区
//
//		if (result == 'Y')
//		{
//			printf("已保存，谢谢！");
//			break;
//		}
//		else if(result == 'N')
//		{
//			printf("请重新输入！");
//		}
//		else
//		{
//			printf("输入错误，只能输入Y/N。");
//		}
//
//		
//	}
//	return 0;
//}