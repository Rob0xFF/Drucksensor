#include <ZSC31050Serial.h>

uint8_t ZSC31050Serial::parseSerialCommand(void)
{
  busy = 1;
  while (Serial.available()) {
    serialCommand[serialCommandIndex] = Serial.read();
//     if (serialCommand[serialCommandIndex] == firstValidChar) {
//       serialCommandIndex = 0;
//       serialCommand[0] = firstValidChar;
//     }
    if (serialCommand[serialCommandIndex] == CR || serialCommand[serialCommandIndex] == COLON) {
      serialCommandIndex = 0;
      return 1;
    } else {
      serialCommandIndex++;
    }
  }
  busy = 0;
  return 0;
}

void ZSC31050Serial::handleSerialCommand(void)
{
  busy = 1;
  connected = 1;
  if (serialCommand[0] == 'I' || serialCommand[0] == 'i' ) {
    if (serialCommand[2] == 'T' || serialCommand[2] == 't') {
      delay(200);
    }
    Wire.beginTransmission(hexchar2int(3, 2));
    if (serialCommand[1] == 'W' || serialCommand[1] == 'w') {
      for (uint16_t i = 0; i < decchar2int(5, 3); i++) {
        Wire.write(hexchar2int(8 + 2 * i, 2));
      }
      Wire.endTransmission();
      Serial.write(ACK);
      Serial.write(CR);
      Serial.write(LF);
    }
    if (serialCommand[1] == 'R' || serialCommand[1] == 'r') {
      uint8_t result[16];
      Wire.requestFrom(hexchar2int(3, 2), (uint8_t) decchar2int(5, 3));
      for (uint16_t i = 0; i < decchar2int(5, 3); i++) {
        result[i] = Wire.read();
      }
      Serial.write(ACK);
      for (uint16_t i = 0; i < decchar2int(5, 3); i++) {
        char tmp[3];
        sprintf(tmp, "%02X", result[i]);
        Serial.print(tmp);
      }
      Serial.write(CR);
      Serial.write(LF);
    }
  }
  if (serialCommand[0] == 'V' || serialCommand[0] == 'v') {
    Serial.write(ACK);
    Serial.print("V2.05 ");
    Serial.write(AT);
    Serial.print(" ZMD AG 2004 - CB");
    Serial.write(CR);
    Serial.write(LF);
  }
  if (serialCommand[0] == 'T' || serialCommand[0] == 't') {
    if (serialCommand[1] != '_' && serialCommand[1] != 'W' && serialCommand[1] != 'w' && serialCommand[1] != '0') {
      triggerDelay = decchar2int(3, 3);
    }
    if (serialCommand[1] == '0') {
      connected = 0;
    }
    Serial.write(ACK);
    Serial.write(CR);
    Serial.write(LF);
  }
  if (serialCommand[0] == 'P' || serialCommand[0] == 'p') {
    if (serialCommand[1] == 'R' || serialCommand[1] == 'r' || serialCommand[1] == 'T' || serialCommand[1] == 't' || serialCommand[1] == 'S' || serialCommand[1] == 's') {
      Serial.write(ACK);
      Serial.print('1');	 // DUMMY value
      Serial.write(CR);
      Serial.write(LF);
    }
  }
  if (serialCommand[0] == 'S' || serialCommand[0] == 's') {
    char buf[7];
    memcpy(buf, & serialCommand[1], 6);
    buf[7] = '\0';
    float slope = atof(buf);
    EEPROM.put(senChipID * 8, slope);
    Serial.write(ACK);
    Serial.print(slope, 4);
    Serial.write(CR);
    Serial.write(LF);
  }
  if (serialCommand[0] == 'O' || serialCommand[0] == 'o') {
    char buf[7];
    memcpy(buf, & serialCommand[1], 6);
    buf[7] = '\0';
    float offs = atof(buf);
    EEPROM.put(senChipID * 8 + 4, offs);
    Serial.write(ACK);
    Serial.print(offs, 4);
    Serial.write(CR);
    Serial.write(LF);
  }
  busy = 0;
}

uint8_t ZSC31050Serial::isBusy(void)
{
  return busy;
}

uint8_t ZSC31050Serial::isConnected(void)
{
  return connected;
}

void ZSC31050Serial::disConnect(void)
{
  connected = 0;
}

uint8_t ZSC31050Serial::hexchar2int(uint8_t start, uint8_t length)
{
  char buf[3];
  memcpy(buf, & serialCommand[start], 2);
  buf[2] = '\0';
  uint8_t retVal = (uint8_t) strtol(buf, NULL, 16);
  return retVal;
}

uint16_t ZSC31050Serial::decchar2int(uint8_t start, uint8_t length)
{
  char buf[4];
  memcpy(buf, & serialCommand[start], 3);
  buf[3] = '\0';
  uint16_t retVal = (uint16_t) strtol(buf, NULL, 10);
  return retVal;
}