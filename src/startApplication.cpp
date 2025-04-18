#include <Arduino.h>
#include "webListener.h"

void setup() {
    Serial.begin(115200);

    xTaskCreate(
        webListenerTaskLauncher,
        "webListenerTaskLauncher",
        2048,
        NULL,
        1,
        NULL
    );

    // No need to start scheduler
}

void loop() {
    // Not used
}
