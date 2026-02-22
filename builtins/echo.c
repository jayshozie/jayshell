/* Jayshell - A shell interpreter that no one should use in their right mind.
Copyright (C) 2025  Emir Baha Yıldırım

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#include "builtins.h"
#include "shell_defs.h"
#include <stdio.h>

/*
 * echo: echo [-neE] [arg ...]
 *  Write arguments to the standard output.
 *
 *  Display the ARGs, separated by a single space character and followed by a
 *  newline, on the standard output.
 *
 *  Options:
 *    -n	do not append a newline
 *    -e	enable interpretation of the following backslash escapes
 *    -E	explicitly suppress interpretation of backslash escapes
 *
 *  `echo' interprets the following backslash-escaped characters:
 *    \a	alert (bell)
 *    \b	backspace
 *    \c	suppress further output
 *    \e	escape character
 *    \E	escape character
 *    \f	form feed
 *    \n	new line
 *    \r	carriage return
 *    \t	horizontal tab
 *    \v	vertical tab
 *    \\	backslash
 *    \0nnn	the character whose ASCII code is NNN (octal).  NNN can be
 *  		0 to 3 octal digits
 *    \xHH	the eight-bit character whose value is HH (hexadecimal).  HH
 *  		can be one or two hex digits
 *    \uHHHH	the Unicode character whose value is the hexadecimal value HHHH.
 *  		HHHH can be one to four hex digits.
 *    \UHHHHHHHH the Unicode character whose value is the hexadecimal value
 *  		HHHHHHHH. HHHHHHHH can be one to eight hex digits.
 *
 *  Exit Status:
 *  Returns success unless a write error occurs.
 */
int builtin_echo(CMD *cmd)
{
	int status = 0;

	return status;
}
