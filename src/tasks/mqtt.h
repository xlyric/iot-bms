#ifndef TASK_MQTT
#define TASK_MQTT

// Web services
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "voltage.h"
#include "dallas.h"
extern PubSubClient client;
extern dallas_data dallas;
extern Voltage voltage;

/// @brief déclaration des configurations HA et MQTT
struct HA
{
private: int MQTT_INTERVAL = 60;
  /* MQTT */
private: String name="none";
public: void Set_name(String setter) {
    name=setter;
  }

private: String object_id;
public: void Set_object_id(String setter) {
    object_id=setter;
  }

private: String dev_cla;
public: void Set_dev_cla(String setter) {
    dev_cla=setter;
  }

private: String unit_of_meas;
public: void Set_unit_of_meas(String setter) {
    unit_of_meas=setter;
  }

private: String stat_cla;
public: void Set_stat_cla(String setter) {
    stat_cla=setter;
  }

private: String entity_category;
public: void Set_entity_category(String setter) {
    entity_category=setter;
  }

private: String entity_type="sensor";
public: void Set_entity_type(String setter) {
    entity_type=setter;
  }

private: String icon;
public: void Set_icon(String setter) {
    icon=R"("ic": ")" + setter + R"(",)";
  }
  // {icon="\"ic\": \""+ setter +"\", "; }

private: String min;
public: void Set_entity_valuemin(String setter) {
    min=setter;
  }

private: String max;
public: void Set_entity_valuemax(String setter) {
    max=setter;
  }

private: String step;
public: void Set_entity_valuestep(String setter) {
    step=setter;
  }

private: String entity_option;
public: void Set_entity_option(String setter) {
    entity_option=setter;
  }

private: bool retain_flag;
public: void Set_retain_flag(bool setter) {
    retain_flag=setter;
  }

private: int qos;
public: void Set_entity_qos(int setter) {
    qos=setter;
  }

private: String retain;
public: void Set_retain(bool setter) {
    if (setter) {retain="\"ret\":true,"; }
  }

private: String expire_after;
public: void Set_expire_after(bool setter) {
    if (setter) {expire_after=R"("exp_aft": ")" + String(MQTT_INTERVAL) + R"(", )"; }
  }

private: String HA_sensor_type() {
    String topic = "homeassistant/"+ entity_type +"/"+ node_id +"/";
    String topic_Xlyric = "Xlyric/"+ node_id +"/";
    String info;
    if (entity_type == "sensor") {
      info = "\"dev_cla\": \""+dev_cla+"\","
             "\"unit_of_meas\": \""+unit_of_meas+"\","
             "\"stat_cla\": \""+stat_cla+"\","
             "\"value_template\": \"{{ value_json."+ object_id +" }}\",";
    }
    else if (entity_type == "switch") {
      info = R"(
          "value_template": "{{ value_json.)" + object_id + R"( }}",
          "payload_on": "{ \")" + object_id + R"(\" : 1 }",
          "payload_off": "{ \")" + object_id + R"(\" : 0 }",
          "stat_on": "1",
          "stat_off": "0",
          "qos": 1,
          "command_topic": ")" + topic_Xlyric + R"(command/)" + entity_type + R"(/)" + object_id + R"(",
          )";
    }
    else if (entity_type == "number") {
      info = "\"val_tpl\": \"{{ value_json."+ object_id +" }}\","
             "\"cmd_t\": \""+ topic_Xlyric + "command/" +  entity_type + "/" + object_id + "\","
             "\"cmd_tpl\": \"{ \\\""+object_id+"\\\" : {{ value }} } \","
             "\"entity_category\": \""+ entity_category + "\","
             "\"max\": \""+max+"\","
             "\"min\": \""+min+"\","
             "\"step\": \""+step+"\",";
    }
    else if (entity_type == "select") {
      info = "\"val_tpl\": \"{{ value_json."+ object_id +" }}\","
             "\"cmd_t\": \""+ topic_Xlyric + "command/" +  entity_type + "/" + object_id + "\","
             "\"cmd_tpl\": \"{ \\\""+object_id+"\\\" : \\\"{{ value }}\\\" } \","
             "\"entity_category\": \""+ entity_category + "\","
             "\"options\": ["+ entity_option + "],";
    }
    else if (entity_type == "binary_sensor") {
      info = "\"dev_cla\": \""+dev_cla+"\","
             "\"pl_on\":\"true\","
             "\"pl_off\":\"false\","
             "\"val_tpl\": \"{{ value_json."+ object_id +" }}\",";
    }
    else if (entity_type == "button") {
      info = "\"entity_category\": \""+ entity_category + "\","
             "\"cmd_t\": \""+ topic_Xlyric + "command/" +  entity_type + "/" + object_id + "\","
             "\"pl_prs\": \"{ \\\""+object_id+"\\\" : \\\"1\\\"  } \",";
    }
    return info;
  }

