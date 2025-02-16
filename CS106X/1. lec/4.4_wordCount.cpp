#include <iostream>
#include <map>
#include <string>
using namespace std;
 
void count(map<char, int> &dic, string word);

int main(){
    string word;
    cin >> word;

    map<char, int> dic;
    count(dic, word);

    // print the dictionary
    cout << "Here is the word count :" << endl;
    for (const auto& pair:dic){
        cout << pair.first << ":" << pair.second << endl;
    }

}

void count(map<char, int> &dic, string word){
    for (int i = 0; i < word.length();i++){
        char ch = word[i];
            dic[ch]++;
    }
}