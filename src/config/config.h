#ifndef CONFIG
#define CONFIG

// dallas 
#define ONE_WIRE_BUS 2

// voltage divider
#define VOLTAGE_DIVIDER_PIN A0
#define VOLTAGE_DIVIDER_R1 10000
#define VOLTAGE_DIVIDER_R2 130000

// oled display I2C    
#define OLED_SDA 5
#define OLED_SCL 4

#define HOSTNAME "ESP8266-BMS"
#define VERSION "0.9.0"

// config mqtt
#define MQTT_SERVER "192.168.1.22"
#define MQTT_PORT 1883
#define MQTT_USER "mosquitto"
#define MQTT_PASSWORD "test-123"

#endif  // CONFIG