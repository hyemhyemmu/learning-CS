[中文](README.md) | [English](README_en.md)

## Contents:
- Smart Home Control System
- MyString Inheriting from string
- Function Object Filter
- String Operation Parser


## I. Smart Home Control System

## Project Background
Design a smart home control system that can manage and control various smart devices in the home to achieve automated control and scene linkage.

## Core Concepts
1. **Device Abstraction**: Unified management of different types of devices
2. **Scene Linkage**: Collaborative work between multiple devices
3. **Scheduled Tasks**: Timed control of devices
4. **Energy Management**: Device power monitoring and optimization
5. **User Interaction**: Multi-user permission management

## Detailed Requirements

### 1. Basic Device Class Design
```cpp
class Device {
    string deviceId;
    string name;
    bool status;  // On/Off status
    double power; // Power consumption
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual string getStatus() = 0;
};
```

### 2. Concrete Device Classes
- Smart Light (brightness, color temperature)
- Air Conditioner (temperature, mode, fan speed)
- Curtains (opening degree)
- Door Lock (password, access records)
- Sensors (temperature, humidity, light, etc.)

### 3. Scene Class Design
```cpp
class Scene {
    string sceneId;
    string name;
    vector<Device*> devices;
    map<Device*, string> actions; // Device-action mapping
    void activate();
    void deactivate();
};
```

### 4. Core Functionality Requirements
1. **Device Management**
   - Add/Remove devices
   - Device status query
   - Device group management
   
2. **Scene Linkage**
   - Custom scenes (e.g., Home mode, Away mode, Movie mode)
   - Condition triggers (e.g., AC turns on when temperature > 26°C)
   - Device linkage (e.g., lights turn on after door opens)

3. **Schedule Management**
   - Device timing switches
   - Scene timing activation
   - Periodic tasks

4. **Energy Management**
   - Real-time power consumption monitoring
   - Power usage statistics analysis
   - Energy-saving suggestions

5. **Security Mechanism**
   - User permission control
   - Exception handling
   - Operation logging

### Advanced Requirements
1. **AI Learning Features**
   - Record user habits
   - Automatic scene adjustment
   - Smart suggestions


### Sample Code
```cpp
int main() {
    SmartHome home;
    
    // Add devices
    SmartLight* livingRoomLight = new SmartLight("L001", "Living Room Light");
    SmartAC* bedRoomAC = new SmartAC("AC001", "Bedroom AC");
    home.addDevice(livingRoomLight);
    home.addDevice(bedRoomAC);
    
    // Create scene
    Scene* movieMode = new Scene("S001", "Movie Mode");
    movieMode->addAction(livingRoomLight, "brightness:20");
    movieMode->addAction(bedRoomAC, "temp:24,mode:silent");
    
    return 0;
}
```
--- 

## II. MyString Inheriting from string
**Problem Description:**  
Define a `MyString` class that inherits from `std::string` and adds the following features:  
- Overload the `()` operator to return a substring.  
- Overload the `+` operator for string concatenation between `MyString` objects.  
- Overload the `==` operator to compare the content of two `MyString` objects.  

**Requirements:**  
- `MyString` should properly inherit from `std::string` and ensure all `std::string` functionality is available.  
- Implement efficient operator overloading, avoiding unnecessary copy operations.  
- Provide exception handling to ensure substring indices are valid.  

**Key Points:**  
- Inheritance and constructors  
- Operator overloading  
- Using C++ standard library `string`


## III. Function Object Filter
**Problem Description:**  
Implement a generic filter `FilterClass` to select elements from a `vector` that meet certain range conditions.  

**Requirements:**  
- `FilterClass` should accept two boundary values `minVal` and `maxVal` to filter elements between them.  
- The filtering operation should support different data types like integers and floating-point numbers.  
- Accept `std::vector<int>` or `std::vector<double>` as input and use STL algorithm `std::copy_if` for filtering.  
- Filtering logic should be encapsulated in a function object (functor) for use with standard library algorithms.  

**Key Points:**  
- Function objects (functors)  
- STL algorithm `std::copy_if`  
- Generic programming and templates 

--- 

## IV. String Operation Parser

**Problem Description:**  
Design a string parser that can handle operations like `copy`, `add`, `find`, and `rfind`.  

**Requirements:**  
- `copy N X L`: Copy a substring of length `L` starting from position `X` in the Nth string.  
- `add N S`: Append string `S` to the end of the Nth string.  
- `find N S`: Find string `S` in the Nth string, return the first occurrence position.  
- `rfind N S`: Find string `S` in the Nth string, return the last occurrence position.  
- Parse input commands and execute corresponding string operations.  

**Key Points:**  
- `std::string`'s `substr`, `find`, `rfind`  
- Recursive input parsing  
- Using `stoi()` for number processing
