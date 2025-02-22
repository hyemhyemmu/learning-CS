#include "../include/smartHome.h"
#include "../include/smartLight.h"
#include "../include/airConditioner.h"
#include "../include/curtain.h"
#include <iostream>

int main() {
    // 创建智能家居系统
    SmartHome home;
    
    // 添加设备
    SmartLight* livingRoomLight = new SmartLight("L001", "客厅灯", 50, 80);
    AirConditioner* livingRoomAC = new AirConditioner("AC001", "客厅空调", 2000);
    Curtain* livingRoomCurtain = new Curtain("C001", "客厅窗帘", 100, 0);
    
    home.addDevice(livingRoomLight);
    home.addDevice(livingRoomAC);
    home.addDevice(livingRoomCurtain);
    
    // 创建场景
    Scene* movieMode = new Scene("S001", "观影模式");
    movieMode->addDevice(livingRoomLight, "ON");
    movieMode->addDevice(livingRoomAC, "ON");
    movieMode->addDevice(livingRoomCurtain, "OFF");
    
    home.addScene(movieMode);
    
    // 激活场景
    cout << "激活观影模式..." << endl;
    home.activateScene("S001");
    
    // 显示设备状态
    cout << "\n设备状态：" << endl;
    for (auto device : home.getDevices()) {
        cout << device->getStatus() << endl;
    }
    
    // 显示总功耗
    cout << "\n当前总功耗: " << home.calculateTotalPower() << "W" << endl;
    
    return 0;
}
