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
#define _PARSER_H_

#include "shell_defs.h"
#include <stdbool.h>

/*
 * TODO: IMPLEMENT
 *
 * a general command struct. we need that to support pipelining and redirection.
 * we need a lexer that will go through the entire command line char by char,
 * then when it hits some pre-selected character combinations (e.g., |, ||, >,
 * >>, <, &, &&, etc.), it should stop that command there (except for & because
 * that doesn't split commands), and then use that information to separate the
 * next command from the previous.
 *
 * then, after we build the AST of that line, we should parse the individual
 * commands using our existing parser, giving it only a single command at a
 * time.
 *
 * then the structure just changes like (char** args -> CMD command)
 *
 * handle_quotes()
 * parse_redirection()
 * parse_pipeline()
 */

/*
 * Temporary solution for tilde expansion. We will switch to a full Bison/Flex
 * parser in the future.
 */
extern char **expand_tilde(char **args);

/*
 * Gets the character array, returns tokens.
 */
extern char **lexer(char *args);

/*
 * Gets the tokens, returns the head of the linked list of commands.
 */
extern CMD *parser(char **line);

/*
 * Free's the linked list.
 */
extern void free_cmds(CMD *head);

#endif /* _PARSER_H_ */
