AsyncWebServer server(80);
DynamicJsonDocument doc(2048);

void initServer() {
  server.on("/health", HTTP_GET, handleHealthCheck);
  server.on("/wifi/list", HTTP_GET, handleWifiList);
  server.addHandler(new AsyncCallbackJsonWebHandler("/wifi/setting", { handleWifiSetting }));
  server.onNotFound(handleNotfound);
  server.begin();
}

void handleHealthCheck(AsyncWebServerRequest *request) {
  String mac_addr = WiFi.macAddress();
  request->send(200, "application/json", "{\"status\":\"ok\",\"mac_address\":\"" + mac_addr + "\"}");
}

void handleWifiList(AsyncWebServerRequest *request) {
  doc.clear();
  doc["status"] = "ok";
  JsonArray data = doc.createNestedArray("data");

  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    JsonObject obj = data.createNestedObject();
    obj["no"] = i + 1;
    obj["ssid"] = WiFi.SSID(i);
    obj["signal_strength"] = WiFi.RSSI(i);
    obj["encryption_flag"] = WiFi.encryptionType(i) != WIFI_AUTH_OPEN;
  }

  String payload;
  serializeJson(doc, payload);

  request->send(200, "application/json", payload);
}

void handleWifiSetting(AsyncWebServerRequest *request, JsonVariant &json) {
  if (request->contentType() != "application/json") {
    request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
    return;
  }

  doc.clear();
  doc = json.as<JsonObject>();

  if (!doc.containsKey("ssid_name") || !doc.containsKey("ssid_pass")) {
    request->send(400, "application/json", "{\"status\":\"error\",\"message\":\"Invalid request\"}");
    return;
  }

  char *ssid = strdup(doc["ssid_name"].as<const char *>());
  char *pass = strdup(doc["ssid_pass"].as<const char *>());

  Serial.printf("[Wifi] Setting: ssid=%s, pass=%s\n", ssid, pass);
  saveWifiSettingToEeprom(ssid, pass);

  request->send(201, "application/json", "{\"status\":\"ok\",\"message\":\"success\"}");
}

void handleNotfound(AsyncWebServerRequest *request) {
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}