#ifndef WEB_FUNCTIONS
#define WEB_FUNCTIONS

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

DNSServer dns;
AsyncWebServer server(80);
AsyncWiFiManager wifiManager(&server,&dns);

extern dallas_data dallas;
extern Voltage voltage;

String status();


// call_pages : appel des pages web

void call_pages() {
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", status());
  });

  // Start server
  server.begin();
}

String status() {
  // remonté json de l état de la batterie
  String message; 
  JsonDocument doc; 
  doc["temperature"] = dallas.temperature;
  doc["tension"] = voltage.get_voltage();
  serializeJson(doc, message) ;

  return message;
}

#endif  // WEB_FUNCTIONS