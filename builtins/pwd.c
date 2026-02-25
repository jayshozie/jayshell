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
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * pwd: pwd [-LP]
 * Print the name of the current working directory.
 *
 * Options:
 *   -L	       print the value of $PWD if it names the current working
 *             directory
 *   -P	       print the physical directory, without any symbolic links
 *
 * By default, `pwd' behaves as if `-L' were specified.
 *
 * Exit Status:
 * Returns 0 unless an invalid option is given or the current directory
 * cannot be read.
 */

int builtin_pwd(CMD *cmd)
{
	int status = 0;
	bool must_free = false;
	char *cwd;
	if ((cwd = getenv("PWD")) == NULL) {
		status = errno;
		fprintf(stderr,
			"[ERROR] Couldn't get environment variable 'PWD'. Falling back to getcwd. errno: %d\n",
			status);
		if ((cwd = getcwd(NULL, 0)) == NULL) {
			/* fallback to getcwd */
			status = errno;
			fprintf(stderr,
				"[ERROR] Fellback to getcwd, but it also failed. errno: %d\n",
				status);
			cwd = "UNKNOWN";
		} else {
			must_free = true;
		}
	}
	printf("%s\n", cwd);
        if (must_free)
                free(cwd);
	return status;
}
