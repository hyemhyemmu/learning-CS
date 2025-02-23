#include <vector>
#include <algorithm>

template <class T>
class FilterClass {
private:
    T minVal;
    T maxVal;

public:
    // 构造函数，接收过滤的范围
    FilterClass(const T& min, const T& max) : minVal(min), maxVal(max) {}

    // 函数调用运算符，用作过滤条件
    bool operator()(const T& val) const {
        return val >= minVal && val <= maxVal;
    }

    // 静态过滤方法
    static std::vector<T> filter(const std::vector<T>& input, const T& min, const T& max) {
        std::vector<T> result;
        FilterClass<T> predicate(min, max);
        
        // 使用 copy_if 算法进行过滤
        std::copy_if(input.begin(), 
                    input.end(), 
                    std::back_inserter(result), 
                    predicate);
        
        return result;
    }
};