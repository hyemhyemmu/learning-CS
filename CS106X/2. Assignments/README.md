[中文](README.md) | [English](README_en.md)

## 目录：
- 智能家居控制系统
- 继承 string 的 MyString
- 函数对象过滤器
- 字符串操作解析器


## 一、 智能家居控制系统

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
    
    
    return 0;
}
```
--- 

## 二、继承 string 的 MyString
**题目描述：**  
定义一个 `MyString` 类，它继承自 `std::string`，并添加以下功能：  
- 重载 `()` 运算符，使其能够返回子串。  
- 重载 `+` 号运算符，实现 `MyString` 对象间的字符串拼接。  
- 重载 `==` 运算符，比较两个 `MyString` 对象的内容是否相同。  

**要求：**  
- `MyString` 需正确继承 `std::string`，并确保 `std::string` 的所有功能可用。  
- 实现高效的运算符重载，避免不必要的拷贝操作。  
- 提供异常处理机制，确保子串索引合法。  

**考察点：**  
- 继承与构造函数  
- 运算符重载  
- C++ 标准库 `string` 的使用


## 三、函数对象过滤器
**题目描述：**  
实现一个泛型过滤器 `FilterClass`，用于筛选 `vector` 中符合某一范围条件的元素。  

**要求：**  
- `FilterClass` 需要接受两个边界值 `minVal` 和 `maxVal`，筛选出介于两者之间的元素。  
- 过滤操作应支持整数、浮点数等不同类型的数据。  
- 允许 `std::vector<int>` 或 `std::vector<double>` 作为输入，并使用 STL 算法 `std::copy_if` 进行筛选。  
- 过滤逻辑需封装到一个函数对象（仿函数）中，以便与标准库算法配合使用。  

**考察点：**  
- 函数对象（仿函数）  
- STL 算法 `std::copy_if`  
- 泛型编程与模板 

--- 

## 四、函数对象过滤器

**题目描述：**  
设计一个字符串解析器，能够处理 `copy`、`add`、`find`、`rfind` 等操作。  

**要求：**  
- `copy N X L`：从第 `N` 个字符串的 `X` 位置开始，复制长度为 `L` 的子串。  
- `add N S`：将字符串 `S` 追加到第 `N` 个字符串末尾。  
- `find N S`：在第 `N` 个字符串中查找 `S`，返回第一次出现的位置。  
- `rfind N S`：在第 `N` 个字符串中查找 `S`，返回最后一次出现的位置。  
- 解析输入命令，并执行相应的字符串操作。  

**考察点：**  
- `std::string` 的 `substr`、`find`、`rfind`  
- 递归解析输入  
- `stoi()` 处理数字
