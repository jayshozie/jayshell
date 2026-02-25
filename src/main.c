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

#include "execute.h"
#include "parser.h"
#include "shell_defs.h"
#include "shell_state.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Readline uses the type 'FILE', but doesn't include <stdio.h>, so we have to
 * move it at after that, although the ordering is messed up that way.
 */
#include <readline/readline.h>

int status = 0;
char *command;
char **tokens; /* DYNAMICALLY ALLOCATED BY THE TOKENIZER */

int main()
{
	init_shell_state();
	while (true) {
		if ((command = readline("$ ")) != NULL) {
			tokens = lexer(command);
			free(command);
			tokens = expand_tilde(tokens);
			CMD *head = parser(tokens);
			if ((status = exec_cmds(head)) != 0) {
				fprintf(stderr,
					"[ERROR] Something went wrong. $? : %d\n",
					status);
			}
			free_cmds(head);
		} else {
			free(command);
			exit(1);
		}
	}
}