// setter mod_mac
public: void Set_node_mac(String setter) {
    node_mac=setter;
  }

private: String IPaddress = WiFi.localIP().toString();
         String node_mac = WiFi.macAddress().substring(12,14)+ WiFi.macAddress().substring(15,17);


         String node_id = String("BMS-") + node_mac;
         String topic_switch = "homeassistant/switch/"+ node_id +"/";
         String topic_switch_state = "homeassistant/switch/";
         String HA_device_declare() {
         String IPaddress = WiFi.localIP().toString();
    String info = R"(
            "dev": {
                "ids": ")" + node_id + R"(",
                "name": ")" + node_id + R"(",
                "sw": "BMS )" + String(VERSION) + R"(",
                "mdl": "ESP8266 )" + IPaddress +
            R"(",
                "mf": "Cyril Poissonnier",
                "cu": "http://)" + IPaddress + R"("
            }
              )";
    return info;
  }


public: void HA_discovery(){

    // protection contre les variables non définies
    if (name == "none") {return; }

    String topic = "homeassistant/"+ entity_type +"/"+ node_id +"/";
    String topic_Xlyric = "Xlyric/"+ node_id +"/";

    String device = R"(
      {
        "name": ")" + name + R"(",
        "obj_id": "BMS-)" + object_id + "-" + node_mac + R"(",
        "uniq_id": ")" + node_mac + "-" + object_id + R"(",
        "stat_t": ")" + topic_Xlyric + "sensors/" + object_id + "/state" + R"(",
        "avty_t": ")" + topic_Xlyric + "status\","
                    + HA_sensor_type()
                    + icon
                    + retain
                    + expire_after
                    + HA_device_declare() +
                    "}";

    if (object_id.length() != 0) {
      client.publish(String(topic+object_id+"/config").c_str(), device.c_str(),true);  // déclaration autoconf BMS
    }
    else {
      client.publish(String(topic+"config").c_str(), device.c_str(),true);   // déclaration autoconf BMS
    }

  }

public: void send(String value){
      String topic = "Xlyric/"+ node_id +"/sensors/";
      String message;
      JsonDocument doc;
      // si value est un int ou float 
      if (value.toFloat() != 0) {
        doc[object_id] = value.toFloat();
      }
      else {
        doc[object_id] = value.c_str();
      }
      serializeJson(doc, message);
      client.publish(String(topic + object_id + "/state").c_str(), message.c_str(), retain_flag);
  }
};

/// création des sensors
HA HA_temp;
HA HA_voltage;

void devices_init(){

    HA_temp.Set_name("Temperature");
    HA_temp.Set_object_id("temperature");
    HA_temp.Set_dev_cla("temperature");
    HA_temp.Set_unit_of_meas("°C");
    HA_temp.Set_stat_cla("measurement");
    HA_temp.Set_entity_category("temperature");
    HA_temp.Set_entity_type("sensor");
    HA_temp.Set_icon("mdi:thermometer");
    
    HA_voltage.Set_name("Voltage");
    HA_voltage.Set_object_id("voltage");
    HA_voltage.Set_dev_cla("voltage");
    HA_voltage.Set_unit_of_meas("V");
    HA_voltage.Set_stat_cla("measurement");
    HA_voltage.Set_entity_category("voltage");
    HA_voltage.Set_entity_type("sensor");
    HA_voltage.Set_icon("mdi:flash");



}
/// function reconnect 
void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
        client.setServer(MQTT_SERVER, MQTT_PORT);
        client.setKeepAlive(120);
        client.setBufferSize(1024);
        client.connect(HOSTNAME, MQTT_USER, MQTT_PASSWORD);
      // Attempt to connect
      if (client.connect(HOSTNAME)) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        String node_mac = WiFi.macAddress().substring(12,14)+ WiFi.macAddress().substring(15,17);
        String topic_Xlyric = "Xlyric/BMS-" + node_mac +"/";;
        client.publish(String(topic_Xlyric +"status").c_str(),"online",true);

        // déclaration des sensors
        HA_temp.HA_discovery();
        HA_voltage.HA_discovery();
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
}



// task mqtt

void mqtt_task() {
    if (!client.connected()) {
      reconnect();
    }
    //client.loop();
    HA_temp.send(String(dallas.temperature));
    HA_voltage.send(String(voltage.voltage));
    client.loop();
}


#endif  // MQTT