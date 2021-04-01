#ifndef envChamber_h
#define envChamber_h

#include "Arduino.h"
#include "new.h"

class EnvChamber
{
  public:

    EnvChamber(HardwareSerial & s, char id) : serialHandler(s), deviceID(id) {serialHandler.begin(9600);};

    uint8_t readSerial(void);

    void handleSerial(void);

    void ack(void);

    void nak(void);

    void sendRequest(void);

    void newSetpoint(float t, float h);

    HardwareSerial & serialHandler;

  private:

    void checkSum(char * str, char * checksum);

    char deviceID;
    char checksum[3];
    char serialCommand[128];
    uint8_t serialCommandIndex = 0;
    uint8_t lastCommand = 0;

    float T = 0.0;
    float H = 0.0;
    float T1 = 0.0;
    float TS = 0.0;
    float HS = 0.0;
    char errCode[3] = "--";
    uint16_t digitalCh = 0;

    const char STX = 0x02;
    const char ETX = 0x03;
    const char ACK = 0x06;
    const char NAK = 0x15;
    const char NUL = 0x00;

};
#endif