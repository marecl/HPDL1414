/*
    HPDL1414 Arduino Library

    Copyright (C) 2020  Marek Ledworowski (@marecl)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef HPDL1414_H
#define HPDL1414_H

#include "Arduino.h"
#include "Print.h"
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

class HPDL1414 : public Print {
  public:
    HPDL1414(const byte[7], const byte[2],
             const byte[], const byte);
    void begin(void);

    /* Print whatever you want */
    virtual size_t write(uint8_t);

    /* Misc */
    void clear(void);
    void setCursor(unsigned short);
    void printOverflow(bool);
    unsigned short segments(void);

  private:
    char translate(char);
    void setDigit(byte);
    const byte* dp;  // Data
    const byte* ap;  // Address
    const byte* wr;  // !Write Enable
    const byte c;    // Segments
    const byte maxcap; // Max digits
    bool printOvf;
    byte cursorPos;
};

#endif //HPDL1414_H