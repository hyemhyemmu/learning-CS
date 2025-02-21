// Polymorphism example
#include <iostream>
using namespace std;

class AbstarctDrinking{
public:
    virtual ~AbstarctDrinking() = default;
    virtual void boil() = 0;
    virtual void brew() = 0;
    virtual void pourInCup() = 0;
    virtual void addStuff() = 0;
    void makeDrink(){
        boil();
        brew();
        pourInCup();
        addStuff();
    }
};

class Coffee:public AbstarctDrinking{
public:
    void boil(){
        cout << "coffee water boiling!" << endl;
    }

    void brew(){
        cout << "coffee brewing!" << endl;
    }

    void pourInCup(){
        cout << "pour coffee in cup!" << endl;
    }

    void addStuff(){
        cout << "add sugar and milk!" << endl;
    }
};

class Tea:public AbstarctDrinking{
public:
    void boil(){
        cout << "tea water boiling!" << endl;
    }

    void brew(){
        cout << "tea brewing!" << endl;
    }

    void pourInCup(){
        cout << "pour tea in cup!" << endl;
    }

    void addStuff(){
        cout << "add lemon!" << endl;
    }
};

void making(AbstarctDrinking* drink){
    drink->makeDrink();
    delete drink;
}

int main(){
    making(new Coffee());
    making(new Tea());
    return 0;
}
