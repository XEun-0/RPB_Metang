#include "webListener.h"

WiFiUDP udp;

WebListener *WebListener::instance = nullptr;

WebListener::WebListener(void) {}
WebListener::~WebListener(void) {}

void WebListener::init(void) {
    // *ssid = "your-SSID";             // Your Wi-Fi network name
    // *password = "your-password";     // Your Wi-Fi password
    // *udpAddress = "192.168.1.100";   // Receiver IP address
    // udpPort = 12345;                 // UDP port

    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i) {
        Serial.printf("%d: %s (%ddBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
    }

    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        printf("Connecting to WiFi...\n");
        //Serial.println("Connecting to WiFi...");
    }

    printf("Connected to WiFi\n");
    //Serial.println("Connected to WiFi");
    
    udp.begin(udpPort);
}

void WebListener::mainLoop(void) {
    // Do whatever
    int packetSize = 0;
    
    printf("[ webListenerTask ]  Starting..\n");

    while(1) {
        // Do whatever
        
        printf("[ webListenerTask ]  Working..\n");
        
        // Do something. Udp just convert the 
        // print job file into something 
        // transferable via network

        // might have to convert this mcu into
        // an WAP (wifi access point).
        
        // packetSize = udp.parsePacket();
        // if (packetSize) {
        //     char incomingPacket[255];
        //     int len = udp.read(incomingPacket, 255);
        //     if (len > 0) {
        //         incomingPacket[len] = 0;  // Null-terminate the string
        //     }
        //     Serial.printf("Received: %s\n", incomingPacket);
        // }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    // Send error code serial msg if needed.
    // It should never get here
    printf("[ webListenerTask ]  Ended..\n");
    vTaskDelete( NULL );
}

WebListener *WebListener::getInstance (void) {
    if (WebListener::instance == nullptr) {
        WebListener::instance = new WebListener();
        WebListener::instance->init(); // may not be needed
    }

    return WebListener::instance;
}

void webListenerTaskLauncher( void *pvParams ) {
    WebListener *pWebListener = WebListener::getInstance();
    pWebListener->mainLoop();
}