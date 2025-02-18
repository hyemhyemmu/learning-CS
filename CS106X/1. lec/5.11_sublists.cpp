#include <iostream>
#include <vector>
#include <string>
using namespace std;

void sublistsHelper(vector<string> &v, vector<string> chosen);

// prints all subsets of given vector
// the key point of this problem is the decision tree
void sublists(vector<string>& v){
    vector<string> chosen;
    sublistsHelper(v, chosen);
}


void sublistsHelper(vector<string>& v, vector<string> chosen){
    if (v.empty()){
        cout << "{";
        for (size_t i = 0; i < chosen.size(); i++) {
            cout << chosen[i];
            if (i < chosen.size() - 1) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
        return;
    }
    else{
    // first element
    string first = v[0];
    v.erase(v.begin());
    
    // not choosing current element
    sublistsHelper(v, chosen);
    
    // choose current element
    chosen.push_back(first);
    sublistsHelper(v, chosen);
    
    // restore
    chosen.pop_back();
    v.insert(v.begin(), first);

    }
}

int main() {
    // test
    vector<string> test = {"A", "B", "C"};
    cout << "All sublists of {A, B, C}:" << endl;
    sublists(test);
    return 0;
}
