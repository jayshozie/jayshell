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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "builtins.h"

int builtin_cd(char** args) {
    int status = 0;
    const char* home;
    char* dirname;
    char old_wd[PATH_MAX_SIZE];
    char curr_wd[PATH_MAX_SIZE];

    if(args[2] != NULL) {
        /* Too many arguments error implemented. */
        status = errno;
        perror("Too many arguments.");
    }
    else {
        if((home = getenv("HOME")) == 0) {
            /* HOME env not set error implemented. */
            status = errno;
            perror("ERR:");
        }
        else {
            if(args[1] == NULL || args[1][0] == '\0') {
                /* empty args[1] implemented, POSIX compliance */
                if(chdir(home) != 0) {
                    status = errno;
                    perror("ERR");
                }
            }
            else if(strcmp(args[1], "-") == 0) {
                /* cd - implemented, POSIX compliance */
                getcwd(old_wd, PATH_MAX_SIZE);
                if(chdir(getenv("OLDPWD")) == 0) {
                    setenv("OLDPWD", old_wd, 1);
                }
                printf("%s\n", curr_wd);
                getcwd(curr_wd, PATH_MAX_SIZE);
                setenv("PWD", curr_wd, 1);
            }
            else {
                getcwd(old_wd, PATH_MAX_SIZE);
                dirname = args[1];
                if(chdir(dirname) != 0){
                    status = errno;
                    perror("ERR");
                }
                else {
                    setenv("OLDPWD", old_wd, 1);
                    getcwd(curr_wd, PATH_MAX_SIZE);
                    setenv("PWD", curr_wd, 1);
                }
            }
        }
    }
    return status;
}
