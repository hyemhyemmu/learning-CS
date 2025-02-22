# 智能家居控制系统设计

## 项目背景
设计一个智能家居控制系统，能够管理和控制家中的各种智能设备，实现自动化控制和场景联动。

## 核心概念
1. **设备抽象**：不同类型设备的统一管理
2. **场景联动**：多个设备之间的协同工作
3. **定时任务**：设备的定时控制
4. **能源管理**：设备用电监控和优化
5. **用户交互**：多用户权限管理

## 详细要求

### 1. 基础设备类设计
```cpp
class Device {
    string deviceId;
    string name;
    bool status;  // 开/关状态
    double power; // 功率
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual string getStatus() = 0;
};
```

### 2. 具体设备类
- 智能灯（亮度、色温）
- 空调（温度、模式、风速）
- 窗帘（开合度）
- 门锁（密码、开关记录）
- 传感器（温度、湿度、光照等）

### 3. 场景类设计
```cpp
class Scene {
    string sceneId;
    string name;
    vector<Device*> devices;
    map<Device*, string> actions; // 设备-动作映射
    void activate();
    void deactivate();
};
```

### 4. 核心功能要求
1. **设备管理**
   - 添加/删除设备
   - 设备状态查询
   - 设备分组管理
   
2. **场景联动**
   - 自定义场景（如：回家模式、离家模式、电影模式）
   - 条件触发（如：温度>26℃时自动开空调）
   - 设备联动（如：开门后自动开灯）

3. **定时管理**
   - 设备定时开关
   - 场景定时激活
   - 周期性任务

4. **能源管理**
   - 实时功耗监控
   - 用电统计分析
   - 节能建议

5. **安全机制**
   - 用户权限控制
   - 异常情况处理
   - 操作日志记录

### 进阶要求
1. **AI学习功能**
   - 记录用户习惯
   - 自动调整场景
   - 智能建议

2. **远程控制**
   - 网络通信接口
   - 设备状态推送
   - 远程操作验证

### 示例代码
```cpp
int main() {
    SmartHome home;
    
    // 添加设备
    SmartLight* livingRoomLight = new SmartLight("L001", "客厅灯");
    SmartAC* bedRoomAC = new SmartAC("AC001", "卧室空调");
    home.addDevice(livingRoomLight);
    home.addDevice(bedRoomAC);
    
    // 创建场景
    Scene* movieMode = new Scene("S001", "观影模式");
    movieMode->addAction(livingRoomLight, "brightness:20");
    movieMode->addAction(bedRoomAC, "temp:24,mode:silent");
    
    // 触发场景
    home.activateScene(movieMode);
    
    // 能源统计
    home.printEnergyReport();
    
    return 0;
}
```

## 设计建议
1. 使用工厂模式创建不同类型的设备
2. 使用观察者模式实现设备状态变化通知
3. 使用命令模式实现场景控制
4. 使用策略模式实现不同的节能策略
5. 考虑使用单例模式管理核心控制器


