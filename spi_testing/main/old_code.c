#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <TouchScreen.h> // Touch support

// Define TFT display pins
#define TFT_CS    5
#define TFT_DC    2
#define TFT_RST   4

// Define Touchscreen pins (XPT2046 controller)
#define TS_CS     15  // Chip Select for Touch
#define TS_IRQ    -1   // Not used
#define TS_CLK    18
#define TS_MISO   19
#define TS_MOSI   23

// Create display and touchscreen objects
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
TouchScreen ts = TouchScreen(TS_CLK, TS_CS, TS_MOSI, TS_MISO, TS_IRQ);

uint16_t textColor = ILI9341_WHITE; // Default text color

void setup() {
    Serial.begin(9600); // Initialize Serial for debugging
    tft.begin();
    tft.setSPISpeed(20000000);
    tft.setRotation(1);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(textColor);
    tft.setTextSize(2);
    tft.setCursor(50, 50);
    tft.print("Hello, World!");
}

void loop() {
    // Check for touch input
    TSPoint p = ts.getPoint();

    // Debug: Print raw touch data (x, y, z)
    Serial.print("X: ");
    Serial.print(p.x);
    Serial.print(" Y: ");
    Serial.print(p.y);
    Serial.print(" Z: ");
    Serial.println(p.z);

    // Check if the touch pressure is above a threshold
    if (p.z > 200) {
        // Switch text color on touch
        if (textColor == ILI9341_WHITE) {
            textColor = ILI9341_RED; // Change color to red
        } else if (textColor == ILI9341_RED) {
            textColor = ILI9341_GREEN; // Change color to green
        } else if (textColor == ILI9341_GREEN) {
            textColor = ILI9341_BLUE; // Change color to blue
        } else {
            textColor = ILI9341_WHITE; // Reset to white
        }

        // Clear screen before updating text color
        tft.fillScreen(ILI9341_BLACK);
        tft.setTextColor(textColor);
        tft.setCursor(50, 50);
        tft.print("Hello, World!");
    }

    // Always update the Z value for debug
    tft.setCursor(50, 100); // Update text position for z value display
    tft.print("Pressure: ");
    tft.print(p.z);

    delay(30);
}