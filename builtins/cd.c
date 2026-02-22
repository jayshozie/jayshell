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
#include "shell_state.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int builtin_cd(CMD *cmd)
{
	char **args = cmd->args;
	int status = 0;
	char *dirname;

	if (args[1] != NULL && args[2] != NULL) {
		/* Too many arguments error implemented. */
		fprintf(stderr, "[ERROR] Too many arguments.\n");
	} else {
		if (args[1] == NULL || args[1][0] == '\0') {
			/* empty args[1] implemented, POSIX compliance */
			if (chdir(getenv("HOME")) != 0) {
				status = errno;
				fprintf(stderr,
					"[ERROR] Couldn't get environment variable 'HOME'. "
					"errno: %d\n",
					status);
			} else {
				if ((status = update_cwd()) != 0) {
					fprintf(stderr,
						"[ERROR] update_cwd had an error. errno: %d\n",
						status);
				}
			}
		} else if (strcmp(args[1], "-") == 0) {
			if (is_valid_oldpwd !=
			    true) { /* defined in shell_state.h */
				status = 1;
				fprintf(stderr,
					"[ERROR] OLD_PWD not set yet.\n");
			} else {
				/* cd - implemented, POSIX compliance */
				if (chdir(getenv("OLDPWD")) != 0) {
					status = errno;
					fprintf(stderr,
						"[ERROR] Failed while changing 'PWD' to 'OLDPWD'. "
						"errno: %d\n",
						status);
				} else {
					if ((status = update_cwd()) != 0) {
						fprintf(stderr,
							"[ERROR] update_cwd had an error. errno: %d\n",
							status);
					}
					printf("%s\n", getenv("PWD"));
				}
			}
		} else {
			dirname = args[1];
			if (chdir(dirname) != 0) {
				status = errno;
				fprintf(stderr,
					"[ERROR] Couldn't change directory. errno: %d\n",
					status);
			} else {
				if ((status = update_cwd()) != 0) {
					fprintf(stderr,
						"[ERROR] update_cwd had an error. errno: %d\n",
						status);
				}
			}
		}
	}
	return status;
}
