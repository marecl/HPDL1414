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
#ifndef HPDL1414SCROLL_H
#define HPDL1414SCROLL_H

#include "Arduino.h"
#include "HPDL1414.h"

class HPDL1414Scroll : public HPDL1414
{
	public:
		/* 7 data pins [D0:D6], address [A0:A1], write enable [L:R], number of displays */
		HPDL1414Scroll(const byte _data[7], const byte _address[2],
		               const byte _wren[], const byte _count);

		/* Init important(er) stuff */
		virtual void begin(void) override;
		void begin(char*, byte);

		/* Print whatever you want */
		virtual size_t write(byte data) override;

		/* But remember to display */
		void display(void);
		/* Cursor manipulation */
		virtual void setCursor(int8_t pos) override;
		virtual int8_t getCursor(void) override;

		/* Scrolling. Basically setCursor but faster and more intuitive */
		void scrollToLeft(void);
		void scrollToRight(void);
		void scrollReset(void);

		/* Buffered string manipulation */
		void setCharAt(byte pos, char data);		// in buffer
		char charAt(byte pos);						// in buffer

		/* Clears buffer and display */
		virtual void clear(void) override;

		/* Set buffer cursor at */
		void setBufferCursor(byte pos);
		/* Allow overflowing characters in buffer */
		void printBufferOverflow(bool bufovf);

	private:

		void _beginScroll();

		bool printBufOvf;

		/* Text buffer */
		uint8_t buflen;
		char* buffer;
		byte bufferPos;
		/* Scroll internals */
		signed short scrollOffset;
		byte scrollStart;
		byte scrollEnd;
};

#endif //HPDL1414SCROLL_H