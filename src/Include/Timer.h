#ifndef TIMER_H
#define TIMER_H

#include "Globals.h"
#include <atomic>

class Timer {

    public:
        /*****************************************************************************
         * Function     : debug
         * Description  :
         *      debug function to test instance
         ****************************************************************************/
        void debug();

        /*****************************************************************************
         * Function     : getInstance
         * Description  :
         *      Function to get instance of Timer
         ****************************************************************************/
        static Timer* getInstance();

        /*****************************************************************************
         * Function     : setCallBack
         * Description  :
         *      Function to set callback function
         ****************************************************************************/
        void setCallBack(void (*callback)());

        /*****************************************************************************
         * Function     : start
         * Description  :
         *      Function to start the clock/timer
         ****************************************************************************/
        void start(int interval);

        /*****************************************************************************
         * Function     : start1Hz
         * Description  :
         *      Function to start the clock/timer at 1Hz
         ****************************************************************************/
        void start1Hz();

        /*****************************************************************************
         * Function     : stop
         * Description  :
         *      Function to stop clock/timer
         ****************************************************************************/
        void stop();
        
    private:
        Timer(): is_running(false), callback_func(NULL) {}
        ~Timer();
        Timer(const Timer&) = delete;
        Timer& operator=(const Timer&) = delete;
        
        static Timer *instance;
        std::atomic<bool> is_running;
        void (*callback_func)();
};


#endif // TIMER_H