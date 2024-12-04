#ifndef TASK_OLED
#define TASK_OLED

#include <OLEDDisplay.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include <ESPAsyncWiFiManager.h>

SSD1306Wire display(0x3c, OLED_SDA, OLED_SCL);
#define defaultFont ArialMT_Plain_16

struct Oled {

// init oled
    void init() {
        // Initialising the UI will init the display too.
        display.init();
        display.flipScreenVertically();
        display.setFont(defaultFont);
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setContrast(50, 100, 30);
    }   

// affichage de la température
    void display_temperature(float temperature) {
        display.drawString(0, 20, "Temp:");
        display.drawString(64, 20, String(temperature));
    }

// affichage de la tension
    void display_voltage(float voltage) {
        display.drawString(0, 40, "Voltage:");
        display.drawString(64, 40, String(voltage));
    }

// affichage de l'IP
    void display_ip() {
        display.setFont(ArialMT_Plain_10);
        String ip = WiFi.localIP().toString();
        String rssi = String(WiFi.RSSI());
        display.drawString(0, 0, ip);
        display.drawString(100, 0, rssi + "dB");
        display.setFont(defaultFont);
    }

};

Oled oled; 
// task oled
void oled_task() {
    display.clear();
    oled.display_ip();
    oled.display_temperature(dallas.temperature);
    oled.display_voltage(voltage.voltage);
    display.display();

}


#endif  // TASK_OLED