#include <ZSC31050Serial.h>

uint8_t ZSC31050Serial::parseSerialCommand(void)
{
  busy = 1;
  while (Serial.available()) {
    serialCommand[serialCommandIndex] = Serial.read();
    if (serialCommand[serialCommandIndex] == firstValidChar) {
      serialCommandIndex = 0;
      serialCommand[0] = firstValidChar;
    }
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
      uint8_t result[decchar2int(5, 3)];
      Wire.requestFrom(hexchar2int(3, 2), decchar2int(5, 3));
      for (uint16_t i = 0; i < decchar2int(5, 3); i++) {
        result[i] = Wire.read();
      }
      Serial.write(ACK);
      for (uint16_t i = 0; i < decchar2int(5, 3); i++) {
        char tmp[2];
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
    if (serialCommand[1] != '_' && serialCommand[1] != 'W' && serialCommand[1] != 'w') {
      triggerDelay = decchar2int(3, 3);
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
  busy = 0;
}

uint8_t ZSC31050Serial::isBusy(void)
{
  return busy;
}

uint8_t ZSC31050Serial::hexchar2int(uint8_t start, uint8_t length)
{
  char buf[length + 1];
  memcpy(buf, & serialCommand[start], length);
  buf[length + 1] = '\0';
  uint8_t retVal = (uint8_t) strtol(buf, NULL, 16);
  return retVal;
}

uint16_t ZSC31050Serial::decchar2int(uint8_t start, uint8_t length)
{
  char buf[length + 1];
  memcpy(buf, & serialCommand[start], length);
  buf[length + 1] = '\0';
  uint16_t retVal = (uint16_t) strtol(buf, NULL, 10);
  return retVal;
}