#ifndef _AIRCONDITIONER_H_
#define _AIRCONDITIONER_H_
#include "device.h"

// 将常量定义移到类内部作为静态成员
class AirConditioner : public Device {
public:
    static const int TARGET_TEMPERATURE = 25;
    static const int DEFAULT_TEMP_RANGE_LOW = 19;
    static const int DEFAULT_TEMP_RANGE_HIGH = 30;
    static const int DEFAULT_WIND_SPEED = 1;
    
    enum class Mode {
        COOL,
        HEAT,
        AUTO,
        DRY,
        FAN
    };

public:
    AirConditioner(string id, string name, int power, Mode mode = Mode::AUTO, 
                  int roomTemperature = TARGET_TEMPERATURE)
        : Device(id, name, power)
        , mode_(mode)
        , roomTemperature_(roomTemperature)
        , temperature_(TARGET_TEMPERATURE)
        , windSpeed_(DEFAULT_WIND_SPEED)
        , isAuto_(false) {}

    // Getters
    Mode getMode() const { return mode_; }
    int getTemperature() const { return temperature_; }
    int getWindSpeed() const { return windSpeed_; }
    int getRoomTemperature() const { return roomTemperature_; }
    bool isAutoMode() const { return isAuto_; }

    // Setters
    void setMode(Mode mode);
    void setTemperature(int temperature);
    void setWindSpeed(int windSpeed);
    void setRoomTemperature(int temp);

    // 重写基类虚函数
    string getStatus() override;
    void turnOn() override;
    void turnOff() override;

    // 自动控制相关
    void autoStop();
    void autoStart();

private:
    Mode mode_;
    int temperature_;
    int windSpeed_;
    int roomTemperature_;
    bool isAuto_;
    
    // 辅助函数
    bool isValidTemperature(int temp) const;
    bool isValidWindSpeed(int speed) const;
    string modeToString(Mode mode) const;
};

#endif