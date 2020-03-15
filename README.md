# HPDL1414 Arduino Library

Arduino wrapper for HPDL1414, 14-segment displays.

### Functionality
The library consists of the most basic commands for these displays. They have quite limited character range and don't support custom glyphs.

### Configuration
Data pins D0 to D7. 
```
const byte dataPins[7] = {/* D0, D1, ..., D7 */};
```
Address pins A0, A1
```
const byte addrPins[2] = {/* A0, A1 */};
```
!WE (active-low Write Enable) pins.
Add segments from left to right
```
const byte wrenPins[] = {...};
```
And in the end create an object.

```
HPDL1414 hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));
```


### Connection
| HPDL1414 | Arduino |
|----------|---------|
| (1)  D5  |    D7   |
| (2)  D4  |    D6   |
| (3)  !WE |    A0   |
| (4)  A1  |    A2   |
| (5)  A0  |    A1   |
| (6)  Vcc |    5V   |
| (7)  GND |   GND   |
| (8)  D0  |    D2   |
| (9)  D1  |    D3   |
| (10) D2  |    D4   |
| (11) D3  |    D5   |
| (12) D6  |    D8   |

### Daisychain
1. Connect all pins in parallel *except* for the !WE pin.
2. Add segment's !WE pin to the code
3. Done

### What you will care about the most
You can print everything that Arduino would let you on other displays.
In normal use you won't need more than these:

```
hpdl.print()
hpdl.clear()
hpdl.setCursor(unsigned short)
```
### Examples
SegmentTest - Test one/more segments. Every segment will be counted.  
OverflowTest - Change the default behaviour when characters don't fit in the display. Choose between truncating or auto-returning to the most left side.

### Limitations
These displays display limited set of characters (ASCII 32-95) but work with small letters too (now).

### Does it work?
![Of course it does!](/testing.jpg)

### [Documentation](https://media.digikey.com/pdf/Data%20Sheets/Avago%20PDFs/HPDL-1414.pdf)
