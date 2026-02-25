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
#include <stdbool.h>
#include <string.h>

static BUILTIN builtins[] = {
	{ "cd", &builtin_cd },
	{ "exit", &builtin_exit },
	{ "echo", &builtin_echo },
	{ "pwd", &builtin_pwd },
	// FIXME: Rest of the commands are not implemented yet.
	// {"help", &builtin_help},
	// {"export", &builtin_export},
	// {"unset", &builtin_unset},
	// {"env", &builtin_env},
	// {"history", &builtin_history},
	// {"type", &builtin_type},
	// {"alias", &builtin_alias},
	// {"source", &builtin_source},
	{ NULL, NULL },
};

/* returns true if cmd is a built-in command, false if not */
builtin_func get_builtin(char *cmd)
{
	int i = 0;
	BUILTIN *curr = &builtins[i];

	while (curr->cmd) {
		if (strcmp(cmd, curr->cmd) == 0)
			return curr->func;
		else
			curr = &builtins[++i];
	}
	return NULL;
}
