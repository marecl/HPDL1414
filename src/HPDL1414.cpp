#include "HPDL1414.h"

HPDL1414::HPDL1414(const byte* _data, const byte* _address,
                   const byte* _wren, const byte _count)
  : dp(_data), ap(_address), wr(_wren), c(_count), maxcap(_count * 4) {

  cursorPos = 0;
  printOvf = false;
};

void HPDL1414::begin(void) {
  for (byte a = 0; a < 7; a++) {
    pinMode(dp[a], OUTPUT);
    digitalWrite(dp[a], LOW);
  }
  for (byte a = 0; a < 2; a++) {
    pinMode(ap[a], OUTPUT);
    digitalWrite(ap[a], LOW);
  }
  for (byte a = 0; a < this->c; a++) {
    pinMode(wr[a], OUTPUT);
    digitalWrite(wr[a], HIGH);
  }
  cursorPos = 0;
};

size_t HPDL1414::write(uint8_t data) {
  if (cursorPos >= this->maxcap) {
    if (printOvf) cursorPos = cursorPos % (this->c * 4);
    else return 0;
  }

  byte seg = (cursorPos - (cursorPos % 4)) / 4;
  setDigit(3 - (cursorPos % 4));

  data = translate(data);
  for (byte x = 0; x < 7; x++)
    digitalWrite(dp[x], ((data >> x) & 0x01));

  digitalWrite(wr[seg], LOW);
  delayMicroseconds(1); // Needs ~150ns so it's okay
  digitalWrite(wr[seg], HIGH);
  delayMicroseconds(1);

  cursorPos++;
  return 1;
}

void HPDL1414::clear(void) {
  /* Set characters to zero */
  for (byte a = 0; a < 7; a++)
    digitalWrite(dp[a], LOW);

  /* Activate all segments */
  for (byte a = 0; a < this->c; a++)
    digitalWrite(wr[a], LOW);

  /* Sweep all address lines */
  for (byte a = 0; a < 4; a++)
    this->setDigit(a);

  /* De-activate all segments back */
  for (byte a = 0; a < this->c; a++)
    digitalWrite(wr[a], HIGH);

  cursorPos = 0;
};

void HPDL1414::setCursor(unsigned short pos) {
  cursorPos = pos;
}

/* Decide if overflowing characters should be printed */
void HPDL1414::printOverflow(bool a) {
  printOvf = a;
};

/* Check how many segments are configured */
unsigned short HPDL1414::segments(void) {
  return this->c;
}

char HPDL1414::translate(char i) {
  if (i > 31 && i < 96) return i;
  else if (i > 96 && i < 123) return i - 32;
  return 32;
}

/* Particular digit of a segment */
void HPDL1414::setDigit(byte a) {
  digitalWrite(ap[0], a & 0x01);
  digitalWrite(ap[1], a & 0x02);
};