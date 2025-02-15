#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    ifstream input;
    input.open("stuff.txt");
    string line;
    while (getline(input,line)){
        cout << line << endl;
    }
    return 0;
}