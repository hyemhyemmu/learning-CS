#include <iostream>
#include <vector>
using namespace std;

void diceRollsHelpers(int dice, vector<int>& chosen);

void diceRolls(int dice){
    vector<int> v;
    diceRollsHelpers(dice, v);
}

void diceRollsHelpers(int dice, vector<int>& chosen){
    if (dice==0) {
        for (int num : chosen) {
            cout << num << " ";
        }
        cout << endl;
    }
    else{
        // for each choice
        for (int i = 0; i <= 6;i++){
            // choose
            chosen.push_back(i);

            // search - explore
            diceRollsHelpers(dice - 1, chosen);

            // remove
            chosen.pop_back();
        }
    }
}
