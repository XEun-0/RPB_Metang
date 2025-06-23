#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    const char* target_ip = "192.168.1.251";  // ESP32's IP address
    const int target_port = 12345;            // UDP port ESP32 is listening on
    const char* message = "Hello ESP32 from Desktop!";

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up ESP32 address
    sockaddr_in esp32_addr{};
    esp32_addr.sin_family = AF_INET;
    esp32_addr.sin_port = htons(target_port);
    inet_pton(AF_INET, target_ip, &esp32_addr.sin_addr);

    // Send message
    ssize_t sent_bytes = sendto(sock, message, strlen(message), 0,
                                (sockaddr*)&esp32_addr, sizeof(esp32_addr));
    if (sent_bytes < 0) {
        perror("Send failed");
        close(sock);
        return 1;
    }

    std::cout << "Sent to ESP32: " << message << std::endl;

    close(sock);
    return 0;
}
