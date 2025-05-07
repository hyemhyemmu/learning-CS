#include <stdio.h>
#include <wiringPi.h>
#include <pcf8591.h>
#include <math.h>

#define makerobo_PCF 120 // 基础管脚120
#define makerobo_DOpin 0 // 温度传感器DO管脚

// 打印出温度传感器的提示信息
void makerobo_Print(int x)
{
    switch (x)
    {
    case 0: // 太热
        printf("\n************************\n");
        printf("* Temperature Too Hot! *\n");
        printf("************************\n\n");
        break;
    case 1: // 正合适
        printf("\n***********************\n");
        printf("* Temperature Better~ *\n");
        printf("***********************\n\n");
        break;
    default: // 打印错误信息
        printf("\n**********************\n");
        printf("* Print value error. *\n");
        printf("**********************\n\n");
        break;
    }
}
// 主函数
int main()
{
    // 相关变量定义
    unsigned char T_analogVal;
    double T_Vr, T_Rt, T_temp;
    int T_tmp, T_status;
    // 初始化连接失败时，将消息打印到屏幕
    if (wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed !");
        return 1;
    }
    // 在基本引脚120上设置pcf8591，地址0x48
    pcf8591Setup(makerobo_PCF, 0x48);
    // 设置温度传感器的数字端口（D0）为输入模式
    pinMode(makerobo_DOpin, INPUT);
    // 无限循环函数
    while (1)
    {
        printf("loop"); // 运行循环
        // 把模拟值转换为温度值
        T_analogVal = analogRead(makerobo_PCF + 0);
        T_Vr = 5 * (double)(T_analogVal) / 255;
        T_Rt = 10000 * (double)(T_Vr) / (5 - (double)(T_Vr));
        T_temp = 1 / (((log(T_Rt / 10000)) / 3950) + (1 / (273.15 + 25)));
        T_temp = T_temp - 273.15;
        printf("Current temperature : %lf\n", T_temp);

        T_tmp = digitalRead(makerobo_DOpin); // 读取温度传感器数字管脚

        if (T_tmp != T_status) // 判断状态值发生改变
        {
            makerobo_Print(T_tmp); // 打印出温度传感器的提示信息
            T_status = T_tmp;      // 把当前状态值设置为比较状态值，避免重复打印；
        }
        delay(200); // 延时 200ms
    }
    return 0;
}
