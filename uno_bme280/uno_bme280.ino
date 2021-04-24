#include <Adafruit_BME280.h>

// ** I2C **
Adafruit_BME280 bme;

// ** SPI **
// Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);
// #define BME_SCK 13
// #define BME_MISO 12
// #define BME_MOSI 11
// #define BME_CS 10

float temperature, humidity, pressure;

void setup() {  
  Serial.begin(115200);
  delay(200);
  bme.begin(0x76);
  delay(1000);
}

void loop() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("hPa");

  delay(5000);
}
