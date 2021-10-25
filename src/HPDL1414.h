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

#ifndef HPDL1414_H
#define HPDL1414_H

#include "Arduino.h"
#include "Print.h"
#include <string.h>

/*
	to self: change translate to substitute value directly without a function call
	document defines
	make defines work (in scroll too!)
*/

/*
	Uncomment to skip checking/correcting incoming characters
	By doing this you hereby promise to use uppercase letters only
*/
//#define NO_ASCII_CHECK
/*
	All invalid cursor settings are clamped at max
	This define will make invalid values valid
	This affects both buffer and display
*/
//#define NO_CURSOR_CLAMP


class HPDL1414 : public Print
{
	public:
		/* 7 data pins [D0:D6], address [A0:A1], write enable [L:R], number of displays */

		// make this all const again or die trying
		HPDL1414(byte _data[7], byte _address[2],
		         byte _wren[], byte _count);

		/* Init important stuff */
		virtual void begin(void);

		/* Print whatever you want */
		virtual size_t write(byte data);

		/* Buffered string manipulation */
		void setCharAt(byte pos, char data);	// in buffer
		char charAt(byte pos);					// in buffer

		/* Clears buffer and display */
		virtual void clear(void);
		/* Sets display cursor only */
		void setCursor(byte pos);

		/* Misc */
		void printOverflow(bool);
		byte segments(void);

	protected:
		/* In case if using HPDL1414Scroll */
		HPDL1414();
		/* Current cursor position */
		byte cursorPos;
		/* Misc */
		bool printOvf;

		void _begin();
		void _clear();
		void put(byte, char);
		char translate(char);
		void setDigit(byte);
		byte* dp;  // Data
		byte* ap;  // Address
		byte* wr;  // !Write Enable
		byte c;    // Segments
		byte maxcap; // Max digits
};

#endif //HPDL1414_H