#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_lcd_ili9341.h"
#include "esp_lcd_touch_xpt2046.h"

// nPrevious pinouts for SPI testing on arduino ide.
// // Define TFT display pins
// #define TFT_CS    5
// #define TFT_DC    2
// #define TFT_RST   4

// // Define Touchscreen pins (XPT2046 controller)
// #define TS_CS     15  // Chip Select for Touch
// #define TS_IRQ    -1   // Not used
// #define TS_CLK    18
// #define TS_MISO   19
// #define TS_MOSI   23

// LCD Pins
#define LCD_HOST        SPI2_HOST
#define PIN_NUM_MISO    19
#define PIN_NUM_MOSI    23
#define PIN_NUM_CLK     18
#define PIN_NUM_CS      5
#define PIN_NUM_DC      2
#define PIN_NUM_RST     4
#define PIN_NUM_BCKL    -1  // Backlight (can be managed by PWM)

// Touchscreen Pins
#define PIN_TOUCH_CS    15
#define PIN_TOUCH_IRQ   -1 // Not used

static const char *TAG = "LCD_TOUCH";

esp_lcd_panel_handle_t panel_handle;
esp_lcd_touch_handle_t touch_handle;

void init_lcd_touch() {
    ESP_LOGI(TAG, "Initializing SPI LCD and Touchscreen...");

    spi_bus_config_t buscfg = {
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = PIN_NUM_MISO,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 320 * 240 * 2 + 8
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_handle_t io_handle;
    esp_lcd_panel_io_spi_config_t io_config = ESP_LCD_PANEL_IO_SPI_CONFIG_DEFAULT(PIN_NUM_CS, LCD_HOST);
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_RST,
        .rgb_endian = LCD_RGB_ENDIAN_RGB,
        .bits_per_pixel = 16,
    };
    
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    // Touchscreen Init
    esp_lcd_touch_config_t touch_config = ESP_LCD_TOUCH_XPT2046_CONFIG_DEFAULT(PIN_TOUCH_CS, LCD_HOST);
    ESP_ERROR_CHECK(esp_lcd_touch_new_spi(io_handle, &touch_config, &touch_handle));

    ESP_LOGI(TAG, "LCD and Touchscreen initialized.");
}

void app_main() {
    init_lcd_touch();

    // Fill screen and print message
    esp_lcd_panel_clear(panel_handle, 0xFFFF);
    ESP_LOGI(TAG, "LCD Initialized, Touchscreen Ready.");

    while (1) {
        esp_lcd_touch_read_data(touch_handle);
        uint16_t touch_x, touch_y;
        bool touched = esp_lcd_touch_get_xy(touch_handle, 0, &touch_x, &touch_y);
        if (touched) {
            ESP_LOGI(TAG, "Touch detected at X: %d, Y: %d", touch_x, touch_y);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
