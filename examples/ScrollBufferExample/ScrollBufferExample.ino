#include <HPDL1414Scroll.h>

/*
   Buffer string manipulation example

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

  // change is stored in text buffer
  hpdl.setCharAt(1, 'o');
  // and now being displayed
  hpdl.display();

  delay(1000);

  // custom cursor position in buffer
  hpdl.setBufferCursor(1);
  // print something
  hpdl.print("APE");
  hpdl.display();
}

void loop() {

}