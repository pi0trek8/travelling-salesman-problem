#include "Timer.h"

void Timer::time_start() {
    initialTime = high_resolution_clock::now();
}

void Timer::time_stop() {
    endTime = high_resolution_clock::now();
}

pair<string ,long long> Timer::elapsed_time() {
    auto time_in_seconds = duration_cast<seconds>(endTime - initialTime).count();
    if (time_in_seconds != 0) {
        return pair("seconds", time_in_seconds);
    }
    return pair("microseconds", duration_cast<microseconds>(endTime - initialTime).count());
}