#include <Arduino.h>

// Web services
#include <ESPAsyncWiFiManager.h>
#include <ESPAsyncWebServer.h>
// ota mise à jour sans fil
#include <ElegantOTA.h>

// MQTT
#include <PubSubClient.h>
#include <ArduinoJson.h> // ArduinoJson v6

// Config
#include "config/config.h"

//tasks
#include <TaskScheduler.h> // gestion des taches
#include "tasks/mqtt.h"
#include "tasks/dallas.h"
#include "tasks/voltage.h"
#include "tasks/oled.h"
#include "tasks/mqtt.h"

// functions
#include "functions/web.h"

WiFiClient espClient;
PubSubClient client(espClient);

Task Task_dallas(8880, TASK_FOREVER, &dallas_task); // tache dallas
Task Task_oled(5550, TASK_FOREVER, &oled_task); // tache oled
Task Task_voltage(9990, TASK_FOREVER, &voltage_task); // tache voltage
Task Task_mqtt(10050, TASK_FOREVER, &mqtt_task); // tache mqtt
Scheduler runner;

/// déclaration de la dallas
dallas_data dallas;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // init des ports 
  pinMode(VOLTAGE_DIVIDER_PIN, INPUT);

  //dallas.init(); // init de la dallas
        sensors.begin();
        sensors.setWaitForConversion(false);
        sensors.setResolution(12);
        sensors.requestTemperatures(); // Send the command to get temperatures
        dallas.temperature = sensors.getTempCByIndex(0);

  /// init des tasks 
  runner.init();
  runner.addTask(Task_dallas); // ajout de la tache dallas
  runner.addTask(Task_oled); // ajout de la tache oled
  runner.addTask(Task_voltage); // ajout de la tache voltage
  //Task_dallas.enable();
  oled.init();
  //Task_oled.enable();
  runner.enableAll();

  // démarrage file system
  //LittleFS.begin();

  // doit être placé avant la connexion sinon sous ESP32, l'hostname n'est pas pris en compte
  WiFi.setHostname(HOSTNAME);
  wifiManager.autoConnect(HOSTNAME);
  // Afficher le nom :
  //wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.setConfigPortalTimeout(600);

  // Wait for Wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  WiFi.setAutoReconnect(true);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

    //***********************************
  //************* Setup - OTA
  //***********************************
  ElegantOTA.begin(&server);      // Start ElegantOTA
  ElegantOTA.setAutoReboot(true);

  //***********************************
  //************* Setup - pages web
  Serial.println("start server");
  call_pages();

  //***********************************
  //************* Setup - MQTT
  //***********************************
  devices_init();
  runner.addTask(Task_mqtt); // ajout de la tache mqtt
  //Task_mqtt.enable();
  




}

void loop() {
  runner.execute();
  delay(5000);
  // put your main code here, to run repeatedly:
}

