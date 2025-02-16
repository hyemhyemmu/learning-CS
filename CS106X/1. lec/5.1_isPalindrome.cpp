#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& word){
    if (word.length()<1)
        return true;
    if (word[0]!=word[word.length()-1])
        return false;
    return isPalindrome(word.substr(1, word.length() - 2));
}


int main(){
    string word;
    cout << "Enter a word: ";
    cin >> word;

    string copy = word;
    if (isPalindrome(copy)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    return 0;
}