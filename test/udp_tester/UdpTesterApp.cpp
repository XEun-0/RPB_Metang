#include "UdpTesterApp.h"


void testingCallBack() {
    printf("Hello\n");
}

int main() {

    gGlobalTestVar = 0;
    gTimerInstance = Timer::getInstance();

    gTimerInstance->setCallBack(testingCallBack);
    
    gTimerInstance->start1Hz();
    gTimerInstance->debug();
    
    printf("%d\n", gGlobalTestVar);

    while(true) {
        SLEEP_FOR(MILLISEC(1000));
    }

    return 0;
}