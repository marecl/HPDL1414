#include <HPDL1414Scroll.h>

/*
   Another scrolling example
   You will need two displays to run this

*/
const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {A1, A2}; // Segment address pins: A0, A1
const byte wrenPins[] = {A0, A3}; // Write Enable pins (left to right)

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

String ping = "PING";
String pong = "PONG";

int len;
int stop;

void setup() {
  hpdl.begin();

  len = ping.length();
  stop = (hpdl.segments() * 4) - len;
}

void loop() {
  // clear everything
  hpdl.clear();
  // first character on the display
  hpdl.setCursor(0);
  hpdl.print(ping);
  hpdl.display();

  while (hpdl.getCursor() < stop) {
    hpdl.scrollToRight();
    hpdl.display();
    delay(500);
  }

  // clear again
  hpdl.clear();
  // begin printing on stop-th character on the display
  hpdl.setCursor(stop);
  hpdl.print(pong);
  hpdl.display();

  while (hpdl.getCursor() > 0) {
    hpdl.scrollToLeft();
    hpdl.display();
    delay(500);
  }
}
