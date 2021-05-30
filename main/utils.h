#ifndef UTILS_H
#define UTILS_H

#include <ArduinoJson.h>
#include <stdlib.h>
#include <string.h>

bool setDefaultServerConfig();
bool storeConfig(DynamicJsonDocument doc);
DynamicJsonDocument loadConfig();
void printConfig(DynamicJsonDocument doc);
void printMessage(String message);
void printlnMessage(String message);

#endif