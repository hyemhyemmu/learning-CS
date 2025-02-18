#include <iostream>
#include <string>
using namespace std;

void permute(string s, string prefix){
    if (s.length()==0)
        // base case
        cout << prefix << endl;
    else{
        // "choose" current character
        for (int i = 0; i < s.length();i++){
            char ch = s[i];
            string newString = s.substr(0, i) + s.substr(i + 1);
            permute(newString, prefix + ch);
        }
    }
}


int main(){
    permute("MARTE", "");
    return 0;
}
