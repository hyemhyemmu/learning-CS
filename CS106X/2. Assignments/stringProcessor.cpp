#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class StringProcessor {
private:
    std::vector<std::string> strings;

public:
    // 构造函数，初始化字符串存储
    StringProcessor() {
        strings.push_back("");  // 添加一个空字符串作为首位
    }

    // 执行复制操作
    std::string copy(size_t N, size_t X, size_t L) {
        if (N >= strings.size()) {
            throw std::out_of_range("Invalid string index");
        }
        return strings[N].substr(X, L);
    }

    // 执行添加操作
    void add(size_t N, const std::string& S) {
        if (N >= strings.size()) {
            throw std::out_of_range("Invalid string index");
        }
        strings[N] += S;
    }

    // 执行查找操作
    size_t find(size_t N, const std::string& S) {
        if (N >= strings.size()) {
            throw std::out_of_range("Invalid string index");
        }
        return strings[N].find(S);
    }

    // 执行反向查找操作
    size_t rfind(size_t N, const std::string& S) {
        if (N >= strings.size()) {
            throw std::out_of_range("Invalid string index");
        }
        return strings[N].rfind(S);
    }

    // 添加新字符串
    void addString(const std::string& str) {
        strings.push_back(str);
    }

    // 处理命令
    std::string processCommand(const std::string& command) {
        std::istringstream iss(command);
        std::string operation;
        iss >> operation;

        try {
            if (operation == "copy") {
                size_t N, X, L;
                iss >> N >> X >> L;
                return copy(N, X, L);
            }
            else if (operation == "add") {
                size_t N;
                std::string S;
                iss >> N;
                std::getline(iss >> std::ws, S);
                add(N, S);
                return "Added successfully";
            }
            else if (operation == "find") {
                size_t N;
                std::string S;
                iss >> N;
                std::getline(iss >> std::ws, S);
                size_t pos = find(N, S);
                return pos == std::string::npos ? "Not found" : std::to_string(pos);
            }
            else if (operation == "rfind") {
                size_t N;
                std::string S;
                iss >> N;
                std::getline(iss >> std::ws, S);
                size_t pos = rfind(N, S);
                return pos == std::string::npos ? "Not found" : std::to_string(pos);
            }
            else {
                return "Unknown command";
            }
        }
        catch (const std::exception& e) {
            return std::string("Error: ") + e.what();
        }
    }

    // 获取指定索引的字符串
    std::string getString(size_t index) const {
        if (index >= strings.size()) {
            throw std::out_of_range("Invalid string index");
        }
        return strings[index];
    }
};

int main() {
    StringProcessor processor;
    
    // 添加一些测试字符串
    processor.addString("Hello World");
    processor.addString("Programming in C++");

    // 测试各种命令
    std::cout << processor.processCommand("copy 1 0 5") << std::endl;        // 输出: Hello
    std::cout << processor.processCommand("add 1 !!!") << std::endl;         // 添加 !!! 到第一个字符串
    std::cout << processor.processCommand("find 1 World") << std::endl;      // 查找 "World"
    std::cout << processor.processCommand("rfind 2 C++") << std::endl;       // 反向查找 "C++"

    return 0;
}

