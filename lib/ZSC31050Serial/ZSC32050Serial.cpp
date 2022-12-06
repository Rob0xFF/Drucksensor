#include <ZSC31050Serial.h>

uint8_t ZSC31050Serial::parseSerialCommand(void)
{
  busy = 1;
  while (serialHandler.available()) {
    serialCommand[serialCommandIndex] = serialHandler.read();
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
    Wire.beginTransmission(hexchar2int(3));
    if (serialCommand[1] == 'W' || serialCommand[1] == 'w') {
      if (hexchar2int(8) == 0xCC) {  // catch clear EEPROM cmd -> do nothing
        Wire.endTransmission();
        serialHandler.write(ACK);
        serialHandler.write(CR);
        serialHandler.write(LF);
        return;
      }
      for (uint16_t i = 0; i < decchar2int(5); i++) {
        Wire.write(hexchar2int(8 + 2 * i));
      }
      Wire.endTransmission();
      serialHandler.write(ACK);
      serialHandler.write(CR);
      serialHandler.write(LF);
    }
    if (serialCommand[1] == 'R' || serialCommand[1] == 'r') {
      uint8_t result[16];
      Wire.requestFrom(hexchar2int(3), (uint8_t) decchar2int(5));
      for (uint16_t i = 0; i < decchar2int(5); i++) {
        result[i] = Wire.read();
      }
      serialHandler.write(ACK);
      for (uint16_t i = 0; i < decchar2int(5); i++) {
        char tmp[3];
        sprintf(tmp, "%02X", result[i]);
        serialHandler.print(tmp);
      }
      serialHandler.write(CR);
      serialHandler.write(LF);
    }
  }
  if (serialCommand[0] == 'V' || serialCommand[0] == 'v') {
    serialHandler.write(ACK);
    serialHandler.print("V2.05 ");
    serialHandler.write(AT);
    serialHandler.print(" ZMD AG 2004 - CB");
    serialHandler.write(CR);
    serialHandler.write(LF);
  }
  if (serialCommand[0] == 'T' || serialCommand[0] == 't') {
    if (serialCommand[1] != '_' && serialCommand[1] != 'W' && serialCommand[1] != 'w' && serialCommand[1] != '0') {
      triggerDelay = decchar2int(3);
    }
    if (serialCommand[1] == '0') {
      connected = 0;
    }
    serialHandler.write(ACK);
    serialHandler.write(CR);
    serialHandler.write(LF);
  }
  if (serialCommand[0] == 'P' || serialCommand[0] == 'p') {
    if (serialCommand[1] == 'R' || serialCommand[1] == 'r' || serialCommand[1] == 'T' || serialCommand[1] == 't' || serialCommand[1] == 'S' || serialCommand[1] == 's') {
      serialHandler.write(ACK);
      serialHandler.print('1');	 // DUMMY value
      serialHandler.write(CR);
      serialHandler.write(LF);
    }
  }
  if (serialCommand[0] == 'S' || serialCommand[0] == 's') {
    char buf[7];
    memcpy(buf, & serialCommand[1], 6);
    buf[7] = '\0';
    float slope = atof(buf);
    EEPROM.put(senChipID * 8, slope);
    isNewCalibration = 1;
    serialHandler.write(ACK);
    serialHandler.print(slope, 4);
    serialHandler.write(CR);
    serialHandler.write(LF);
  }
  if (serialCommand[0] == 'O' || serialCommand[0] == 'o') {
    char buf[7];
    memcpy(buf, & serialCommand[1], 6);
    buf[7] = '\0';
    float offs = atof(buf);
    EEPROM.put(senChipID * 8 + 4, offs);
    isNewCalibration = 1;
    serialHandler.write(ACK);
    serialHandler.print(offs, 4);
    serialHandler.write(CR);
    serialHandler.write(LF);
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

uint8_t ZSC31050Serial::hexchar2int(uint8_t start)
{
  char buf[3];
  memcpy(buf, & serialCommand[start], 2);
  buf[2] = '\0';
  uint8_t retVal = (uint8_t) strtol(buf, NULL, 16);
  return retVal;
}

uint16_t ZSC31050Serial::decchar2int(uint8_t start)
{
  char buf[4];
  memcpy(buf, & serialCommand[start], 3);
  buf[3] = '\0';
  uint16_t retVal = (uint16_t) strtol(buf, NULL, 10);
  return retVal;
}