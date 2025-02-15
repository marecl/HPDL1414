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

/* Create just like normal HPDL1414 object */
HPDL1414Scroll::HPDL1414Scroll(const byte *_data, const byte *_address,
							   const byte *_wren, const byte _count)
	: HPDL1414(_data, _address, _wren, _count){};

bool HPDL1414Scroll::begin(void)
{
	buflen = maxcap;
	buffer = new char[buflen];
	if (buffer == NULL)
		return false;
	_beginScroll();
	return true;
};

bool HPDL1414Scroll::begin(char *bufptr, byte size)
{
	if (bufptr == NULL)
		return false;
	buflen = size;
	buffer = bufptr;
	_beginScroll();
	return true;
};

size_t HPDL1414Scroll::write(byte data)
{
	if (bufferPos >= (buflen))
		if (printBufOvf)
			bufferPos = 0;
		else
			return 0;

	this->buffer[bufferPos++] = translate(data);
	return 1;
}

void HPDL1414Scroll::display()
{
	byte bufferOffset = 0;
	cursorPos = 0;
	if (scrollOffset < 0) // Scrolling to the left
	{
		// Commented out because they are already initialized, but shows they are necessary
		// cursorPos = 0;
		bufferOffset = abs(scrollOffset);
	}
	if (scrollOffset > 0) // Scrolling to the right
	{
		cursorPos = scrollOffset;
		// bufferOffset = 0;
	}

	_clear();

	while (true)
	{
		if (bufferOffset >= buflen)
			break;
		if (cursorPos >= maxcap)
		{
			if (printOvf)
				cursorPos = 0;
			else
				break;
		}

		put(cursorPos++, buffer[bufferOffset++]);
	}
}

/* "Cursor" is a fancy name for scrolled text */
void HPDL1414Scroll::setCursor(int8_t pos)
{
	if (pos > maxcap)
		return;
	if (pos < (-buflen))
		return;

	scrollOffset = pos;
}

int8_t HPDL1414Scroll::getCursor(void)
{
	return scrollOffset;
}

void HPDL1414Scroll::scrollToLeft(void)
{
	setCursor(scrollOffset - 1);
}

void HPDL1414Scroll::scrollToRight(void)
{
	setCursor(scrollOffset + 1);
}

void HPDL1414Scroll::scrollReset(void)
{
	setCursor(0);
}

void HPDL1414Scroll::setCharAt(byte pos, char data)
{
	if (pos < buflen)
		buffer[pos] = translate(data);
}

char HPDL1414Scroll::charAt(byte pos)
{
	if (pos < buflen)
		return buffer[pos];
	return 0;
}

void HPDL1414Scroll::clear(void)
{
	_clear();
	memset(this->buffer, 32, buflen);
	bufferPos = 0;
	scrollOffset = 0;
	cursorPos = 0;
};

void HPDL1414Scroll::setBufferCursor(byte pos)
{
	bufferPos = (pos >= buflen) ? bufferPos : pos;
}

void HPDL1414Scroll::printBufferOverflow(bool bufovf)
{
	printBufOvf = bufovf;
}

char &HPDL1414Scroll::operator[](byte i)
{
	if (i < this->buflen)
		return this->buffer[i];
	return 0;
}

void HPDL1414Scroll::_beginScroll(void)
{
	_begin();
	memset(this->buffer, 32, this->buflen);
	printBufOvf = false;
	bufferPos = 0;
	scrollOffset = 0;
}