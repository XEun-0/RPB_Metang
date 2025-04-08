#include <stdio.h>
#include "driver/uart.h"
#include "esp_log.h"
#include <string.h>


#define UART_NUM UART_NUM_0 // Use UART0 for USB-to-serial
#define BUF_SIZE (1024)

static const char *TAG = "UART_VERIFY";

void app_main() {
    // Configure UART parameters
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    // Install and configure UART driver
    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    ESP_LOGI(TAG, "UART initialized. Sending test message...");

    // Send test message
    const char *test_msg = "ESP-IDF UART verification!\n";
    uart_write_bytes(UART_NUM, test_msg, strlen(test_msg));

    // Buffer for receiving data
    uint8_t data[BUF_SIZE];

    while (1) {
        int len = uart_read_bytes(UART_NUM, data, BUF_SIZE, 1000 / portTICK_PERIOD_MS);
        if (len > 0) {
            data[len] = '\0'; // Null-terminate received data
            ESP_LOGI(TAG, "Received: %s", data);
            uart_write_bytes(UART_NUM, (const char *)data, len); // Echo back
        }
    }
}
