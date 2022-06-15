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
	Uncomment to skip checking/correcting incoming characters
	By doing this you hereby promise to use uppercase letters only
*/
//#define NO_ASCII_TRANSLATION

class HPDL1414 : public Print
{
public:
	/* 7 data pins [D0:D6], address [A0:A1], write enable [L:R], number of displays */

	// make this all const again or die trying
	HPDL1414(const byte _data[7], const byte _address[2],
			 const byte _wren[], const byte _count);

	/* Init important stuff */
	virtual bool begin(void);

	/* Print whatever you want */
	virtual size_t write(byte data);

	/* Clears  display */
	virtual void clear(void);
	/* Sets display cursor */
	virtual void setCursor(int8_t pos);
	virtual int8_t getCursor(void);

	/* Misc */
	void printOverflow(bool);
	byte segments(void);

protected:
	/* Current cursor position */
	byte cursorPos;
	/* Misc */
	bool printOvf;

	void _begin();
	void _clear();
	void put(byte, char);
	virtual char translate(char);
	void setDigit(byte);
	const byte *dp;	   // Data
	const byte *ap;	   // Address
	const byte *wr;	   // !Write Enable
	const byte c;	   // Segments
	const byte maxcap; // Max digits
};

#endif // HPDL1414_H