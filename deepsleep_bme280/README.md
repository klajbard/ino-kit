# NodeMCU and BME-280 sensor send data over MQTT with deepsleep enabled

## Wiring

BME280 | NodeMCU |
:---: | :---: |
VIN | 5V |
GND | GND |
SCL | GPIO 2(D4) |
SDA | GPIO 0(D3) |

## Setup
Set Wifi and MQTT credentials
```cpp
#define mqtt_user "MQTT_USERNAME"
#define mqtt_password "MQTT_PASSWORD"
// ...
const char* ssid = "WIFI_SSID";
const char* ss_pswd = "WIFI_PASSWORD";
const char* mqtt_server = "MQTT_SERVER_IP";
```

## How it works
1. Wakes up
2. Reads from BME-280 sensor
3. Connects to Wifi
4. Sends data as JSON to `sensor/nodemcubme` topic (`humidity`, `temperature`, `pressure`)
5. Goes to sleep for 30 minutes then goes to step 1