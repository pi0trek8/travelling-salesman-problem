#ifndef LIST_TIMER_H
#define LIST_TIMER_H

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Timer {
private:
    high_resolution_clock::time_point endTime;
    high_resolution_clock::time_point initialTime;
public:

    void time_start();
    void time_stop();

    float elapsed_time_in_seconds();
    pair<string ,long long> elapsed_time();
};




#endif //LIST_TIMER_H
