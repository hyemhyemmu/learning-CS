#include <string>
#include <iostream>
using namespace std;

// use recursion to evaluate the value of a mathematic expression
class Evaluator{
public:
    Evaluator(const string& expression) : exp(expression), index(0) {}

    int evaluate() { return parseExpression(); }
private:
    string exp;
    int index;

    //1. deal with ( and digits
    int parseFactor(){
        if (index >= exp.size()) return 0; //protection

        if (exp[index]=='('){
            index++;
            int result = parseExpression();
            index++;
            return result;
        }
        else{
            // numbers
            int num = 0;
            while (index<exp.size()&&isdigit(exp[index])){
                num = 10 * num + (exp[index] - '0');
                index++;
            }
            return num;
        }
    }

    //2. deal with * and /
    int parseTerm(){

        int prev = parseFactor();
        while (index < exp.size() && (exp[index] == '*' || exp[index] == '/')){
            char op = exp[index];
            index++;
            int next = parseFactor(); // deal with the parts after op first

            if (op== '*')
                prev *= next;
            else
                prev /= next;
        }
        return prev;
    }

    // 3. deal with + and -
    int parseExpression(){
        int prev = parseTerm();
        while (index < exp.size() && (exp[index] == '+' || exp[index] == '-')){
            char op = exp[index];
            index++;
            int next = parseTerm(); // deal with the parts after op first

            if (op== '+')
                prev += next;
            else
                prev -= next;
        }
        return prev;
    }
};


// entrance function
int evaluate(const string& exp){
    Evaluator eval(exp);
    return eval.evaluate();
}

// testing code
int main() {
    cout << evaluate("3+5*2") << endl;      // 13
    cout << evaluate("(3+5)*2") << endl;    // 16
    cout << evaluate("10/(2+3)") << endl;   // 2
    cout << evaluate("100-5*10+50") << endl; // 100
    return 0;
}
