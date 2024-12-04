#ifndef TASK_VOLTAGE
#define TASK_VOLTAGE

struct Voltage {
    float voltage;
    float get_voltage() {
        int value = analogRead(VOLTAGE_DIVIDER_PIN);
        float voltage = (value * 3.3) / 1024;
        voltage = voltage * ((VOLTAGE_DIVIDER_R1 + VOLTAGE_DIVIDER_R2) / VOLTAGE_DIVIDER_R1);
        return voltage;
    }
};

Voltage voltage;

// task voltage
void voltage_task() {
    voltage.voltage = voltage.get_voltage();
    //Serial.print("Voltage is: ");
    //Serial.println(voltage.voltage);
}

#endif  // TASK_VOLTAGE