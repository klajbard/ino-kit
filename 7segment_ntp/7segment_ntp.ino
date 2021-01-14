#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <TM1637Display.h>
#include <WiFiUdp.h>

static const char *ssid = "WIFI_SSID";
static const char *pswd = "WIFI_PW";
static const long offset = 3600;
bool dot = true;

TM1637Display display(4 /* CLK */, 5 /* DIO */);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", offset);

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  display.setBrightness(0x00);
}

void loop()
{
  timeClient.update();
  if (dot)
  {
    display.showNumberDec(timeClient.getHours() * 100 + timeClient.getMinutes());
  }
  else
  {
    display.showNumberDecEx(timeClient.getHours() * 100 + timeClient.getMinutes(), 0x40);
  }
  dot = !dot;
  Serial.println(timeClient.getHours() * 100 + timeClient.getMinutes());
  delay(1000);
}
