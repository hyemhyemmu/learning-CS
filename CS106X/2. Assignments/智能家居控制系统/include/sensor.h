#ifndef SENSOR_H
#define SENSOR_H

#include "D:\0.mofei\Code\learning CS\CS106X\2. Assignments\智能家居控制系统\include\device.h"

class Sensor : public Device {
private:
    double temperature;
    double humidity;
    double lightLevel;
    
public:
    Sensor(string deviceId, string name, double power)
        : Device(deviceId, name, power), temperature(0), humidity(0), lightLevel(0) {}
        
    void turnOn() override;
    void turnOff() override;
    string getStatus() override;
    
    void updateReadings(double temp, double humid, double light);
    double getTemperature() const { return temperature; }
    double getHumidity() const { return humidity; }
    double getLightLevel() const { return lightLevel; }
};

#endif
