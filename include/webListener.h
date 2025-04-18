#ifndef WEB_LISTENER_H
#define WEB_LISTENER_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

class WebListener {

public:
    static WebListener *getInstance(void);
    void mainLoop(void);

private:
    static WebListener *instance;
    const char *ssid = "your-SSID";       // Your Wi-Fi network name
    const char *password = "your-password";  // Your Wi-Fi password
    const char *udpAddress = "192.168.1.100"; // Receiver IP address
    const int udpPort = 12345;  // UDP port

    WebListener(void);
    ~WebListener(void);

    void init(void);
};

// Not in class

void webListenerTaskLauncher( void *pvParams );

#endif  // WEB_LISTENER_H