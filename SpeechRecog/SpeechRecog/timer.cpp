#include "timer.h"

using namespace std;

Timer::Timer()
{
    resetTimer();
}

void Timer::resetTimer()
{
    startTime = chrono::high_resolution_clock::now();
    tick = true;
}

bool Timer::hasTickYet()
{
    if (tick) {
        tick = false;
        return true;
    } else {
        if (chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - lastTick).count()>= 1) {
            lastTick = chrono::high_resolution_clock::now();
            tick = false;
            return true;
        } else return false;
    }
}

double Timer::elapsedTimeSecond()
{
    auto elapsed = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - startTime);
    return elapsed.count();
}

