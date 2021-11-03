#include <HPDL1414Scroll.h>

/*
   Text scrolling example
   You can scroll text to either left or right by one character at a time
   You will need two displays to run this
*/

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {A1, A2}; // Segment address pins: A0, A1
const byte wrenPins[] = {A0, A3}; // Write Enable pins (left to right)

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

int characters;

void setup() {
  hpdl.begin();
  characters = hpdl.segments() * 4;

  hpdl.print("TEST");
  hpdl.display();
  delay(1000);
}

void loop() {
  // all the way to the right
  while (hpdl.getCursor() < characters) {
    hpdl.scrollToRight();
    hpdl.display();
    delay(500);
  }
  
  // all the way to the left
  while (hpdl.getCursor() > 0) {
    hpdl.scrollToLeft();
    hpdl.display();
    delay(500);
  }
}
