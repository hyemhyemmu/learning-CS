#ifndef DEVICE_H
#define DEVICE_H

#include <string>
using namespace std;

class Device {
protected:  // 允许子类访问这些成员
    string deviceId;
    string name;
    bool status;    // 开/关状态
    double power;   // 功率

public:
    // 构造函数声明
    Device(string deviceId, string name, double power);
    
    // 虚析构函数
    virtual ~Device() = default;
    
    // 纯虚函数声明
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual string getStatus() = 0;

    // getter 方法
    string getDeviceId() const { return deviceId; }
    string getName() const { return name; }
    bool getStatus() const { return status; }
    double getPower() const { return power; }
};


// constructor
Device::Device(string deviceId, string name, double power){
    this->deviceId = deviceId;
    this->status = false;
    this->name = name;
    this->power = power;
}
#endif // DEVICE_H

