#include "constants.h"
#include "utils.h"
#include <EEPROM.h>
#include <HardwareSerial.h>
#include <StreamUtils.h>
#include <string.h>

void printMessage(String message) {
  if(DEBUG) {
    Serial.print(message);
  }
}

void printlnMessage(String message) {
  if(DEBUG) {
    Serial.println(message);
  }
}

bool sameConfig(DynamicJsonDocument doc1, DynamicJsonDocument doc2) {
  bool same = true;
  String serializedDoc1;
  String serializedDoc2;

  serializeJson(doc1, serializedDoc1);
  serializeJson(doc2, serializedDoc2);

  return serializedDoc1.equals(serializedDoc2);
}

bool setDefaultServerConfig() {
  DynamicJsonDocument doc(DOC_SIZE);
  char defaultConfig[] = "{\n\t\"ssid\": \"\",\n\t\"pass\": \"\",\n\t\"mqttBroker\": \"\",\n\t\"mqttPort\": 1883,\n\t\"mqttUser\":\"\",\n\t\"mqttPass\":\"\",\n\t\"mqttUpdateInterval\": 5000,\n\t\"restUser\":\"\",\n\t\"restPass\":\"\",\n\t\"service\": 0,\n\t\"sensorConfig\":0\n}";
  
  deserializeJson(doc, defaultConfig);

  DynamicJsonDocument curSettings = loadConfig();

  bool alreadyDefault = sameConfig(doc, curSettings);
  if(alreadyDefault) {
    return alreadyDefault;
  }

  return storeConfig(doc);
}

void printConfig(DynamicJsonDocument doc) {
  int serviceConfig = doc[JSON_KEY_SERVICE_CONFIG];
  const char* ssid = doc[JSON_KEY_WIFI_SSID];
  const char* pass = doc[JSON_KEY_WIFI_PASS];
  const char* mqttBroker = doc[JSON_KEY_MQTT_BROKER];
  int mqttPort = doc[JSON_KEY_MQTT_PORT];
  int mqttUpdateInterval = doc[JSON_KEY_MQTT_UPDATE_INTERVAL];
  const char* mqttUser = doc[JSON_KEY_MQTT_USER];
  const char* mqttPass = doc[JSON_KEY_MQTT_PASS];
  const char* restUser = doc[JSON_KEY_REST_USER];
  const char* restPass = doc[JSON_KEY_REST_PASS];
  int sensorConfig = doc[JSON_KEY_SENSOR_CONFIG];

  printlnMessage("\n===========================================");
  printMessage("serviceConfig: "); printlnMessage(String(serviceConfig));
  printMessage("ssid: "); printlnMessage(String(ssid));
  printMessage("pass: "); printlnMessage(String(pass));
  printMessage("mqttBroker: "); printlnMessage(String(mqttBroker));
  printMessage("mqttPort: "); printlnMessage(String(mqttPort));
  printMessage("mqttUpdateInterval: "); printlnMessage(String(mqttUpdateInterval));
  printMessage("mqttUser: "); printlnMessage(String(mqttUser));
  printMessage("mqttPass: "); printlnMessage(String(mqttPass));
  printMessage("restUser: "); printlnMessage(String(restUser));
  printMessage("restPass: "); printlnMessage(String(restPass));
  printMessage("sensorConfig: "); printlnMessage(String(sensorConfig));
  printlnMessage("\n===========================================");
}

DynamicJsonDocument loadConfig() {
  DynamicJsonDocument doc(DOC_SIZE);
  EepromStream eepromStream(ADDRESS_CONFIG, DOC_SIZE);
  deserializeJson(doc, eepromStream);

  return doc;
}

bool storeConfig(DynamicJsonDocument doc) {
  EepromStream eepromStream(ADDRESS_CONFIG, DOC_SIZE);
  serializeJson(doc, eepromStream);
  if(EEPROM.commit()) {
    printlnMessage("Wrote config to EEPROM");
    printConfig(loadConfig());
  } else {
    printlnMessage("Config was not written to EEPROM");
  }
}
