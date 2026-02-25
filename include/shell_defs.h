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

#ifndef _SHELL_DEFS_H_
#define _SHELL_DEFS_H_

#ifndef PATH_MAX_SIZE
#define PATH_MAX_SIZE 4096
#endif

#ifndef ARGS_SIZE
#define ARGS_SIZE 255
#endif

#ifndef SPEC_PIDS
#define SPEC_PIDS

#define SENTINEL_PID -1

#endif /* SPEC_PIDS */

#ifndef STRUCT_CMD
#define STRUCT_CMD

typedef enum {
	NONE,
	PIPE, /* the character `|` */
	SEQ, /* the character `;` */
} CON;

typedef struct CMD CMD;
struct CMD {
	char **args; /* e.g. ['bat', '-H', '/home/test/project/main.c'] */

	char *file_in; /* < file.txt */
	char *file_out; /* > file.txt */
	int append_mode; /* true if '>>', false if '>' */
	CON type; /* how is this CMD connected to the next */

	CMD *next; /* next command in the list */
};

#endif /* STRUCT_CMD */

#endif /* _SHELL_DEFS_H_ */
