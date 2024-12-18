#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int calculate_score(int base) {  // 接收基础分数作为参数
    int increase = 2;             // 每次增加的量是固定的
    static int bonus = 3;         // 静态变量 bonus，初始为 3，每次调用时保留上次的值

    bonus += 2;                   // 每次调用后加成分数增加 2

    return (base + increase + bonus);  // 返回总分
}

int main() {
    int i;
    int base = 2;                 // 每次关卡的基础分数是固定的 2 分

    // 模拟玩家连续完成 5 个关卡
    for (i = 1; i <= 5; i++) {
        printf("After completing level %d, your score is %d\n", i, calculate_score(base));
    }

    return 0;
}
