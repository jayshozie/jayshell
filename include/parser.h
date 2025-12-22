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

#ifndef _PARSER_H_
# define _PARSER_H_

#include "shell_defs.h"
#include <stdio.h>
#include <string.h>

/*
 * TODO: IMPLEMENT
 * handle_quotes()
 * parse_redirection()
 * parse_pipeline()
 * tilde_expansion() or something similar that checks char by char
 */

/*
 * Temporary solution for tilde expansion. We will switch to a full Bison/Flex
 * parser in the future.
 */
extern char** expand_tilde(char** args);

/*
 * Defines the function tokenize implemented in parser.c.
 * Gets line, tokenizes it with the " " (space) character, returns tokens.
 */
extern char** tokenize(char* line);

#endif /* _PARSER_H_ */
