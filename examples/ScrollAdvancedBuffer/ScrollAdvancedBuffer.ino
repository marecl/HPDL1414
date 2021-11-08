#include <HPDL1414Scroll.h>

/*

   Advanced buffer example
   This shows a difference between cursorPos and bufferCursorPos

*/

const byte dataPins[7] = {2, 3, 4, 5, 6, 7, 8};	// Segment data pins: D0 - D6
const byte addrPins[2] = {9, 10};				// Segment address pins: A0, A1
const byte wrenPins[] = {11};					// Write Enable pins (left to right)

HPDL1414Scroll hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));

int characters;

void setup()
{
  hpdl.begin();
  hpdl.clear();

  // This will start writing at the first digit of the display
  hpdl.print("XD");
  hpdl.display();

  delay(1000);

  // This will print string above but on 3rd digit
  hpdl.setCursor(2);
  hpdl.display();

  delay(1000);

  // Now change the first element of the buffer
  // But it will print on the 3rd again due to setCursor, which is semi-permanent
  hpdl.setBufferCursor(0);
  hpdl.print(":");
  hpdl.display();

  delay(1000);

  // Now shift everything to the left
  // getCursor will return 1
  hpdl.scrollToLeft();
  hpdl.display();

  delay(1000);

  // Now shift everything to the right
  // getCursor will return 2
  hpdl.scrollToRight();
  hpdl.display();

  delay(1000);

  // And reset the initial cursor position
  hpdl.scrollReset();
  hpdl.display();

  delay(1000);

  // Even though the cursor is at 0, it doesn't mean that buffer cursor is also at 0!
  hpdl.print("O");
  hpdl.display();

  delay(1000);

  hpdl.clear();
  hpdl.print("<3");
  hpdl.display();
}

void loop()
{

}
