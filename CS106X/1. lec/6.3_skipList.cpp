#include <iostream>
#include <cstdlib>
#include <cmath>
#include <climits>

template<typename T>
class SkipList {
private:
    struct Node {
        T value;
        Node** forward; // 存储每一层的前向指针
        int level;      // 节点的层数

        Node(T val, int lvl) : value(val), level(lvl) {
            forward = new Node*[lvl + 1];
            for (int i = 0; i <= lvl; i++) {
                forward[i] = nullptr;
            }
        }

        ~Node() {
            delete[] forward;
        }
    };

    Node* head;     // 头节点
    int maxLevel;   // 最大层数
    int currentLevel; // 当前层数
    float probability; // 用于随机层数的概率值

    // 随机生成层数
    int randomLevel() {
        int level = 1;
        while ((float)rand()/RAND_MAX < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLvl = 16, float p = 0.5) : 
        maxLevel(maxLvl), probability(p), currentLevel(1) {
        head = new Node(T(), maxLevel);
    }

    ~SkipList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    // 插入节点
    void insert(T value) {
        Node* update[maxLevel + 1];
        Node* current = head;

        // 从最高层开始向下查找插入位置
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        // 获取随机层数
        int newLevel = randomLevel();
        if (newLevel > currentLevel) {
            for (int i = currentLevel; i < newLevel; i++) {
                update[i] = head;
            }
            currentLevel = newLevel;
        }

        // 创建新节点
        Node* newNode = new Node(value, newLevel);

        // 更新指针
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    // 查找节点
    bool search(T value) {
        Node* current = head;

        // 从最高层开始向下搜索
        for (int i = currentLevel - 1; i >= 0; i--) {
            while (current->forward[i] != nullptr && 
                   current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        return (current != nullptr && current->value == value);
    }

    // 打印跳表
    void display() {
        for (int i = currentLevel - 1; i >= 0; i--) {
            Node* current = head->forward[0];
            std::cout << "Level " << i << ": ";
            while (current != nullptr) {
                if (current->level > i) {
                    std::cout << current->value << " ";
                } else {
                    std::cout << "- ";
                }
                current = current->forward[0];
            }
            std::cout << std::endl;
        }
    }
};