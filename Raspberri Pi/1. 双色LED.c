#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define unchar unsigned char
#define redPin 0
#define greenPin 1

// LED初始化
void ledInit()
{
    softPwmCreate(redPin, 0, 100);
    softPwmCreate(greenPin, 0, 100);
}

// 设置LED亮度 调节范围是0x00-0xff
void colorSet(unchar r_val, unchar g_val)
{
    softPwmWrite(redPin, r_val);
    softPwmWrite(greenPin, g_val);
}

// 主程序
int main()
{
    if (wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed");
        return 1;
    }

    ledInit();

    while (1)
    {
        colorSet(0xff, 0x00);
        delay(500);
        colorSet(0x00, 0xff); 
        delay(500);
        colorSet(0xff, 0x45);
        delay(500);
        colorSet(0xff, 0xff);
        delay(500);
        colorSet(0x7c, 0xfc);
        delay(500);
    }
}