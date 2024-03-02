void getWifiSettingFromEeprom(char* ssid, char* pass) {
  readEEPROM(EEPROM_TEXT_SIZE, EEPROM_TEXT_SIZE, ssid);
  readEEPROM((2 * EEPROM_TEXT_SIZE), EEPROM_TEXT_SIZE, pass);
}

void saveWifiSettingToEeprom(char* ssid, char* pass) {
  writeEEPROM(EEPROM_TEXT_SIZE, EEPROM_TEXT_SIZE, ssid);
  writeEEPROM(2 * EEPROM_TEXT_SIZE, EEPROM_TEXT_SIZE, pass);
}

void writeEEPROM(int startAdr, int length, char* writeString) {
  EEPROM.begin(EEPROM_BUFFER_SIZE);
  yield();
  for (int i = 0; i < length; i++) EEPROM.write(startAdr + i, writeString[i]);
  EEPROM.commit();
  EEPROM.end();
}

void readEEPROM(int startAdr, int maxLength, char* dest) {
  EEPROM.begin(EEPROM_BUFFER_SIZE);
  delay(10);
  for (int i = 0; i < maxLength; i++) dest[i] = char(EEPROM.read(startAdr + i));
  dest[maxLength - 1] = 0;
  EEPROM.end();
}