#include <iostream>
using namespace std;

void printLine(int width=10, char letter='*'){
    for (int i = 0; i < width;i++){
        cout << letter;
    }
}

int main(){
    int width;
    char letter;

    cin >> width;
    cin >> letter;

    printLine(width, letter);

    return 0;
}