#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <string>
#include <functional>
using namespace std;

class Timer {
private:
    time_t scheduledTime;
    bool isRecurring;
    int intervalDays;
    function<void()> task;
    
public:
    Timer(time_t time, bool recurring, int interval, function<void()> callback)
        : scheduledTime(time), isRecurring(recurring), 
          intervalDays(interval), task(callback) {}
          
    void execute();
    bool shouldRun(time_t currentTime);
    void updateNextRun();
};

#endif
