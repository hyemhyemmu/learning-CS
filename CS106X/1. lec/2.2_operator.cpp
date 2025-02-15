#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(){
    // operator >> allows us to tokenize the input stream
    ifstream input;
    input.open("stuff.txt");
    string word;
    input >> word;
    input >> word;

    if (!(input >> word)){
        cout << "No more words" << endl;
    }

    return 0;
}
