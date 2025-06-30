#include "Timer.h"

/** Variables */
Timer *Timer::instance = nullptr;

/************************************************************************************
 * Private      : Timer.h
 * Constructor  : Timer
 * In: 
 *      None
 * Returns:
 *      None
 ***********************************************************************************/
// Timer(): is_running(false), callback_func(NULL) {}

/************************************************************************************
 * Private      : Timer.h
 * Destructor   : ~Timer
 * In: 
 *      None
 * Returns:
 *      None
 ***********************************************************************************/
Timer::~Timer() {}

/************************************************************************************
 * Public       : Timer.h
 * Function     : start
 * In: 
 *      int     interval
 * Returns:
 *      void
 ***********************************************************************************/
void Timer::start(int interval) {
    is_running = true;

    std::thread([this, interval]() {
        while (is_running) {
            SLEEP_FOR(MILLISEC(interval));
            if(callback_func) {
                callback_func();
            }
        }
    }).detach();
}

/************************************************************************************
 * Public       : Timer.h
 * Function     : start1Hz
 * In: 
 *      None
 * Returns:
 *      void
 ***********************************************************************************/
void Timer::start1Hz() {
    start(1000);
}

/************************************************************************************
 * Public       : Timer.h
 * Function     : stop
 * In: 
 *      None
 * Returns:
 *      void
 ***********************************************************************************/
void Timer::stop() {
    is_running = false;
}

/************************************************************************************
 * Public       : Timer.h
 * Function     : setCallBack
 * In: 
 *      void*       func()
 * Returns:
 *      void
 ***********************************************************************************/
void Timer::setCallBack(void (*func)()) {
    callback_func = func;
}

/************************************************************************************
 * Public       : Timer.h
 * Function     : getInstance
 * In: 
 *      None
 * Returns:
 *      Timer*
 ***********************************************************************************/
Timer* Timer::getInstance() {
    if (Timer::instance == nullptr) {
        Timer::instance = new Timer();
    }

    return Timer::instance;
}

/************************************************************************************
 * Public       : Timer.h
 * Function     : debug
 * In: 
 *      None
 * Returns:
 *      void
 ***********************************************************************************/
void Timer::debug() {
    printf("Debbuged\n");
}