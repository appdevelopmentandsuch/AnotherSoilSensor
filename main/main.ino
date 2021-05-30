#include "config.h"
#include "constants.h"
#include "mqtt.h"
#include "rest.h"
#include "utils.h"
#include "wifi.h"
#include <EEPROM.h>
#include <HardwareSerial.h>

int serviceConfig = OPTION_CONFIG;

void setup() {
  if(DEBUG) {
    Serial.begin(SERIAL_FREQUENCY);
  }
  EEPROM.begin(DOC_SIZE);

  handleWifiSetup();

  DynamicJsonDocument settings = loadConfig();

  serviceConfig = settings[JSON_KEY_SERVICE_CONFIG];

  setupConfig[serviceConfig].func();

  pinMode(BUTTON_INPUT, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_INPUT), resetConfig, RISING);
}

void loop() {
  runConfig[serviceConfig].func();
}
