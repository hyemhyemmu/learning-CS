#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

void permute(string s, string prefix);

void combinations(string s){
    string uniqueString = "";
    unordered_set<char> seen;
    for (int i = 0; i < s.length();i++){
        char ch = s[i];
        if (seen.find(ch)==seen.end()){
            seen.insert(ch);
            uniqueString += ch;
        }
    }

    permute(uniqueString, "");
}

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
    combinations("GOOGLE");
    return 0;
}