#ifndef _AIRCONDITIONER_H_
#define _AIRCONDITIONER_H_
#include "device.h"

const int TARGET_TEMPERATURE = 25;
const int DEFAULT_TEMP_RANGE_LOW=19;
const int DEFAULT_TEMP_RANGE_HIGH=30;
const int DEFAULT_WIND_SPEED=1;

class AirConditioner : public Device {
public:
    AirConditioner(string id, string name, int power, string status, string mode,int roomTemperature)
        :Device(id, name, power), mode(mode),roomTemperature(roomTemperature){
            this->temperature = TARGET_TEMPERATURE;
            this->windSpeed = DEFAULT_WIND_SPEED;
            this->isAuto = false;
        }
    void setMode(string mode);
    void setTemperature(int temperature);
    void setWindSpeed(int windSpeed);

    string getStatus();
    void turnOn();
    void turnOff();
    void autostop();
    void autoStart();


private:
    string mode;
    int temperature;
    int windSpeed;
    int roomTemperature;
    bool isAuto;
};

#endif