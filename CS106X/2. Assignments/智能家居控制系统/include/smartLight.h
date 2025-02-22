#ifndef SMART_LIGHT_H
#define SMART_LIGHT_H

#include "D:\0.mofei\Code\learning CS\CS106X\2. Assignments\智能家居控制系统\include\device.h"
const int DEFAULT_LIGHT = 50;
const int DEFAULT_COLOR_TEMP = 4000;

class SmartLight : public Device {
private:
    int brightness;
    int colorTemp;  // 添加色温属性

public:
    SmartLight(string deviceId, string name, double power, int brightness = DEFAULT_LIGHT)
        : Device(deviceId, name, power), brightness(brightness), colorTemp(DEFAULT_COLOR_TEMP) {}

    // 重写基类的虚函数
    void turnOn() override;
    void turnOff() override;
    string getStatus() override;
    
    // 智能灯特有的功能
    void setBrightness(int value);
    void setColorTemp(int temp);
    
    // getter方法
    int getBrightness() const { return brightness; }
    int getColorTemp() const { return colorTemp; }
};

#endif // SMART_LIGHT_H