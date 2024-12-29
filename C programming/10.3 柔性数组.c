#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct s
{
	int n;
	int arr[]; //ÈáÐÔÊý×é
};


int main()
{
	struct s* ps = (struct s*)malloc(sizeof(struct s) + 40);
	if (ps == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}
	ps->n = 100;
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		ps->arr[i] = i;
		printf("%d ", ps->arr[i]);
	}

	struct s* pstr = (struct s*)realloc(ps, sizeof(struct s) + 80);
	if (pstr == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}
	ps = pstr;


	free(ps);
	ps = NULL;


	return 0;
}