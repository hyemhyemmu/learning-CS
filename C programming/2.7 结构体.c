#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct stu
{
	char name[20];
	int age;
	char sex[6];
	char tel[12];
};

void print(struct stu* ps)
{
	printf("%s %d %s %s\n", ps->name,ps->age,ps->sex,ps->tel);
	printf("%s %d %s %s\n", (*ps).name, (*ps).age, (*ps).sex, (*ps).tel);
}


int main()
{
	struct stu s = { "Lionel Messi",35,"male","13466668888"};
	printf("%s %d %s %s\n", s.name, s.age, s.sex, s.tel);

	print(&s);


	return 0;
}