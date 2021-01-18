#include <SD.h>;
#include <DHT.h>;

DHT dht(2, DHT22);
File logFile;

void setup()
{
  Serial.begin(115200);
  dht.begin();
  SD.begin(10);
}

void loop()
{
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  unsigned long logTime = millis();
  logFile = SD.open("data.log", FILE_WRITE);
  if (logFile)
  {
    Serial.println("Printing to file...");
    logFile.print(logTime);
    logFile.print(" - ");
    logFile.print(temp);
    logFile.print(" °C, ");
    logFile.print(hum);
    logFile.println(" %.");
    logFile.close();
  }
  else
  {
    Serial.println("Something wrong happened.");
  }
  delay(30 * 1000);
}
