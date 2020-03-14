#include <HPDL1414.h>

/*
 * This example shows how character overflow works
 * 
 * You can choose what to do when printing too many characters:
 *    (false) Omit them
 *    (true)  Print at the beginning of the display
 * 
 */
const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {A2, A1}; // Segment address pins: A0, A1
const byte wrenPins[] = {A0}; // Right to left

HPDL1414 d(&dataPins[0], &addrPins[0], &wrenPins[0], sizeof(wrenPins));

void setup() {
  d.begin();
}

bool flip = true;

void loop() {
  d.clear();
  d.printOverflow(flip);
  for (uint8_t a = 0; a < d.segments() * 4; a++) {
    d.print("TEST", a);
    delay(750);
    d.clear();
  }

  flip = !flip;
}