#include "config.h"
#include "constants.h"
#include "utils.h"
#include "wifi.h"
#include <EEPROM.h>
#include <ESP8266WiFi.h>

// Wifi Connection Methods
bool isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void handleNoWifi() {
  printlnMessage("Unable to connect to Wifi, starting device Wifi...");
  setDefaultConfig();
  WiFi.softAP(DEFAULT_DEVICE_SSID, DEFAULT_DEVICE_PASS, WIFI_CHANNEL, WIFI_VISIBLE, WIFI_MAX_CONNECTIONS);
}

void handleWifiSetup() {
  DynamicJsonDocument settings = loadConfig();
  const char* ssid = settings[JSON_KEY_WIFI_SSID]; 
  const char* pass = settings[JSON_KEY_WIFI_PASS]; 

  while(!WiFi.disconnect()) {
    delay(DELAY_SETUP);
  }

  if(ssid != "" && pass != "") {
    printMessage("Connecting with ssid: \""); printMessage(ssid); printMessage("\" and pass: \""); printMessage(pass); printlnMessage("\"");
    WiFi.begin(ssid, pass);

    uint tries = 0;
      while (!isConnected() && tries < WIFI_MAX_TRIES) {
        delay(DELAY_SETUP);
        tries += 1;
      }

    if(isConnected() && tries < WIFI_MAX_TRIES) {
      printlnMessage("WiFi connected.");
      
      printMessage("Got IP: ");  printlnMessage(WiFi.localIP().toString());
      int serviceConfig = settings[JSON_KEY_SERVICE_CONFIG];
      if(serviceConfig > OPTION_MQTT || serviceConfig < OPTION_REST) {
        settings[JSON_KEY_SERVICE_CONFIG] = OPTION_CONFIG;
        storeConfig(settings);
      }
    } else {
      handleNoWifi();
    }
  } else {
    handleNoWifi();
  }
}
