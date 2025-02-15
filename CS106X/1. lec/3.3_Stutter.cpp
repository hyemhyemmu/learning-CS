#include <queue>
using namespace std;

/**
 * Accept a queue of integers and replace every elements with two copies of itself
 */
void Stutter(queue<int>& inputQueue){
    queue<int> tempQueue;
    while (!inputQueue.empty()) {
        int num = inputQueue.front();
        inputQueue.pop();
        tempQueue.push(num);
        tempQueue.push(num);
    }
    inputQueue = tempQueue;
}