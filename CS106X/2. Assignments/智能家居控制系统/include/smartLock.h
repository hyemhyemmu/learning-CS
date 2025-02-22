#ifndef SMART_LOCK_H
#define SMART_LOCK_H

#include "device.h"
#include <vector>
#include <ctime>

class SmartLock : public Device {
private:
    string password;
    vector<pair<time_t, bool>> accessLog; // 记录开关时间和状态

public:
    SmartLock(string deviceId, string name, double power, string initPassword)
        : Device(deviceId, name, power), password(initPassword) {}

    void turnOn() override;
    void turnOff() override;
    string getStatus() override;
    
    bool verifyPassword(string inputPassword);
    void changePassword(string oldPassword, string newPassword);
    vector<pair<time_t, bool>> getAccessLog() const { return accessLog; }
};

#endif
