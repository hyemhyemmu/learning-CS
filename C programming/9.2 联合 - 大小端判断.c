#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//常规
//int check_sys()
//{
//	int a = 1;
//	return *(char*)&a;
//}

//联合
int check_sys()
{
	union
	{
		char a;
		int b;
	}u;
	
	u.b = 1;
	return u.a;
}



int main()
{
	int ret = check_sys();
	if (ret == 1)
		printf("小端\n");
	else
		printf("大端\n");
	return 0;
}