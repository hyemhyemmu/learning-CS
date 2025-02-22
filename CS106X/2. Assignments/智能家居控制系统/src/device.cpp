#include "../include/device.h"
#include "../include/smartLight.h"
#include "../include/airConditioner.h"
#include "../include/curtain.h"

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
    temperature_ = 0;
    windSpeed_ = 0;
}

string AirConditioner::getStatus() {
    return "AirConditioner[" + deviceId + "] " + name + 
           " Status: " + (status ? "ON" : "OFF") + 
           " Mode: " + modeToString(mode_) + 
           " Temperature: " + to_string(temperature_) + "°C" + 
           " WindSpeed: " + to_string(windSpeed_);
}

void AirConditioner::setMode(Mode mode) {
    mode_ = mode;
}

void AirConditioner::setTemperature(int temperature) {
    if (isValidTemperature(temperature)) {
        temperature_ = temperature;
    }
}

void AirConditioner::setWindSpeed(int windSpeed) {
    if (isValidWindSpeed(windSpeed)) {
        windSpeed_ = windSpeed;
    }
}

void AirConditioner::autoStop() {
    if (roomTemperature_ == TARGET_TEMPERATURE) {
        turnOff();
        isAuto_ = false;
    }
}

void AirConditioner::autoStart() {
    isAuto_ = true;
    if (roomTemperature_ < DEFAULT_TEMP_RANGE_LOW) {
        setMode(Mode::HEAT);
    } else if (roomTemperature_ > DEFAULT_TEMP_RANGE_HIGH) {
        setMode(Mode::COOL);
    }
}

bool AirConditioner::isValidTemperature(int temp) const {
    return temp >= DEFAULT_TEMP_RANGE_LOW && temp <= DEFAULT_TEMP_RANGE_HIGH;
}

bool AirConditioner::isValidWindSpeed(int speed) const {
    return speed >= 1 && speed <= 3;
}

string AirConditioner::modeToString(Mode mode) const {
    switch (mode) {
        case Mode::COOL: return "Cool";
        case Mode::HEAT: return "Heat";
        case Mode::AUTO: return "Auto";
        case Mode::DRY: return "Dry";
        case Mode::FAN: return "Fan";
        default: return "Unknown";
    }
}


// curtain
void Curtain::turnOn() {
    status = true;
}

void Curtain::turnOff() {
    status = false;
}

string Curtain::getStatus() {
    return "Curtain[" + deviceId + "] " + name + 
           " Status: " + (status ? "ON" : "OFF");
}

// device
Device::Device(string deviceId, string name, double power) {
    this->deviceId = deviceId;
    this->status = false;
    this->name = name;
    this->power = power;
}


