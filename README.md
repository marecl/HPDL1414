# HPDL1414 Library

Get those gorgeous 14-segment displays to work.

### Are they though?
YES!

### Connection

|Arduino|HPDL1414|Name|
|-|-|-|
|D7|1|D5|
|D6|2|D4|
|A0|3|!WE|
|A1|4|A1|
|A2|5|A0|
|5V|6|Vcc|
|GND|7|GND|
|D2|8|D0|
|D3|9|D1|
|D4|10|D2|
|D5|11|D3|
|D8|12|D6|

### Adding more segments
1. Connect all pins in parallel *except* for the !WE pin.
2. Add segment's !WE pin to the code
3. Done

### Examples
SegmentTest.ino - Test one/more segments. Every segment will be counted.

### Limitations
These displays display limited set of characters (ASCII 32-95) but works with small letters too (now).

### Does it work?
![Of course it does!](/testing.jpg)

### [Documentation](https://media.digikey.com/pdf/Data%20Sheets/Avago%20PDFs/HPDL-1414.pdf)