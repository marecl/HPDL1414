# HPDL1414 Arduino Library

Arduino wrapper for HPDL1414, 14-segment displays.

### Functionality
The library consists of the most basic commands for these displays. They have quite limited character range and don't support custom glyphs.

### Configuration
Data pins D0 to D6. 
```
const byte dataPins[7] = {/* D0, D1, ..., D6 */};
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
For basic use you won't need more than these:

```
hpdl.print()
hpdl.clear()
hpdl.setCursor(byte pos)
```

### Scrolling
This release of HPDL1414 library includes text scrolling via ```HPDL1414Scroll.h```.  
To use new features just create ```HPDL1414Scroll``` object. Everything is printed to a buffer, so don't forget to call  ```display()```.  
Scrolling moves the *entire* buffer in both ways.  
Default buffer size is equal to the display. That means if you have 2 displays the buffer is 8 bytes, if you have 3 it's 12 etc.  
You can provide external buffer with ```begin(char* bufptr, byte size)```. When in doubt, just use default ```begin()```.  
Note that ```printOverflow()``` doesn't make sense when you use default text buffer. You should use ```printBufferOverflow()``` instead.

### Examples
Base library is very simple and straightforward. You want something printed - you got it.  
Scrolling however needs some explaination.  
##### HPDL1414.h
SegmentTest - Test one/more segments. Every segment will be counted  
OverflowExample - Printing overflowing characters at the beginning of the display  

##### HPDL1414Scroll.h
ScrollExample - Scrolling text from left to right  
ScrollBufferExample - Manipulating buffer contents  
ScrollPong - Word floating left-right  
ScrollAdvancedBuffer - Manipulating both buffer and printing positions  
ScrollBufferOverflow - Printing overflowing characters at the beginning of the display  
ScrollCustomBuffer - Using custom text buffer for greater flexibility

### Limitations
These displays work on limited set of characters (ASCII 32-95). Library has built-in "translator" for lowercase letters.  

### Does it work?
![Of course it does!](/res/testing.jpg)

### [HPDL1414 Documentation](https://media.digikey.com/pdf/Data%20Sheets/Avago%20PDFs/HPDL-1414.pdf)

#### Consider donating?
I'm just a student tinkering around in my free time. Nothing says "thanks" better than a bottle of *beverage* ;)  

ETH: 0x402071e3a4969B0FB5Cc8A894F83f0a1Ce627c06  
DOT: 1aRoKeqeR3hpknjf65926TR5xb8H55JuZEMrtweUCRjAPVZ  
RVN: RNVB2UTYXW8XRTtmKU4GcxsitkS4Jai2gX  
