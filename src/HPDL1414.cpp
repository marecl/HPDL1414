#include "HPDL1414.h"

HPDL1414::HPDL1414(const byte* _data, const byte* _address,
                   const byte* _wren, const byte _count)
  : dp(_data), ap(_address), wr(_wren), c(_count) {

  bytesWritten = 0;
  printOvf = false;
};

void HPDL1414::begin(void) {
  /* Disable writing first */
  for (byte a = 0; a < 7; a++) {
    pinMode(dp[a], OUTPUT);
    digitalWrite(wr[a], LOW);
  }
  for (byte a = 0; a < 2; a++) {
    pinMode(ap[a], OUTPUT);
    digitalWrite(wr[a], LOW);
  }
  for (byte a = 0; a < c; a++) {
    pinMode(wr[a], OUTPUT);
    digitalWrite(wr[a], HIGH);
  }
};

void HPDL1414::print(String t) {
  return print(t.c_str());
};

void HPDL1414::print(String t, uint8_t pos) {
  print(t.c_str(), pos);
};

/* I guess these two can be optimized */
void HPDL1414::print(const char* t, uint8_t pos) {
  uint8_t l = strlen(t);
  for (int8_t a = 0; (a < l) && (printOvf || (a + pos) < 4 * c); a++) {
    printChar(t[a], a + pos);
  }
}

void HPDL1414::print(const char* t) {
  uint8_t l = strlen(t);
  for (int8_t a = 0; (a < l) && (printOvf || bytesWritten < 4 * c); a++) {
    printChar(t[a], bytesWritten++);
  }
}

/* Print on next available digit */
void HPDL1414::printChar(char a) {
  if (bytesWritten == c * 4) bytesWritten = 0;
  printChar(a, bytesWritten++);
};

/* Print on specific digit (beginning at 0) */
void HPDL1414::printChar(char a, byte pos) {
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
void HPDL1414::setDigit(byte a) {
  digitalWrite(ap[0], a & 0x01);
  digitalWrite(ap[1], a & 0x02);
};

void HPDL1414::clear(void) {
  for (byte a = 0; a < c * 4; a++) {
    setDigit(a);
    printChar(' ', a);
  }
  bytesWritten = 0;
};

/* Decide if overflowing characters should be printed */
void HPDL1414::printOverflow(bool a) {
  printOvf = a;
};

/* Check how many segments are configured */
uint8_t HPDL1414::segments(void) {
  return this->c;
}

char HPDL1414::translate(char i) {
  if (i > 31 && i < 96) return i;
  else if (i > 96 && i < 123) return i - 32;
  else return 32;
}