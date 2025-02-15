#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> names {"Alex", "Betty", "Carla", "David", "Emily"};

int main(){
    for (int i = 0; i < names.size();i++){
        cout << names[i] << endl;
    }

    for (string name: names){
        cout << name << endl;
    }

    for (string& name: names){
        name = "Hello " + name;
    }

    for (const string& name : names) {
        cout << name << endl;
    }

    return 0;
}

