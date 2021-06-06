#include "constants.h"
#include "sensor_dht.h"
#include "DHT.h"
#include <Arduino.h>

float readTemperature() {
    DHT dht(DHT_PIN, DHT_TYPE);
    dht.begin();
    return dht.readTemperature();
}

float readHumidity() {
    DHT dht(DHT_PIN, DHT_TYPE);
    dht.begin();
    return dht.readHumidity();
}