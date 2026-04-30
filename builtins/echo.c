/* Jayshell - A shell interpreter that no one should use in their right mind.
Copyright (C) 2025, 2026  Emir Baha Yıldırım

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

/*
 * echo: echo [-neE] [arg ...]
 * Write arguments to the standard output.
 *
 * Display the ARGs, separated by a single space character and followed by a
 * newline, on the standard output.
 *
 * Options:
 *   -n	do not append a newline
 *   -e	enable interpretation of the following backslash escapes
 *   -E	explicitly suppress interpretation of backslash escapes
 *
 * `echo' interprets the following backslash-escaped characters:
 *   \a	alert (bell)
 *   \b	backspace
 *   \c	suppress further output
 *   \e	escape character
 *   \E	escape character
 *   \f	form feed
 *   \n	new line
 *   \r	carriage return
 *   \t	horizontal tab
 *   \v	vertical tab
 *   \\	backslash
 *   \0nnn      the character whose ASCII code is NNN (octal).  NNN can be
 *              0 to 3 octal digits
 *   \xHH       the eight-bit character whose value is HH (hexadecimal).  HH
 *              can be one or two hex digits
 *   \uHHHH	    the Unicode character whose value is the hexadecimal value HHHH.
 *              HHHH can be one to four hex digits.
 *   \UHHHHHHHH the Unicode character whose value is the hexadecimal value
 *              HHHHHHHH. HHHHHHHH can be one to eight hex digits.
 *
 * Exit Status:
 * Returns success unless a write error occurs.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <builtins.h>
#include <shell_defs.h>
#include <string.h>

static uint8_t ERROR = UINT8_MAX;

typedef enum {
	NO_NL = 0x1,  /* Don't add a newline at the end.  -n |  binary: 0001 */
	ESC_BS = 0x2, /* Escape backslash characters.     -e |  binary: 0010 */
} opts;

static inline bool is_valid_opts(const char *arg)
{
	bool is_valid = true;
	const char *valid_chars = "-neE";
	if (arg[0] != '-')
		is_valid = false;
	while (*arg) {
		if (!strchr(valid_chars, *arg))
			is_valid = false;
		arg++;
	}
	return is_valid;
}

static inline uint8_t parse_opts(CMD *cmd, uint64_t *start_index)
{
	uint8_t opts = 0, prev_opts = 0x0;
	bool in_args = true;
	if (!cmd || !cmd->argv)
		return ERROR;
	for (uint64_t i = 1; i < cmd->argc; i++) {
		if (!in_args || cmd->argv[i] == NULL)
			return opts;
		if (cmd->argv[i][0] != '-' || !is_valid_opts(cmd->argv[i])) {
			in_args = false;
			*start_index = i;
		}

		uint64_t j = 1;
		while (cmd->argv[i][j] != '\0' && in_args) {
			if (cmd->argv[i][j] == 'n') {
				opts |= NO_NL;
			} else if (cmd->argv[i][j] == 'e') {
				opts |= ESC_BS;
			} else if (cmd->argv[i][j] == 'E') {
				opts &= ~ESC_BS;
			} else {
				opts |= prev_opts;
				in_args = false;
			}
			prev_opts |= opts;
			j++;
		}
	}
	return opts;
}

static inline uint8_t echo_no_esc(CMD *cmd, uint64_t index)
{
	while (cmd->argv[index]) {
		if (cmd->argv[index][0] == '-')
			index++;
		else
			break;
	}
	while (cmd->argv[index] && index < cmd->argc) {
		printf("%s ", cmd->argv[index]);
		index++;
	}
	return 0;
}

static inline uint8_t echo_esc(CMD *cmd, uint64_t index)
{
	(void)cmd;
	(void)index;
	(void)fprintf(stderr, "[ERROR] TODO: -e flag is not implemented yet.\n");
	return ERROR;
}

int builtin_echo(CMD *cmd)
{
	opts opts;
	uint8_t status = 0;
	uint64_t start_index = 1;

	if (!cmd)
		return ERROR;

	if (!cmd->argv)
		return ERROR;

	/* should theoretically be faster than letting the pipeline do its job */
	if (cmd->argc < 2) {
		printf("\n");
		return 0;
	}

	opts = parse_opts(cmd, &start_index);
	if (opts & ESC_BS)
		status = echo_esc(cmd, start_index);
	else
		status = echo_no_esc(cmd, start_index);

	if (status == ERROR)
		return status;

	if (!(opts & NO_NL))
		printf("\n");

	return status;
}
