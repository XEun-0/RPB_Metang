#include "webListener.h"

WiFiUDP udp;

WebListener *WebListener::instance = nullptr;

WebListener::WebListener(void) {}
WebListener::~WebListener(void) {}

void WebListener::init(void) {
    // *ssid = "your-SSID";       // Your Wi-Fi network name
    // *password = "your-password";  // Your Wi-Fi password
    // *udpAddress = "192.168.1.100"; // Receiver IP address
    // udpPort = 12345;  // UDP port

    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    
    udp.begin(udpPort);
}

void WebListener::mainLoop(void) {
    // Do whatever
    int packetSize = 0;
    
    while(1) {
        // Do whatever
        
        packetSize = udp.parsePacket();
        if (packetSize) {
            char incomingPacket[255];
            int len = udp.read(incomingPacket, 255);
            if (len > 0) {
                incomingPacket[len] = 0;  // Null-terminate the string
            }
            Serial.printf("Received: %s\n", incomingPacket);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }

    // Send error code serial msg if needed.
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