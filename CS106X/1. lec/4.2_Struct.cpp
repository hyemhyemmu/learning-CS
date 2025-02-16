#include <unordered_set>
#include <set>
using namespace std;

struct Date{
    int month;
    int day;
};

// if it is a set
bool operator < (const Date& d1, const Date& d2){
    return d1.month < d2.month || (d1.month == d2.month && d1.day < d2.day);
}


// if it is a hashSet
int hashCode(const Date& date){
    return date.month * 100 + date.day;
}
