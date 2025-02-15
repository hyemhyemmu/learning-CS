#include <iostream>
#include <string>
using namespace std;

int main(){
    string name;
    cout << "Enter your name:";
    getline(cin, name);

    int size=name.size();
    for (int i = 1; i < size;i++){
        cout << name.substr(0, i) << endl;
    }

    for (int i = 1; i <size;i++){
        for (int j=0;j<i;j++){
            cout << " ";
        }
        cout << name.substr(i, size) << endl;
    }

        return 0;
}