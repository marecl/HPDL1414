#include <HPDL1414Scroll.h>

/*

   HPDL1414Scroll custom text buffer example

*/

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8}; // Segment data pins: D0 - D6
const byte addrPins[2] = {9, 10};               // Segment address pins: A0, A1
const byte wrenPins[] = {11};                   // Write Enable pins (left to right)

// Initializing buffer 2 times bigger than display
byte buffersize = 8;
char *textbuffer = new char[buffersize];

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

void setup()
{
  if (!hpdl.begin(textbuffer, buffersize))
  {
    // Serial.println("Invalid buffer!");
    while (true)
      ;
  }
  hpdl.printBufferOverflow(false);
  hpdl.printOverflow(false);

  // No suprise, printOverflow is off, so no matter how big is the buffer this won't be printed
  hpdl.print("HPDL1414");
  hpdl.display();

  delay(1000);

  // However this will work fine when scrolling!
  for (short a = 0; a < 4; a++)
  {
    hpdl.scrollToLeft();
    hpdl.display();
    delay(250);
  }

  delay(500);

  for (short a = 0; a < 4; a++)
  {
    hpdl.scrollToRight();
    hpdl.display();
    delay(250);
  }

  delay(1000);

  // Now when you enable printOverflow it will behave just like using base HPDL1414.h
  hpdl.printOverflow(true);
  hpdl.display();

  delay(1000);

  // And the textbuffer is preserved all this time!
  hpdl.printOverflow(false);
  hpdl.display();
}

void loop()
{
}
