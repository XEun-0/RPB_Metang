#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdio>

// #include "Timer.h"
class Timer;

#ifdef DECLARE_GLOBALS
    uint8_t gGlobalTestVar;
    Timer*  gTimerInstance;
#else
    extern uint8_t  gGlobalTestVar;
    extern Timer*   gTimerInstance;
#endif

// Convenience Macros
#define SEC(sec)            std::chrono::seconds(sec)
#define MILLISEC(msec)      std::chrono::milliseconds(msec)
#define SLEEP_FOR(time)     std::this_thread::sleep_for(time)


#endif // GLOBALS_H