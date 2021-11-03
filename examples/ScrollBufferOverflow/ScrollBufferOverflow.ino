#include <HPDL1414Scroll.h>

/*
   HPDL1414Scroll text buffer overflow example

*/
const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {A1, A2}; // Segment address pins: A0, A1
const byte wrenPins[] = {A0}; // Write Enable pins (left to right)

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

void setup() {
  hpdl.begin();
  hpdl.print("TEST");
  hpdl.display();

  delay(1000);

  // Won't show anything at the beginning
  hpdl.printBufferOverflow(false);
  hpdl.print("AA"); // No effect
  hpdl.display();

  delay(1000);

  // Will show overflowed characters
  hpdl.printBufferOverflow(true);
  hpdl.print("BB");
  hpdl.display();
}

void loop() {

}
