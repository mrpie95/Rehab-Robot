#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
    bool tick;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point lastTick;

public:
    Timer();
    void resetTimer();

    bool hasTickYet();
    double elapsedTimeSecond();
};

#endif // TIMER_H
