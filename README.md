

# HPDL1414 Arduino Library

Arduino library for HPDL1414, 14-segment displays.

### Functionality
The library consists of the most basic commands for these displays. They have quite limited character range and don't support custom glyphs.
Apart from basic functionality, this library provides extra features for text scrolling.

### Configuration
You will need 3 arrays. One for data pins, one for address pins and one for write-enable.  
First two are of fixed size (7 and 2 respectively). Third one is flexible.  
Initialization will look something like this:  
```
const byte dataPins[7] = {/* [D0:D6] */};
const byte addrPins[2] = {/* [A0:A1] */};
const byte wrenPins[] = {/* [L:R] */};

HPDL1414 hpdl(dataPins, addrPins, wrenPins, sizeof(wrenPins));
```

### Connection
Pinout below is used in library examples.
| Physical | Name |Arduino Pin|
|:--------:|:----:|:---------:|
|     1*   |  D5  |     D7    |
|     2    |  D4  |     D6    |
|     3    | !WE  |    D11    |
|     4    |  A1  |    D10    |
|     5    |  A0  |     D9    |
|     6    | Vcc  |     5V    |
|     7    | GND  |    GND    |
|     8    |  D0  |     D2    |
|     9    |  D1  |     D3    |
|    10    |  D2  |     D4    |
|    11    |  D3  |     D5    |
|    12    |  D6  |     D8    |

Pin 1 is marked with a notch.

### Daisychain
1. Connect all pins in parallel **except** for the !WE pins.
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
Scrolling moves the *entire* buffer in both ways. This means characters can "disappear" from both sides.  
Default buffer size is equal to the display. That means if you have 2 displays the buffer is 8 bytes, if you have 3 it's 12 etc.  
You can provide external buffer with ```begin(char* bufptr, byte size)```. When in doubt, just use default ```begin()```.  
Note that ```printOverflow()``` doesn't make sense when you use default text buffer. You should use ```printBufferOverflow()``` instead.

#### Buffer access  
Since buffer is stored as C-style char array it might be unnecessary to use C++-style string operators.  
To get char at selected position you can use normal array operators i.e. ```hpdl[1]```. You must provide a valid character or use ```translate(char)```.

### Examples
Base library is very simple and straightforward. You want something printed - you got it.  
Scrolling however needs some explaination.  
#### HPDL1414.h
SegmentTest - Test one/more segments. Every segment will be counted  
OverflowExample - Printing overflowing characters at the beginning of the display  

#### HPDL1414Scroll.h
ScrollExample - Scrolling text from left to right  
ScrollBufferExample - Manipulating buffer contents  
ScrollPong - Word floating left-right  
ScrollAdvancedBuffer - Manipulating both buffer and printing positions  
ScrollBufferOverflow - Printing overflowing characters at the beginning of the display  
ScrollCustomBuffer - Using custom text buffer for greater flexibility

### Limitations
These displays work on limited set of characters (ASCII 32-95). Library has built-in "translator" for lowercase letters.  
You can disable character validation by defining ```NO_ASCII_TRANSLATION``` before include, or uncommenting it in ```HPDL1414.h``` directly.  

### TODO
Recode assignments to use ```translate``` as little as possible, including operator.  
String validation/automatic translation is also an option. Possibly return current buffer contents.

### Does it work?
![Of course it does!](/res/testing.jpg)

### [HPDL1414 Datasheet](https://media.digikey.com/pdf/Data%20Sheets/Avago%20PDFs/HPDL-1414.pdf)

#### Consider donating?
I'm just a student tinkering around in my free time. Nothing says "thanks" better than a bottle of *beverage* ;)  

ETH: 0x402071e3a4969B0FB5Cc8A894F83f0a1Ce627c06  
DOT: 1aRoKeqeR3hpknjf65926TR5xb8H55JuZEMrtweUCRjAPVZ  
RVN: RNVB2UTYXW8XRTtmKU4GcxsitkS4Jai2gX  
