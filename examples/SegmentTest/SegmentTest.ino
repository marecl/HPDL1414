#include <HPDL1414.h>

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {A2, A1}; // Segment address pins: A0, A1
const byte wrenPins[] = {A0}; // Right to left

HPDL1414 d(&dataPins[0], &addrPins[0], &wrenPins[0], sizeof(wrenPins));

void setup() {
  d.begin();
  d.printOverflow(true);
  d.clear();
  d.print("DTST");
  delay(1000);
  d.clear();

  /* List all connected segments */
  for (uint8_t a = 0; a < sizeof(wrenPins); a++)
    d.print("SEG" + String(a + 1));
}

void loop() {
}