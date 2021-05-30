#ifndef CONFIG_H
#define CONFIG_H

#include "mqtt.h"
#include "rest.h"
#include "constants.h"
#include "stdint.h"

void handleConfigServerSetup();
void handleConfigServer();
void resetConfig();
void setServiceConfig(int service);
bool setDefaultConfig();

typedef struct { 
  uint8_t itemConfig;
  void (*func)(void);
} configDictionary;

const configDictionary setupConfig[] {
  {OPTION_CONFIG, &handleConfigServerSetup},
  {OPTION_REST, &handleServerSetup},
  {OPTION_MQTT, &handleMQTTSetup},
};

const configDictionary runConfig[] {
  {OPTION_CONFIG, &handleConfigServer},
  {OPTION_REST, &handleServer},
  {OPTION_MQTT, &handleMQTT},
};

#endif