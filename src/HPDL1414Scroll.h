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
		HPDL1414Scroll(byte _data[7], byte _address[2],
		               byte _wren[], byte _count);

		/* Init important(er) stuff */
		void begin(void) override;

		/* Print whatever you want */
		virtual size_t write(byte data) override;
		virtual size_t write(byte* data, byte size);

		/* But remember to display */
		void display(void);

		/* Scrolling */
		int8_t scroll(void);						// you want to call this every now and then when activated scrollAuto
		int8_t scrollStop(void);					// stop auto-scroll
		int8_t scrollManual(void);					// manual scroll (single step)
		void scrollAuto(uint32_t interval);			// start autoscroll. default 100ms
		void scrollReset(void);						// reset scroll settings
		void scrollBoundaries(byte start, byte end);// beginning and end of scroll (shifts entire buffer)
		void scrollDirection(bool lr);				// self-descriptive enough I think

		/* Buffered string manipulation */
		void setCharAt(byte pos, char data);		// in buffer
		char charAt(byte pos);						// in buffer

		/* Clears buffer and display */
		virtual void clear(void) override;
		
		/* Set buffer cursor at */
		void setBufferCursor(byte pos);

	private:
		/* Text buffer */
		byte* buffer;
		byte bufferPos;
		/* Scroll internals */
		byte scrollOffset;
		byte scrollStart;
		byte scrollEnd;
		uint32_t scrollInterval;
		uint32_t nextScroll;
};

#endif //HPDL1414SCROLL_H