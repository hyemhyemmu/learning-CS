#include <queue>
#include <stack>
using namespace std;

/**
 * accept a queue of string, append the queue's content to itself and reverse order
 */
void Mirror(queue<char>& inputQueue){
    int size = inputQueue.size();
    stack<char> tempStack;

    for (int i = 0; i < size;i++){
        char temp = inputQueue.front();
        inputQueue.pop();
        inputQueue.push(temp);
        tempStack.push(temp);
    }

    while (!tempStack.empty()){
        char element = tempStack.top();
        tempStack.pop();
        inputQueue.push(element);
    }
}