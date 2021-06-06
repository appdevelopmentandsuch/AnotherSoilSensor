#include "constants.h"
#include "mqtt.h"
#include "sensor_dht.h"
#include "sensor_moisture.h"
#include "utils.h"
#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include <string.h>

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

// MQTT Methods
void handleMQTTSetup() {
  DynamicJsonDocument settings = loadConfig();
  const char* mqttUser = settings[JSON_KEY_MQTT_USER];
  const char* mqttPass = settings[JSON_KEY_MQTT_PASS];

  if(!(mqttUser == "" || mqttPass == "")) {
    mqttClient.setUsernamePassword(mqttUser, mqttPass);
  }

  const char* mqttBroker = settings[JSON_KEY_MQTT_BROKER];
  int mqttPort = settings[JSON_KEY_MQTT_PORT];
  int tries = 0;

  while (!mqttClient.connect(mqttBroker, mqttPort) && tries < MQTT_MAX_TRIES) {
    delay(DELAY_SETUP);
    tries += 1;
  }

  if(!mqttClient.connected() || tries > MQTT_MAX_TRIES) {
    ESP.reset();
  }
}

String buildTopic(String root) {
  return root + "/" + WiFi.macAddress();
}

void sendMqttMessage(String topic, String message) {
    mqttClient.beginMessage(topic);
    mqttClient.print(message);
    mqttClient.endMessage();
}

void handleMQTT() {
  mqttClient.poll();

  DynamicJsonDocument settings = loadConfig();
  int sensorConfig = settings[JSON_KEY_SENSOR_CONFIG];

  long moisture = readMoisture();
  sendMqttMessage(buildTopic(TOPIC_MOISTURE), String(moisture));

  if(sensorConfig == SENSOR_CONFIG_SOIL_TEMP) {
    float humidity = readHumidity();
    float temperature = readTemperature();

    sendMqttMessage(buildTopic(TOPIC_TEMPERATURE), String(temperature));
    sendMqttMessage(buildTopic(TOPIC_HUMIDITY), String(humidity));
  }
  
  int mqttUpdateInterval = settings[JSON_KEY_MQTT_UPDATE_INTERVAL];
  delay(mqttUpdateInterval);
}