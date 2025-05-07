#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>

#define PCF 120 // 基础管脚120

int main(void)
{
    int res, tmp, status; // 定义状态值、缓冲值和当前值变量
    wiringPiSetup();      // wiringPi初始化
    //  在基本引脚120上设置pcf8591，地址0x48
    pcf8591Setup(PCF, 0x48);
    status = 0; // 设置默认状态值为0

    while (1)
    {
        res = analogRead(PCF);                                     // 获取AIN0 的模拟量值；
        printf("Current intensity of magnetic field : %d\n", res); // 打印出磁场的电流强度值
        if (res - 133 < 5 || res - 133 > -5)                       // 判断磁场强度范围
            tmp = 0;                                               // 没有磁场
        if (res < 128)
            tmp = -1; // 磁场强度为北
        if (res > 138)
            tmp = 1;       // 磁场强度为南
        if (tmp != status) // 磁场发生改变
        {
            switch (tmp) // 磁场判断
            {
            case 0: // 没有磁场
                printf("\n*****************\n");
                printf("* Magnet: None. *\n");
                printf("*****************\n\n");
                break;
            case -1: // 磁场为北
                printf("\n******************\n");
                printf("* Magnet: North. *\n");
                printf("******************\n\n");
                break;
            case 1: // 磁场为南
                printf("\n******************\n");
                printf("* Magnet: South. *\n");
                printf("******************\n\n");
                break;
            }
            status = tmp; // 把当前状态值设置为比较状态值，避免重复打印；
        }
        delay(200); // 延时200ms
    }
    return 0;
}
