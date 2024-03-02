void initWifi(char* ssid, char* pass, char* ap_ssid, char* ap_pass) {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_MODE_APSTA);
  WiFi.onEvent(handleWifiAPStart, ARDUINO_EVENT_WIFI_AP_START);
  WiFi.onEvent(handleWifiSTAConnected, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(handleWifiSTADisconnected, ARDUINO_EVENT_WIFI_STA_LOST_IP);

  Serial.printf("[Wifi] Setting: ssid=%s, pass=%s\n", ssid, pass);
  Serial.printf("[Wifi] AP Setting: ssid=%s, pass=%s\n", ap_ssid, ap_pass);
  WiFi.softAP(ap_ssid, ap_pass);
  WiFi.begin(ssid, pass);

  // http://esp32.local/
  if (!MDNS.begin("esp32")) Serial.println("[MDNS] Error starting mDNS");
}

void handleWifiSTADisconnected(arduino_event_id_t event) {
  Serial.println("[Wifi] STA Disconnected");
  WiFi.mode(WIFI_MODE_APSTA);
}

void handleWifiAPStart(arduino_event_id_t event) {
  Serial.print("[Wifi] AP_IP: ");
  Serial.println(WiFi.softAPIP());
}

void handleWifiSTAConnected(arduino_event_id_t event) {
  Serial.print("[Wifi] STA_IP: ");
  Serial.println(WiFi.localIP());
  WiFi.mode(WIFI_MODE_STA);
}
