#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME 50
#define DEFAULT_SYS_CAPACITY 10
#define DEFAULT_INC 5


//个人
typedef struct StuInfo
{
	char name[MAX_NAME];
	int stu_num;
	int grade;
}StuInfo;


//系统
typedef struct System
{
	StuInfo* data;
	int count;  //当前学生人数
	int capacity;  //系统容量
}System;

//初始化系统
int Init(System* sys);

//检查系统是否为空
int CheckIfEmpty(System* sys);

//检查容量，必要时扩容
void CheckCapacity(System* sys);

//添加
void AddStu(System* sys);

//查找
int FindByName(const System* sys);


//删除
void DelStu(System* sys);

//查找并展示
void SearchStu(const System* sys);

//退出系统，释放内存
void Exit(System* sys);