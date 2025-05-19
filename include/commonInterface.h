#ifndef COMMON_INTERFACE_H
#define COMMON_INTERFACE_H

struct wifiDataType {
    const char  *ssid;          // Your Wi-Fi network name
    const char  *password;      // Your Wi-Fi password
    const char  *udpAddress;    // Receiver IP address
    const int    udpPort;       // UDP port to use
}; // wifiDataType

#endif