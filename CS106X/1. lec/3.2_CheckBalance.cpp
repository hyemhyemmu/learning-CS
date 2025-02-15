#include <iostream>
#include <stack>
using namespace std;

/**
 * Write a function named checkBalance that accepts a string of source code and 
 * uses a stack to check whether the braces/parentheses are balanced. 
 * Every ( or { must be closed by a } or ) in the opposite order. 
 * Return the index at which an imbalance occurs, or -1 if the string is balanced. 
 * If any ( or { are never closed, return the string's length.
 */

int checkBalance(string code) {
    stack<char> s;
    for (int i = 0; i < code.length();i++){
        if (code[i]=='{'||code[i]=='(' ){
            s.push(code[i]); // push all the left elements to the stack
        }else if(code[i]=='}'){
            // check if match
            if (s.empty() || s.top() != '{'){
                return i;
            }
            // match -> pop it out
            s.pop();
        }else if(code[i]==')'){
            if (s.empty() || s.top() != '(')
                return i;
            // match -> pop it out
            s.pop();
        }

        
    }

// at the end: 1. stack empty -> all the stuff done-> return -1; 
//2. stack not empty -> not matched -> return length

    return s.empty() ? -1 : code.length();
}