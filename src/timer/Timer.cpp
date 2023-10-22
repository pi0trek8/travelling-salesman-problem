#include "Timer.h"

void Timer::time_start() {
    initialTime = high_resolution_clock::now();
}

void Timer::time_stop() {
    endTime = high_resolution_clock::now();
}

long long Timer::elapsed_time() {
    return duration_cast<seconds>(endTime - initialTime).count();
}