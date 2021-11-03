#include <HPDL1414.h>

/*
   This example shows how character overflow works

   You can choose what to do when printing too many characters:
      (false) Truncate characters
      (true)  Print at the beginning of the display

*/
const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {A1, A2}; // Segment address pins: A0, A1
const byte wrenPins[] = {A0}; // Write Enable pins (left to right)

HPDL1414 hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

void setup() {
  hpdl.begin();
}

bool flip = true;

void loop() {
  hpdl.clear();
  hpdl.printOverflow(flip);
  for (uint8_t a = 0; a < hpdl.segments() * 4; a++) {
    hpdl.setCursor(a);
    hpdl.print("TEST");
    delay(750);
    hpdl.clear();
  }

  flip = !flip;
}