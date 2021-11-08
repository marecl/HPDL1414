#include <HPDL1414.h>

/*

  Segment numeration example

*/

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8};	// Segment data pins: D0 - D6
const byte addrPins[2] = {9, 10};				// Segment address pins: A0, A1
const byte wrenPins[] = {11};					// Write Enable pins (left to right)

HPDL1414 hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

void setup()
{
  hpdl.begin();
  hpdl.printOverflow(true);
  hpdl.clear();
  hpdl.print("DTST");
  delay(1000);
  hpdl.clear();

  /* List all connected segments */
  for (uint8_t a = 0; a < hpdl.segments(); a++)
    hpdl.print("SEG" + String(a + 1));
}

void loop()
{

}