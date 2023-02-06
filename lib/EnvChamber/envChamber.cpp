#include "envChamber.h"

uint8_t EnvChamber::readSerial(void)
{
  while (serialHandler.available()) {
    serialCommand[serialCommandIndex] = serialHandler.read();
    if (serialCommandIndex == 0 && serialCommand[serialCommandIndex] != STX) {
      return 0;
    }
    if (serialCommand[serialCommandIndex] == ETX) {
      serialCommandIndex = 0;
      return 1;
    } else {
      serialCommandIndex++;
    }
  }
  return 0;
}

void EnvChamber::handleSerial()
{
  if (serialCommand[2] == ACK) {
    lastCommand = 1;
  }
  if (serialCommand[2] == NAK) {
    lastCommand = 0;
  }
  if (serialCommand[2] == 'T') {
    char tStr[6];
    for (uint8_t i = 0; i < sizeof(tStr) - 1; i++) {
      tStr[i] = serialCommand[3 + i];
    }
    tStr[5] = NUL;
    T = atof(tStr);
    if (serialCommand[9] != '-') {
      char hStr[3];
      for (uint8_t i = 0; i < sizeof(hStr) - 1; i++) {
        hStr[i] = serialCommand[9 + i];
      }
      hStr[3] = NUL;
      H = atof(hStr);
    }
    char t1Str[6];
    for (uint8_t i = 0; i < sizeof(t1Str) - 1; i++) {
      t1Str[i] = serialCommand[14 + i];
    }
    t1Str[5] = NUL;
    T1 = atof(t1Str);
    errCode[0] = serialCommand[20];
    errCode[1] = serialCommand[21];
    errCode[2] = NUL;
    char tsStr[6];
    for (uint8_t i = 0; i < sizeof(tsStr) - 1; i++) {
      tsStr[i] = serialCommand[23 + i];
    }
    tsStr[5] = NUL;
    TS = atof(tsStr);
    if (serialCommand[29] != '-') {
      char hsStr[3];
      for (uint8_t i = 0; i < sizeof(hsStr) - 1; i++) {
        hsStr[i] = serialCommand[29 + i];
      }
      hsStr[3] = NUL;
      HS = atof(hsStr);
    }
    digitalCh = 0;
    for (uint8_t i = 0; i < 16; i++) {
      digitalCh |= atoi(serialCommand[32 + i]) << i;
    }
  }
}

void EnvChamber::ack(void)
{
  char requestStr[4];
  requestStr[0] = STX;
  requestStr[1] = deviceID;
  requestStr[2] = ACK;
  requestStr[3] = NUL;
  checkSum(requestStr, checksum);
  serialHandler.print(requestStr);
  serialHandler.print(checksum);
  serialHandler.write(ETX);
}

void EnvChamber::nak(void)
{
  char requestStr[4];
  requestStr[0] = STX;
  requestStr[1] = deviceID;
  requestStr[2] = NAK;
  requestStr[3] = NUL;
  checkSum(requestStr, checksum);
  serialHandler.print(requestStr);
  serialHandler.print(checksum);
  serialHandler.write(ETX);
}

void EnvChamber::sendRequest(void)
{
  char requestStr[4];
  requestStr[0] = STX;
  requestStr[1] = deviceID;
  requestStr[2] = '?';
  requestStr[3] = NUL;
  checkSum(requestStr, checksum);
  serialHandler.print(requestStr);
  serialHandler.print(checksum);
  serialHandler.write(ETX);
}

void EnvChamber::newSetpoint(float t, float h)
{
  char requestStr[29];
  char tStr[6];
  char hStr[3];
  snprintf(tStr, sizeof(tStr), "%05.1f", t);
  snprintf(hStr, sizeof(hStr), "%02.0f", h);
  requestStr[0] = STX;
  requestStr[1] = deviceID;
  requestStr[2] = 'T';
  for (uint8_t i = 0; i < sizeof(tStr) - 1; i++) {
    requestStr[3 + i] = tStr[i];
  }
  requestStr[8] = 'F';
  for (uint8_t i = 0; i < sizeof(hStr) - 1; i++) {
    requestStr[9 + i] = hStr[i];
  }
//   requestStr[11] = '-';
//   requestStr[12] = '-';
  requestStr[11] = 'R';
  requestStr[12] = '1';
  requestStr[13] = '1';
  requestStr[14] = '0';
  requestStr[15] = '0';
  requestStr[16] = '0';
  requestStr[17] = '0';
  requestStr[18] = '0';
  requestStr[19] = '0';
  requestStr[20] = '0';
  requestStr[21] = '0';
  requestStr[22] = '0';
  requestStr[23] = '0';
  requestStr[24] = '0';
  requestStr[25] = '0';
  requestStr[26] = '0';
  requestStr[27] = '0';
  requestStr[28] = '\0';
  checkSum(requestStr, checksum);
  serialHandler.print(requestStr);
  serialHandler.print(checksum);
  serialHandler.write(ETX);
}

// private function

void EnvChamber::checkSum(char * str, char * checksum)
{
  uint8_t l = strlen(str);
  uint8_t b = 0;
  uint8_t j = 0;
  uint8_t k = 0;
  for (uint8_t i = 0; i < l; i++) {
    b -= str[i];
  }
  j = b / 16;
  if (j < 10) {
    j += 48;
  } else {
    j += 55;
  }
  k = b % 16;
  if (k < 10) {
    k += 48;
  } else {
    k += 55;
  }
  checksum[0] = j;
  checksum[1] = k;
  checksum[2] = NUL;
}