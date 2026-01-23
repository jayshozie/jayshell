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
#include <stdbool.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "shell_defs.h"
#include "shell_state.h"
#include "builtins.h"
#include "execute.h"
#include "parser.h"

int i = 0;
int status = 0;
char* command;
char** args; /* DYNAMICALLY ALLOCATED BY THE TOKENIZER */
builtin_func run_builtin;

int main()
{
    /* initialize shell env vars */
    init_shell_state();

    while(true) {
        /*
         * 1. GET COMMAND ✔️
         *  a. ADD TO HISTORY
         * 2. TOKENIZE ✔️
         * 3. FREE `command` ✔️
         * 4. REQUEST BUILT-IN FUNCTION POINTER ✔️
         *  a. IF NULL, CALL EXEC_EXTERNAL WITH ARGS ✔️
         *  b. IF NOT, CALL THE RETURNED FUNCTION POINTER ✔️
         * 5. CHECK STATUS ✔️
         *  a. IF FAIL CALL PERROR OR SIMILAR ✔️
         *  b. IF NOT DO NOTHING ✔️
         * 6. GOTO 1:
         */

        /* get prompt, if null readline failed */
        if((command = readline("$ ")) != NULL) {
            /* tokenize command, args is dynamically allocated */
            args = tokenize(command);
            /* readline uses heap to store the output, don't forget to free */
            free(command);

            /* TEMPORARY: TILDE EXPANSION */
            args = expand_tilde(args);

            /* Request built-in function pointer */
            run_builtin = get_builtin(args[0]);

            if(run_builtin != NULL) {
                status = run_builtin(args);
            }
            else {
                status = exec_external(args);
            }

            /*
             * `args` and every single element of `args` is on heap. thus they
             * must be individually free`d.
             */
            i = 0;
            while(args[i] != NULL) {
                free(args[i]);
                i++;
            }
            free(args);
        }
        else {
            free(command);
            exit(1);
        }
    }
}
