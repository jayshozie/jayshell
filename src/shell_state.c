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

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "shell_defs.h"
#include "shell_state.h"

/* GLOBAL VARIABLES */
char shell_cwd[PATH_MAX_SIZE];
char shell_oldpwd[PATH_MAX_SIZE];
const char* usr_home;
bool is_valid_oldpwd;

/* Initialization function */
void init_shell_state(void) {
    int status = 0;
    is_valid_oldpwd = false;

    if((usr_home = getenv("HOME")) == NULL) {
        printf("[ERROR] HOME not set.");
    }

    if(getcwd(shell_cwd, sizeof(shell_cwd)) == NULL) {
        printf("[ERROR] Critical error. CWD is not set.");
        exit(1);
    }

    if(setenv("PWD", shell_cwd, 1) != 0) {
        status = errno;
        printf("[ERROR] Couldn't set environment variable 'PWD'. errno: %d", status);
    }

    unsetenv("OLDPWD"); /* explicitly unset OLDPWD on startup */
    shell_oldpwd[0] = '\0'; /* mark as empty/invalid */
}

/* Helper to update state safely */
/* Run after chdir */
int update_cwd(void) {
    int status = 0;
    /* 
     * 1. copy shell_cwd -> shell_oldpwd
     * 2. getcwd
     * 3. sync env:
     *      export OLDPWD using shell_oldpwd
     *      export PWD using shell_cwd
     * 4. return success/failure
     */
    strcpy(shell_oldpwd, shell_cwd);
    if(getcwd(shell_cwd, PATH_MAX_SIZE) == NULL) {
        status = errno;
        printf("[ERROR] Couldn't get cwd. errno: %d\n", status);
    }
    if(setenv("OLDPWD", shell_oldpwd, 1) != 0) {
        status = errno;
        printf("[ERROR] Couldn't set environment variable 'OLDPWD'. errno: %d\n", status);
    }
    if(setenv("PWD", shell_cwd, 1) != 0) {
        status = errno;
        printf("[ERROR] Couldn't set environment variable 'PWD'. errno: %d\n", status);
    }
    is_valid_oldpwd = true;

    return status;
}
