#ifndef _CURTAIN_H
#define _CURTAIN_H

#include "D:\0.mofei\Code\learning CS\CS106X\2. Assignments\智能家居控制系统\include\device.h"

class Curtain : public Device{
public:
    Curtain(string deviceId, string name, double power, int openPercent)
        : Device(deviceId, name, power), status(false) {}
    void turnOn() override;
    void turnOff() override;
    string getStatus() override;

private:
    bool isOpen;
    bool status; // open or close
};

#endif