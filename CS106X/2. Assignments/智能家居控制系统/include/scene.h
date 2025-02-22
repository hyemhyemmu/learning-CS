#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <map>
#include "device.h"

class Scene {
private:
    string sceneId;
    string name;
    vector<Device*> devices;
    map<Device*, string> actions;

public:
    Scene(string id, string name) : sceneId(id), name(name) {}
    
    void addDevice(Device* device, string action) {
        devices.push_back(device);
        actions[device] = action;
    }
    
    void activate() {
        for (auto device : devices) {
            // 根据action执行相应操作
            if (actions[device] == "ON") device->turnOn();
            else if (actions[device] == "OFF") device->turnOff();
        }
    }
    
    void deactivate() {
        for (auto device : devices) {
            device->turnOff();
        }
    }
    
    string getSceneId() const { return sceneId; }
    string getName() const { return name; }
};

#endif
