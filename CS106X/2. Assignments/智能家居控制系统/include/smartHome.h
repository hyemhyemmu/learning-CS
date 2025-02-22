#ifndef SMART_HOME_H
#define SMART_HOME_H

#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <string>
#include "device.h"
#include "scene.h"
#include "timer.h"

using namespace std;

class SmartHome {
private:
    vector<Device*> devices;
    vector<Scene*> scenes;
    vector<Timer*> timers;
    double totalPower;
    map<string, vector<string>> userPermissions;
    vector<string> operationLogs;

public:
    SmartHome() : totalPower(0) {}
    
    // 析构函数，清理内存
    ~SmartHome() {
        for (auto device : devices) delete device;
        for (auto scene : scenes) delete scene;
        for (auto timer : timers) delete timer;
    }
    
    // 禁止拷贝构造和赋值操作
    SmartHome(const SmartHome&) = delete;
    SmartHome& operator=(const SmartHome&) = delete;

    // 基本设备和场景管理
    void addDevice(Device* device) {
        if (device) {
            devices.push_back(device);
            logOperation("Added device: " + device->getName());
        }
    }
    
    void removeDevice(const string& deviceId) {
        auto it = find_if(devices.begin(), devices.end(),
            [&deviceId](const Device* d) { 
                return (d != nullptr) ? (d->getDeviceId() == deviceId) : false;
            });
        if (it != devices.end()) {
            Device* device = *it;
            logOperation("Removed device: " + device->getName());
            delete device;
            devices.erase(it);
        }
    }
    
    // 场景管理
    void addScene(Scene* scene) {
        if (scene != nullptr) {
            scenes.push_back(scene);
            logOperation("Added scene: " + scene->getName());
        }
    }
    
    void activateScene(const string& sceneId) const {
        auto it = find_if(scenes.begin(), scenes.end(),
            [&sceneId](const Scene* s) { 
                return (s != nullptr) ? (s->getSceneId() == sceneId) : false;
            });
        if (it != scenes.end()) {
            Scene* scene = *it;
            scene->activate();
            const_cast<SmartHome*>(this)->logOperation("Activated scene: " + scene->getName());
        }
    }
    
    // 能源管理
    double calculateTotalPower() const {
        double power = 0;
        for (const Device* device : devices) {
            if (device != nullptr) {
                if (device->getStatus()) {
                    power += device->getPower();
                }
            }
        }
        const_cast<SmartHome*>(this)->logOperation(
            "Calculated total power: " + to_string(power) + "W");
        return power;
    }
    
    // 定时任务管理
    void addTimer(Timer* timer) {
        timers.push_back(timer);
        logOperation("Added new timer");
    }
    
    void checkTimers() {
        time_t now = time(nullptr);
        for (Timer* timer : timers) {
            if (timer != nullptr) {
                if (timer->shouldRun(now)) {
                    timer->execute();
                    timer->updateNextRun();
                }
            }
        }
    }
    
    // 用户权限管理
    void addUser(const string& userId, const vector<string>& permissions) {
        userPermissions[userId] = permissions;
        logOperation("Added user: " + userId);
    }
    
    bool checkPermission(const string& userId, const string& operation) {
        auto userIt = userPermissions.find(userId);
        if (userIt == userPermissions.end()) {
            logOperation("Permission denied for user: " + userId);
            return false;
        }
        const vector<string>& permissions = userIt->second;
        return find(permissions.begin(), permissions.end(), operation) != permissions.end();
    }
    
    // 操作日志
    void logOperation(const string& operation) {
        time_t now = time(nullptr);
        string timestamp = ctime(&now);
        timestamp = timestamp.substr(0, timestamp.length() - 1); // 移除换行符
        operationLogs.push_back(timestamp + ": " + operation);
    }
    
    // Getters with null checks
    Device* getDevice(const string& deviceId) const {
        auto it = find_if(devices.begin(), devices.end(),
            [&deviceId](const Device* d) { 
                return (d != nullptr) ? (d->getDeviceId() == deviceId) : false;
            });
        return it != devices.end() ? *it : nullptr;
    }

    const vector<Device*>& getDevices() const { return devices; }
    const vector<Scene*>& getScenes() const { return scenes; }
    const vector<string>& getLogs() const { return operationLogs; }
};

#endif
