#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(){
    map<string, double> gpa;
    gpa.insert({"Messi", 3.98});
    gpa.insert({"Ronaldo", 0.43});
    gpa.insert({"Tuchel", 4.00});

    for (const auto& pair : gpa){
        cout << pair.first << "'s GPA is " << pair.second << endl;
    }
    return 0;
}