#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

#define EEPROM_BUFFER_SIZE 200
#define EEPROM_TEXT_SIZE 30

char ssid[EEPROM_TEXT_SIZE] = "";
char pass[EEPROM_TEXT_SIZE] = "";
char *ap_ssid = "esp32_wifi";
char *ap_pass = "esp32_pass";

void setup() {
  Serial.begin(115200);
  Serial.println("\nDevice is running");
  getWifiSettingFromEeprom(ssid, pass);
  initWifi(ssid, pass, ap_ssid, ap_pass);
  initServer();
}

void loop() {}
