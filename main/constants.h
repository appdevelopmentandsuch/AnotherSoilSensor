#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <string.h>
#include <Arduino.h>

#define DEBUG false

#define SERIAL_FREQUENCY 115200

#define DHT_PIN D5
#define DHT_TYPE DHT11

#define MOISTURE_PIN A0

#define BAD_READ -1

#define VALUE_AIR 693
#define VALUE_WATER 333
#define VALUE_MIN 0
#define VALUE_MAX 100

#define DELAY_SETUP 500
#define DELAY_SEND 500
#define DELAY_DISCONNECT 100

#define WEB_SERVER_PORT 80

#define VERSION "0.0.0"

#define WIFI_CHANNEL 9
#define WIFI_VISIBLE 0
#define WIFI_MAX_CONNECTIONS 1
#define WIFI_MAX_TRIES 20

#define MQTT_MIN_UPDATE_INTERVAL 500
#define MQTT_MAX_TRIES 20

#define BUTTON_INPUT 0

#define OPTION_CONFIG 0
#define OPTION_REST 1
#define OPTION_MQTT 2

#define SENSOR_CONFIG_SOIL 0
#define SENSOR_CONFIG_SOIL_TEMP 1

#define ADDRESS_CONFIG 0

#define DOC_SIZE 1024

#define TOPIC_HUMIDITY "humidity"
#define TOPIC_MOISTURE "moisture"
#define TOPIC_TEMPERATURE "temperature"

#define DEFAULT_DEVICE_SSID "AnotherSoilSensor"
#define DEFAULT_DEVICE_PASS "password"

#define JSON_KEY_WIFI_SSID "ssid"
#define JSON_KEY_WIFI_PASS "pass"
#define JSON_KEY_SERVICE_CONFIG "service"
#define JSON_KEY_MQTT_BROKER "mqttBroker"
#define JSON_KEY_MQTT_PORT "mqttPort"
#define JSON_KEY_MQTT_UPDATE_INTERVAL "mqttUpdateInterval"
#define JSON_KEY_MQTT_USER "mqttUser"
#define JSON_KEY_MQTT_PASS "mqttPass"
#define JSON_KEY_REST_USER "restUser"
#define JSON_KEY_REST_PASS "restPass"
#define JSON_KEY_SENSOR_CONFIG "sensorConfig"

#define JSON_KEY_TEMPERATURE "temperature"
#define JSON_KEY_HUMIDITY "humidity"
#define JSON_KEY_MOISTURE "moisture"
#define JSON_KEY_IDENTIFIER "identifier"
#define JSON_KEY_VERSION "version"

#define ENDPOINT_INFO "/api/info/"
#define ENDPOINT_READ_ALL "/api/read/all/"
#define ENDPOINT_READ_HUMIDITY "/api/read/humidity/"
#define ENDPOINT_READ_MOISTURE "/api/read/moisture/"
#define ENDPOINT_READ_TEMPERATURE "/api/read/temperature/"

#define ENDPOINT_CONFIG "/api/config/"

#define HTTP_OK 200
#define HTTP_BAD_REQUEST 400

#define HTTP_TYPE_JSON "text/json"

#define HTTP_MISSING_JSON_BODY "{\n\t\"error\":\"JSON body missing\"}"
#define HTTP_BAD_SERVICE "{\n\t\"error\":\"Invalid service, select 1 for REST or 2 for MQTT.\"}"
#define HTTP_BAD_WIFI_CONFIG "{\n\t\"error\":\"Missing a wifi configuration, please add one.\"}"
#define HTTP_BAD_REST_CONFIG "{\n\t\"error\":\"Invalid REST config, double check the config and try again.\"}"
#define HTTP_BAD_MQTT_CONFIG "{\n\t\"error\":\"Invalid MQTT config, double check the config and try again.\"}"
#define HTTP_ERROR_PARSING_BODY "{\n\t\"error\":\"Unable to parse config.\"}"
#define HTTP_ERROR_UNABLE_TO_STORE_CONFIG "{\n\t\"error\":\"Unable to store config.\"}"


#endif