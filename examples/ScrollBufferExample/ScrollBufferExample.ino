#include <HPDL1414Scroll.h>

/*

   Buffer string manipulation example

*/

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {9, 10};               // Segment address pins: A0, A1
const byte wrenPins[] = {11};                   // Write Enable pins (left to right)

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

void setup()
{
  if (!hpdl.begin())
  {
    // Serial.println("Can't allocate buffer memory!");
    while (true)
      ;
  }
  hpdl.print("TEST");
  hpdl.display();

  delay(1000);

  // Change is stored in text buffer
  // hpdl.setCharAt(1, 'o');
  hpdl[1] = 'o';
  // And now being displayed
  hpdl.display();

  delay(1000);

  // Custom cursor position in buffer
  hpdl.setBufferCursor(1);
  // Print something
  hpdl.print("APE");
  hpdl.display();
}

void loop()
{
}