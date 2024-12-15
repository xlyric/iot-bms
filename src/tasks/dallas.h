#ifndef TASK_DALLAS
#define TASK_DALLAS

// Dallas 18b20
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config/config.h"
OneWire ds(ONE_WIRE_BUS);   //  (a 4.7K resistor is necessary - 5.7K work with 3.3 ans 5V power)
DallasTemperature sensors(&ds);

// structure dallas 
struct dallas_data {
  float temperature;

    void print() {
        Serial.print("Temperature: ");
        Serial.println(temperature);
    }   

//init dallas
    void init() {
        sensors.begin();
        sensors.setWaitForConversion(false);
        sensors.setResolution(12);
    }

// récupération de la température
    void get_temperature() {
        sensors.requestTemperatures(); // Send the command to get temperatures
        temperature = sensors.getTempCByIndex(0);
        if (temperature == -127.00) {
          init();
        }
    }

};

extern dallas_data dallas;

void dallas_task() {
  dallas.get_temperature(); 
  Serial.print("Temperature is: ");
  Serial.println(dallas.temperature); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
}

#endif  // TASK_DALLAS