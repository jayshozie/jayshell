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

#ifndef _SHELL_STATE_H_
# define _SHELL_STATE_H_

#include "shell_defs.h"

/* GLOBAL VARIABLES */
extern char shell_cwd[PATH_MAX_SIZE];
extern char shell_oldpwd[PATH_MAX_SIZE];
extern const char* usr_home;
extern bool is_valid_oldpwd;

/* Initialization function */
void init_shell_state(void);

/* Helper to update state safely */
int update_cwd(void);

#endif /* _SHELL_STATE_H_ */
