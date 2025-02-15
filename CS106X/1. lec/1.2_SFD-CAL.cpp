#include <iostream>
using namespace std;

int main(){
    int stanford, cal;
    cout << "Stanford points scored: ";
    cin >> stanford;
    cout << "Cal points scored: ";
    cin >> cal;

    if (stanford>cal){
        cout << "yay" << endl;
    }
    else{
        cout << "boo" << endl;
    }

    return 0;
}
