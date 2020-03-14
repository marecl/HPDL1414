#ifndef HPDL1414_H
#define HPDL1414_H

#include "Arduino.h"
#include <string.h>

/*
   Pinout (notch on case is pin 1):
    1 - D5         7 - GND
    2 - D4         8 - D0
    3 - !WREN      9 - D1
    4 - A1        10 - D2
    5 - A0        11 - D3
    6 - Vcc       12 - D6

    All arrays: LSB to MSB / right to left
    Data: 7
    Address: 2
    WREN: How many you have
    Count: segments
*/

/* Note to self: Plz use stream for printing */
class HPDL1414 {
  public:
    HPDL1414(const byte*, const byte*,
             const byte*, const byte);
    void begin(void);
	
	/* Print anything */
    void print(String);
    void print(const char*);
    void printChar(char);
	
	/* Print strings beginning on specific index */
    void print(String, uint8_t);
    void print(const char*, uint8_t);
    void printChar(char, byte);
	
	/* Misc */
    void clear(void);
    void printOverflow(bool);
    uint8_t segments(void);

  private:
    char translate(char);
    void setDigit(byte);
    const byte* dp;  // Data
    const byte* ap;  // Address
    const byte* wr;  // !Write Enable
    const byte c;    // Segments
    bool printOvf;
    byte bytesWritten;
};

#endif //HPDL1414_H
