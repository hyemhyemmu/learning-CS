#include <wiringPi.h>
#include <stdio.h>

#define buttonPin 0 
#define redPin 1    
#define greenPin 2  

// 双色LED控制函数
void double_colorLED(char *color)
{
    pinMode(redPin, OUTPUT);   // 设置为输出模式
    pinMode(greenPin, OUTPUT); // 设置为输出模式

    if (color == "RED") // 点亮红色LED灯
    {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
    }
    else if (color == "GREEN") // 点亮绿色LED灯
    {
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
    }
    else
        printf("LED Error");
}

int main(void)
{
    // 初始化连接失败
    if (wiringPiSetup() == -1)
    {
        printf("setup wiringPi failed !");
        return 1;
    }
    // 轻触按键Pin设置为输入模式
    pinMode(buttonPin, INPUT);
    double_colorLED("GREEN");

    while (1)
    {
        // 轻触按键去除抖动处理
        if (0 == digitalRead(buttonPin))
        {              // 按键有按下
            delay(10); // 延时去抖动
            if (0 == digitalRead(buttonPin))
            {
                double_colorLED("RED"); // 点亮红色LED灯
                printf("Button is pressed\n");
            }
        }
        else if (1 == digitalRead(buttonPin))
        { // 没有按键按下亮绿灯
            delay(10);
            if (1 == digitalRead(buttonPin))
            {
                while (!digitalRead(buttonPin))
                    ;
                double_colorLED("GREEN"); // 点亮绿色LED灯
                printf("No Button is pressed\n");
            }
        }
    }
    return 0;
}
