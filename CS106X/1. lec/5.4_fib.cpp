#include <iostream>
#include <unordered_map>
using namespace std;

int fib (int n){
    static unordered_map<int, int> cache;

    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;
    else if (cache.count(n)>0)
        return cache[n];
    else {
        cache[n] = fib(n - 1) + fib(n - 2);
        return cache[n];
    }
}
