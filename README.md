## ESP-32 WiFi setting
This project is an example of setting WiFi using an API.

### Connect to wifi with the name `esp32_wifi` and password `esp32_pass`
```bash
# Health check
$ curl -L -X GET "http://esp32.local/health"

# List all wifi
$ curl -L -X GET "http://esp32.local/wifi/list"

# Wifi setting
$ curl -L -X POST "http://esp32.local/wifi/setting" \
-H "Content-Type: application/json" \
-d "{
    \"ssid_name\": \"<ssid_name>\",
    \"ssid_pass\": \"<ssid_pass>\"
}"
```