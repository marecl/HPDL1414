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

#include "HPDL1414.h"

HPDL1414::HPDL1414(const byte* _data, const byte* _address,
                   const byte* _wren, const byte _count)
	: dp(_data), ap(_address), wr(_wren), c(_count), maxcap(_count * 4) {}

void HPDL1414::begin(void)
{
	_begin();
}

// won't allow writing more than the buffer can handle
size_t HPDL1414::write(byte data)
{
	if(cursorPos >= maxcap)
		return 0;

	put(cursorPos++, translate(data));
	return 1;
}

void HPDL1414::clear(void)
{
	_clear();
};

void HPDL1414::setCursor(byte pos)
{
	cursorPos = (pos >= maxcap) ? cursorPos : pos;
}

/* Decide if overflowing characters should be printed */
void HPDL1414::printOverflow(bool a)
{
	printOvf = a;
};

/* Check how many segments are configured */
byte HPDL1414::segments(void)
{
	return c;
}

void HPDL1414::_begin(void)
{
	cursorPos = 0;
	printOvf = false;

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
}

void HPDL1414::_clear()
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

	cursorPos = 0;
}

void HPDL1414::put(byte pos, char data)
{
	setDigit(pos);
	byte s = (pos - (pos % 4)) / 4;

	for(byte x = 0; x < 7; x++)
		digitalWrite(dp[x], ((data >> x) & 0x01));

	digitalWrite(wr[s], LOW);
	delayMicroseconds(1); // Needs ~150ns so it's okay
	digitalWrite(wr[s], HIGH);
	delayMicroseconds(1);
}

/* For fastest I/O use uppercase only */
char HPDL1414::translate(char i)
{
#ifdef NO_ASCII_CHECK
	return i;
#else
	return((i > 31 && i < 96) ? i : ((i > 96 && i < 123) ? i - 32 : 32));
#endif
}

/* Particular digit of a segment */
void HPDL1414::setDigit(byte a)
{
	digitalWrite(ap[0], !(a & 0x01));
	digitalWrite(ap[1], !(a & 0x02));
};