# AnotherSoilSensor

[![CodeFactor](https://www.codefactor.io/repository/github/appdevelopmentandsuch/anothersoilsensor/badge)](https://www.codefactor.io/repository/github/appdevelopmentandsuch/anothersoilsensor)

Soil Moisture Logger using NodeMCU, Capacitive Soil Mosutre Sensor v1.2, sending data either using MQTT, or pulling directly from device's REST API

## Components

|                                                                   Capacitive Soil Moisture Sensor v1.2                                                                    |                                                         NodeMCU 1.0 (ESP-12 Module)                                                          |
| :-----------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------: |
| <img src="https://user-images.githubusercontent.com/73759882/120107299-2f373f80-c126-11eb-969a-d285b51d4b6e.jpg" alt="Capacitive Soil Moisture Sensor v1.2" width="200"/> | <img src="https://user-images.githubusercontent.com/22528729/105792624-5a7a0a00-5f4d-11eb-8d6b-925c647c68b1.jpg" alt="NodeMCU" width="200"/> |
|              [Buy Capacitive Soil Moisture Sensor v1.2 on Amazon (CA)](https://www.amazon.ca/Gikfun-Capacitive-Corrosion-Resistant-Detection/dp/B07H3P1NRM)               |           [Buy NodeMCU 12E on Amazon (CA)](https://www.amazon.ca/KeeYees-Internet-Development-Wireless-Compatible/dp/B07S5Z3VYZ/)            |

## Wiring

<img src="https://user-images.githubusercontent.com/22528729/120115959-6ff57f80-c14b-11eb-9ac0-5149d37bce63.png" alt="Wiring" width="200"/>

## Quick Start

1. Download and install Arduino IDE

2. Go to `File -> Preferences` and under `Additional Boards Manager URLs` enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json`

3. Install the necessary libraries by going to `Tools -> Manage Libraries...` and filtering on the libraries below.

```bash
ArduinoJson Version 6.18.0
ArduinoMQTTClient Version 0.1.5
```

4. Navigate to `Tools -> Boards -> ESP8266 Boards` and select `NodeMCU 1.0 (ESP-12 Module)`.

5. Plug your board into your computer and select the appropriate `Port` in `Tools -> Port`, for example mine was `/dev/ttyUSB0`.

6. You can either `Verify` the sketch, to see if everything compiles without error, or you can `Upload` the sketch, which will compile it anyway and warn you of any issues then.

7. (Debugging) Open the `Serial Monitor` to `115200`, and you should be able to tell if your device connects to Wifi, and if so, what its IP address is.

## Usage

### Configuration

AnotherSoilSensor is designed to be easy to setup and use. Without any prior configuration, you should be able to flash a device and use immediately.

**NOTE**
The data produced for consumption by either the REST API or the MQTT Broker is represented as a percentage, from 0% - 100%. These values used for determining the mositure percentage are stored in `constants.h` as `VALUE_AIR` and `VALUE_WATER`, where `VALUE_AIR` is the value read from the sensor when it is exposed to air, and `VALUE_WATER` is the value read from the sensor when it is almost completely submerged.

These values were determined through experimentation with an example project in the Arduino IDE library. If the set values are not representative of your device, run an Analog Input example on your device and observe the output to acquire the corresponding values.

Once flashed, using a computer with Postman, open up your WiFi settings and find the network `AnotherSoilSensor` which you can login to using the **password** `password`.

Once connected to the network `AnotherSoilSensor`, in Postman, configure the below JSON body and send:

**POST** `http://192.168.4.1/api/config/`

```bash
Raw JSON Body
{
    "ssid": "", //WiFi SSID to connect to
    "pass": "", //WiFi Password for connection
    "mqttBroker": "", //The IP address or hostname for an MQTT broker
    "mqttPort": 1883, //The port number of the MQTT broker
    "mqttUser":"", //A username for a valid MQTT user
    "mqttPass":"", //The password for the valid MQTT user
    "restUser":"", //The username you wish to use going forward to make authenticated requests to the device
    "restPass":"", //The password you wish to use going forward to make authenticated requests to the device
    "service": 1 //1 for REST, 2 for MQTT
}
```

Also valid ways to configure:

**POST** `http://192.168.4.1/api/config/`

```bash
// REST Configuration
Raw JSON Body
{
    "ssid": ""
    "pass": ""
    "restUser":"",
    "restPass":"",
    "service": 1
}
```

**POST** `http://192.168.4.1/api/config/`

```bash
// MQTT Configuration
Raw JSON Body
{
    "ssid": "",
    "pass": "",
    "mqttBroker": "",
    "mqttPort": 1883,
    "mqttUser":"",
    "mqttPass":"",
    "service": 2
}
```

If your device received and processed your configuration, you should receive a response like this:

```bash
// Device Response
{
    "success": true,
    "identifier": "##:##:##:##:##:##"
}
```

Otherwise, you will receive one of a possible few messages, indicating what corrections should be made.

The device will automatically reboot and attempt to connect to WiFi using the `ssid` and `pass` you provided. If it is unable to connect for whatever reason, it will revert to the configure stage again and you will be able to again attempt to configure the endpoint.

#### Reset Device

To clear any previous configuration and restore the default one, press the `Flash` button on your device.

### REST API

You should be able to query the API by opening an API application such as Postman, setting `Authentication` to `Basic Auth`, setting `Username` and `Password` to what you set `restUser` and `restPass` to, and setting the URL to one of the possible endpoints, i.e. `http://[device_ip]/api/read/moisture/`, and getting a result back, i.e.

```bash
{
    "moisture": 80,
    "identifier": "##:##:##:##:##:##"
}
```

#### Documentation

**GET** `http://[device_ip]/api/read/moisture/`

```bash
{
"moisture": 80,
"identifier": "##:##:##:##:##:##"
}
```

**GET** `http://[device_ip]/api/info/`

```bash
{
"identifier": "##:##:##:##:##:##",
"version": "#.#.#"
}
```

**WARNING** The current REST API server setup is not a very secure method of protecting your endpoints, as the username and password are simply base64 encoded and can be read VERY easily as the server is not HTTPS encrypted. This is HOPEFULLY a temporary measure until something sturdier is put in place.

### MQTT

Using an MQTT application such as MQTT Explorer, you should be able to see `moisture` as root topics, with the device's `identifier` as a sub-topic, i.e. `moisture/##:##:##:##:##:##: 80`
