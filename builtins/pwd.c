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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_pwd(CMD *cmd)
{
	int status = 0;
	const char *cwd;
	if ((cwd = getenv("PWD")) == NULL) {
		status = errno;
		fprintf(stderr,
			"[ERROR] Couldn't get environment variable 'PWD'. errno: %d\n",
			status);
	}
	printf("%s\n", cwd);
	return status;
}
