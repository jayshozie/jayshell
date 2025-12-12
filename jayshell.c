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
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define ARGS_SIZE     255
#define PATH_MAX_SIZE 4096 // standard
char* command;
char old_wd[PATH_MAX_SIZE];
char curr_wd[PATH_MAX_SIZE];

int main()
{
    /*
     *                         M A I N   L O O P
     */
    while(true) {
        /*
         *    P A R S E   C O M M A N D S
         */
        char* args[ARGS_SIZE];
        if((command = readline("jaysh > ")) == NULL) { // readline failed
            // readline failed
            free(command);
            exit(1);
        }

        args[0] = strtok(command, " ");

        // only iterate through the arguments of the executable
        for(int i = 1; i <= ARGS_SIZE; i++) {
            if((args[i] = strtok(NULL, " ")) == NULL) {
                // finished parsing arguments
                break;
            }
        } // for(int i = 1; i <= ARGS_SIZE; i++)

        if(args[0] != NULL) {
            if(strcmp(args[0], "exit") == 0) { // SIGSEGV: if args[0] is \n
                free(command);
                exit(0);
            }
            else if(strcmp(args[0], "cd") == 0) {
                const char* home;
                char* dirname;
                if((home = getenv("HOME")) == 0) { perror("ERR"); }
                else {
                    if(args[1] == NULL || args[1][0] == '\0') { chdir(home); }

                    else {
                        /*
                         * Parse args[1] to check for tilde
                         */
                        if(strncmp(args[1], "~", 1) == 0) {
                            char dirname_ext[PATH_MAX_SIZE];
                            snprintf(dirname_ext, PATH_MAX_SIZE, "%s%s", home,
                                     args[1] + 1);
                            getcwd(old_wd, PATH_MAX_SIZE); // get old_wd
                            if(chdir(dirname_ext) == 0) {
                                setenv("OLDPWD", old_wd, 1);
                            };
                            getcwd(curr_wd, PATH_MAX_SIZE); // get curr_wd
                            setenv("PWD", curr_wd, 1);
                        }
                        else if(strcmp(args[1], "-") == 0) {
                            getcwd(old_wd, PATH_MAX_SIZE); // get old_wd
                            if(chdir(getenv("OLDPWD")) == 0) {
                                setenv("OLDPWD", old_wd, 1);
                            };
                            getcwd(curr_wd, PATH_MAX_SIZE); // get curr_wd
                            setenv("PWD", curr_wd, 1);
                        }
                        else {
                            getcwd(old_wd, PATH_MAX_SIZE); // get old_wd
                            dirname = args[1];
                            if(chdir(dirname) != 0) {
                                /*
                                 * FIXME: For some reason, chdir returns -1 when
                                 * tilde is used
                                 */
                                perror("ERR");
                            }
                            else {
                                if(chdir(getenv("OLDPWD")) == 0) {
                                    setenv("OLDPWD", old_wd, 1);
                                };
                                getcwd(curr_wd, PATH_MAX_SIZE); // get curr_wd
                                setenv("PWD", curr_wd, 1);
                            }
                        }
                    }
                }
                free(command);
            }
            else {
                pid_t pid = fork();
                if(pid == 0) {
                    // we're in a child process
                    if(execvp(args[0], args) == -1) {
                        perror("ERR");
                        exit(1);
                    }
                }
                else {
                    waitpid(pid, NULL, 0);
                    free(command);
                }
            }
        }
    }
}
