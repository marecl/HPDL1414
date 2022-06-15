#include <HPDL1414Scroll.h>

/*

   Text scrolling example
   Works best with two displays

*/

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {9, 10};               // Segment address pins: A0, A1
const byte wrenPins[] = {11, 12};               // Write Enable pins (left to right)

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

int characters;

void setup()
{
  if (!hpdl.begin())
  {
    // Serial.println("Can't allocate buffer memory!");
    while (true)
      ;
  }
  characters = hpdl.segments() * 4;

  hpdl.print("TEST");
  hpdl.display();
  delay(1000);
}

void loop()
{
  // All the way to the right
  while (hpdl.getCursor() < characters)
  {
    hpdl.scrollToRight();
    hpdl.display();
    delay(500);
  }

  // All the way to the left
  while (hpdl.getCursor() > 0)
  {
    hpdl.scrollToLeft();
    hpdl.display();
    delay(500);
  }
}
