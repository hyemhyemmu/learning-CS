#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void reverseLines(ifstream& input){
    string line;
    if (getline(input,line)){ //still other lines
        reverseLines(input);
        cout << line << endl;
    }
}