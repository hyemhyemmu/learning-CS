#include <iostream>
#include <unordered_set>
using namespace std;

bool isHappyNumber(int n) {
    unordered_set<int> seen;
    
    if (n == 1)
        return true;
    
    while (seen.find(n) == seen.end()) { // does not exist
        seen.insert(n);
        
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
        
        if (n == 1)
            return true;
    }
    
    return false;
}