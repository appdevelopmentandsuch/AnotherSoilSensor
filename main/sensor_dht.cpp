#include "constants.h"
#include "sensor_dht.h"
#include "DHT.h"
#include <Arduino.h>

float readTemperature() {
    DHT dht(DHT_PIN, DHT_TYPE);
    dht.begin();
    float temperature = dht.readTemperature();
    if(isnan(temperature)) {
        return BAD_READ;
    }
    return temperature;
}

float readHumidity() {
    DHT dht(DHT_PIN, DHT_TYPE);
    dht.begin();
    float humidity = dht.readHumidity();
    if(isnan(humidity)) {
        return BAD_READ;
    }
    return humidity;
}