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

#ifndef _BUILTINS_H_
#define _BUILTINS_H_

#include "shell_defs.h"

typedef int (*builtin_func)(CMD *cmd);

typedef struct {
	/* name of the command that will be used to run it */
	char *cmd;
	/* function pointer pointing to the function needed to run the command */
	builtin_func func;
} BUILTIN;

/*
 * Defines the function get_builtin implemented in builtins/builtin.c
 */
/*
 * Checks if the given `cmd` is builtin, if it is returns the function pointer
 * for that command. If it isn't returns NULL.
 */
extern builtin_func get_builtin(char *cmd);

/*
 * Defines the function builtin_exit implemented in builtins/exit.c
 */
/*
 * Exits the shell with the args[1], defaults to 1, won't return.
 */
extern int builtin_exit(CMD *cmd);

/*
 * Defines the function builtin_cd implemented in builtins/cd.c
 */
/*
 * Command `cd`, gets the `abs_path`, then changes the directory to that
 * directory.
 */
extern int builtin_cd(CMD *cmd);

/*
 * Defines the function builtin_echo implemented in builtins/echo.c
 */
/*
 * Command `echo`. Echo the strings(s) to standard output.
 */
extern int builtin_echo(CMD *cmd);

/*
 * Defines the function builtin_pwd implemented in builtins/pwd.c
 */
/*
 * Command `pwd`. Prints the name of the current (a.k.a. working) directory to
 * standard out.
 */
extern int builtin_pwd(CMD *cmd);

/*
 * Defines the function builtin_help implemented in builtins/help.c
 */
/*
 * Command `help`. Displays information about builtin commands.
 */
extern int builtin_help(CMD *cmd);

/*
 * Defines the function builtin_export implemented in builtins/
 * TODO: DECIDE ON PLACEMENT
 */
/*
 * Command `export`. Sets export attribute for shell variables.
 */
extern int builtin_export(CMD *cmd);

/*
 * Defines the function builtin_unset implemented in builtins/
 * TODO: DECIDE ON PLACEMENT
 */
/*
 * Command `unset`. Unset values and attributes of shell variables and
 * functions.
 */
extern int builtin_unset(CMD *cmd);

/*
 * Defines the function builtin_env implemented in builtins/
 * TODO: DECIDE ON PLACEMENT
 */
/*
 * Command `env`. Sets environment and runs the given command with that
 * enviroment.
 */
extern int builtin_env(CMD *cmd);

/*
 * Defines the function builtin_history implemented in builtins/history.c
 */
/*
 * Command `history`. Displays or manipulates the history list.
 */
extern int builtin_history(CMD *cmd);

/*
 * Defines the function builtin_type implemented in builtins/type.c
 */
/*
 * Command `type`. Displays information about command type.
 */
extern int builtin_type(CMD *cmd);

/*
 * Defines the function builtin_alias implemented in builtins/alias.c
 */
/*
 * Command `alias`. Defines or displays aliases.
 */
extern int builtin_alias(CMD *cmd);

/*
 * Defines the function builtin_source implemented in builtins/
 * TODO: DECIDE ON PLACEMENT
 */
/*
 * Command `source`. Executes commands from a file in the current shell.
 */
extern int builtin_source(CMD *cmd);

#endif /* _BUILTINS_H_ */
