#ifndef HPDL1414_H
#define HPDL1414_H

#include <string.h>

/*
   Pinout (notch on case is pin 1):
    1 - D5         7 - GND
    2 - D4         8 - D0
    3 - !WREN      9 - D1
    4 - A1        10 - D2
    5 - A0        11 - D3
    6 - Vcc       12 - D6

    All arrays: LSB to MSB
    Data: 7
    Address: 2
    WREN: How many you have
    Count: segments
*/

class HPDL1414 {
  public:
    HPDL1414(const byte* _data, const byte* _address,
             const byte* _wren, const byte _count)
      : dp(_data), ap(_address), wr(_wren), c(_count) {

      bytesLeft = 0;
      printOvf = false;
      for (byte a = 0; a < c; a++) {
        pinMode(wr[a], OUTPUT);
        digitalWrite(wr[a], HIGH);
      }
      for (byte a = 0; a < 7; a++) {
        pinMode(dp[a], OUTPUT);
        digitalWrite(wr[a], LOW);
      }
      for (byte a = 0; a < 2; a++) {
        pinMode(ap[a], OUTPUT);
        digitalWrite(wr[a], LOW);
      }
    };

    int8_t print(String t) {
      return this->print(t.c_str());
    };

    int8_t print(const char* t) {
      uint8_t l = strlen(t);
      int8_t a = 0;
      for (; ((bytesLeft < c * 4 || printOvf) &&
              (a < l || !printOvf)); a++) {
        printChar(t[a]);
      }
      return a;
    }

    /* Print on next available digit */
    void printChar(char a) {
      if (bytesLeft == c * 4) bytesLeft = 0;
      printChar(a, bytesLeft);
      bytesLeft++;
    };

    /* Print on specific digit (beginning at 0) */
    void printChar(char a, byte pos) {
      pos = (c * 4) - pos - 1;
      setDigit(pos % 4);
      char chr = translate(a);
      for (byte x = 0; x < 7; x++)
        digitalWrite(dp[x], ((chr >> x) & 0x01));

      byte seg = (pos - (pos % 4)) / 4;
      if (seg + 1 >= c) seg = seg % c;
      digitalWrite(wr[seg], LOW);
      delayMicroseconds(1); // Needs ~150ns so it's okay
      digitalWrite(wr[seg], HIGH);
      delayMicroseconds(1);
    };

    /* Particular digit of a segment */
    void setDigit(byte a) {
      digitalWrite(ap[0], a & 0x01);
      digitalWrite(ap[1], a & 0x02);
    };

    void clear() {
      for (byte a = 0; a < c * 4; a++) {
        setDigit(a);
        printChar(' ', a);
      }
      bytesLeft = 0;
    };

    /* Decide if overflowing characters should be printed */
    void printOverflow(bool a) {
      printOvf = a;
    };

  private:
    char translate(char i) {
      if (i > 31 && i < 96) return i;
      else if (i > 96 && i < 123) return i - 32;
      else return 32;
    }
    const byte* dp;
    const byte* ap;
    const byte* wr;// data, address, wren pins
    const byte c;
    bool printOvf;
    byte bytesLeft;
};

#endif //HPDL1414_H
