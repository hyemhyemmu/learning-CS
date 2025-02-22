#include "D:\0.mofei\Code\learning CS\CS106X\2. Assignments\智能家居控制系统\include\smartLight.h"
#include "D:\0.mofei\Code\learning CS\CS106X\2. Assignments\智能家居控制系统\include\airConditioner.h"

// smartLight
void SmartLight::turnOn() {
    status = true;
    brightness = DEFAULT_LIGHT;
}

void SmartLight::turnOff() {
    status = false;
    brightness = 0;
}

string SmartLight::getStatus() {
    return "SmartLight[" + deviceId + "] " + name + 
           " Status: " + (status ? "ON" : "OFF") + 
           " Brightness: " + to_string(brightness) + "%" +
           " ColorTemp: " + to_string(colorTemp) + "K";
}

void SmartLight::setBrightness(int value) {
    if (value >= 0 && value <= 100) {
        brightness = value;
    }
}

void SmartLight::setColorTemp(int temp) {
    if (temp >= 2700 && temp <= 6500) {
        colorTemp = temp;
    }
}

// airConditioner
void AirConditioner::turnOn() {
    status = true;
}

void AirConditioner::turnOff() {
    status = false;
    temperature = 0;
    windSpeed = 0;
}

string AirConditioner::getStatus() {
    return "AirConditioner[" + deviceId + "] " + name + 
           " Status: " + (status ? "ON" : "OFF") + 
           " Mode: " + mode + 
           " Temperature: " + to_string(temperature) + "°C" + 
           " WindSpeed: " + to_string(windSpeed);
}

void AirConditioner::setMode(string mode) {
    this->mode = mode;
}

void AirConditioner::setTemperature(int temperature) {
    if (temperature >= 16 && temperature <= 30) {
        this->temperature = temperature;
    }
}

void AirConditioner::setWindSpeed(int windSpeed) {
    if (windSpeed >= 1 && windSpeed <= 3) {
        this->windSpeed = windSpeed;
    }
}

void AirConditioner::autostop() {
    if (roomTemperature==TARGET_TEMPERATURE){
        turnOff();
        isAuto = false;
    }
}

void AirConditioner::autoStart() {
    isAuto = true;
    if (roomTemperature<DEFAULT_TEMP_RANGE_LOW||roomTemperature>DEFAULT_TEMP_RANGE_HIGH){
        setMode("Cool");
    } else {
        setMode("Heat");
    }
}


