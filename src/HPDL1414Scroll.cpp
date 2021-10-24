/*
    HPDL1414 Arduino Library

    Copyright (C) 2021  Marek Ledworowski (@marecl)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "HPDL1414Scroll.h"

/*
	to self: add method for adding external buffer
*/

HPDL1414Scroll::HPDL1414Scroll(byte* _data, byte* _address,
                               byte* _wren, byte _count)
{
	dp = _data;
	ap = _address;
	wr = _wren;
	c = _count;
	maxcap = c * 4;
};

void HPDL1414Scroll::begin(void)
{
	buffer = new char[maxcap];
	cursorPos = 0;
	bufferPos = 0;
	printOvf = false;

	scrollReset();

	for(byte a = 0; a < 7; a++)
	{
		pinMode(dp[a], OUTPUT);
		digitalWrite(dp[a], LOW);
	}
	for(byte a = 0; a < 2; a++)
	{
		pinMode(ap[a], OUTPUT);
		digitalWrite(ap[a], LOW);
	}
	for(byte a = 0; a < c; a++)
	{
		pinMode(wr[a], OUTPUT);
		digitalWrite(wr[a], HIGH);
	}
};

// won't allow writing more than the buffer can handle
size_t HPDL1414Scroll::write(byte data)
{
	if(bufferPos >= maxcap)
		return 0;

	this->buffer[bufferPos++] = translate(data);
	return 1;
}

size_t HPDL1414Scroll::write(uint8_t* data, uint8_t size)
{
	uint8_t r = 0;
	while((cursorPos < maxcap) && (r < size))
		buffer[cursorPos++] = data[r++];

	return r;
}

void HPDL1414Scroll::display()
{
	byte bp = 0;
	while(true)
	{
		if(bp >= maxcap) break;
		if(cursorPos >= maxcap)
		{
			if(printOvf)
				cursorPos = 0;
			else break;
		}

		put(cursorPos++, buffer[bp++]);
	}
}

/* They return how far the text is scrolled */
int8_t HPDL1414Scroll::scroll(void)		// auto-scroll loop
{
	if(nextScroll == 0) return 0;
	if(millis() < nextScroll) return 0;

	scrollManual();
	nextScroll = millis() + scrollInterval;
}

int8_t HPDL1414Scroll::scrollStop(void)   // stop auto-scroll loop
{
	nextScroll = 0;
}

int8_t HPDL1414Scroll::scrollManual(void)	// single step
{
	Serial.println("Scrolled");
}

void HPDL1414Scroll::scrollBoundaries(byte start, byte end)
{
	scrollStart = start;
	scrollEnd = end;
}

void HPDL1414Scroll::scrollDirection(bool lr)
{

}

void HPDL1414Scroll::scrollAuto(uint32_t interval = 100) // start auto-scroll
{
	scrollInterval = interval;
	nextScroll = millis() + scrollInterval;
}

void HPDL1414Scroll::scrollReset(void)
{
	scrollOffset = 0;
	nextScroll = 0;
	scrollInterval = 100;
	scrollStart = 0;
	scrollEnd = maxcap;
}

void HPDL1414Scroll::setCharAt(byte pos, char data)
{
	if(pos < maxcap)
		buffer[pos] = translate(data);
}

char HPDL1414Scroll::charAt(byte pos)
{
	if(pos < maxcap)
		return buffer[pos];
	return 0;
}

void HPDL1414Scroll::clear(void)
{
	/* Set characters to zero */
	for(byte a = 0; a < 7; a++)
		digitalWrite(dp[a], LOW);

	/* Activate all segments */
	for(byte a = 0; a < c; a++)
		digitalWrite(wr[a], LOW);

	/* Sweep all address lines */
	for(byte a = 0; a < 4; a++)
		setDigit(a);

	/* De-activate all segments back */
	for(byte a = 0; a < c; a++)
		digitalWrite(wr[a], HIGH);

	memset(buffer, ' ', maxcap);
	cursorPos = 0;
	bufferPos = 0;
};

void HPDL1414Scroll::setBufferCursor(byte pos)
{
	bufferPos = (pos >= maxcap) ? bufferPos : pos;
}