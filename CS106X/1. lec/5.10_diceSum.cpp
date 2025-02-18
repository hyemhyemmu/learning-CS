#include <iostream>
#include <vector>
using namespace std;

// notice: "lastNum" is used to keep tracked of the number just used to make sure
// there won't be any repeating combinations
void diceSumHelper(int dice, int desiredSum, int currentSum, vector<int>& chosen, int lastNum);

void diceSum(int dice, int desiredSum){
    vector<int> v;
    diceSumHelper(dice, desiredSum, 0, v, 1);
}

void diceSumHelper(int dice, int desiredSum, int currentSum, vector<int>& chosen, int lastNum){
    if (dice==0){
        if (currentSum==desiredSum){
            cout << "[";
            for (size_t i = 0; i < chosen.size(); i++) {
                cout << chosen[i];
                if (i < chosen.size() - 1) cout << " ";
            }
            cout << "]" << endl;
        }
    }
    else{
        // still choice to make
        for (int i = lastNum; i <= 6;i++){
            // six choices can be made each time
            // filter, filt the path that are impossible at the very beginning
            int min = currentSum + i + 1 * (dice - 1);
            int max = currentSum + i + 6 * (dice - 1);

            // only possible paths will be used
            if (min <= desiredSum && desiredSum <= max){
                // choose
                chosen.push_back(i);
                currentSum += i;
                diceSumHelper(dice - 1, desiredSum, currentSum, chosen, i);
                // remove
                chosen.pop_back();
                currentSum -= i; // everyone only need to deal with own stuff
            }
        }
    }
}

int main(){
    diceSum(3, 8);
    system("pause");
    return 0;
}