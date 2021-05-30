#include "constants.h"
#include "sensor_moisture.h"
#include <Arduino.h>

long readMoisture() {
    int sensorValue = analogRead(MOISTURE_PIN);
    return map(sensorValue, VALUE_AIR, VALUE_WATER, VALUE_MIN, VALUE_MAX);
}