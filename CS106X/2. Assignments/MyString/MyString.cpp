#include <string>

class MyString: public std::string {
public:
    // 构造函数
    using std::string::string;

    // 1. 返回子串的运算符
    std::string operator() (size_t start, size_t length = std::string::npos) const {
        return std::string(substr(start, length));
    }  

    // 2. 字符串拼接运算符
    std::string operator+ (const MyString& other) const {
        return std::string(*this) + std::string(other);
    }

    // 3. 相等比较运算符
    bool operator== (const MyString& other) const {
        return std::string(*this) == std::string(other);
    }
};