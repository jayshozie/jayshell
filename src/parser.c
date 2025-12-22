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
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell_defs.h"
#include "parser.h"

char** expand_tilde(char** args) {
    int i = 0;
    char* remainder;
    int dirsize;
    char* home = getenv("HOME");
    while(args[i] != NULL) {
        if(args[i][0] == '~') {
            /* /home/user + ~/dir/to/chdir - ~ */
            dirsize = strlen(home) + strlen(args[i]);
            remainder = malloc(dirsize);
            snprintf(remainder, dirsize, "%s%s", home, args[i] + 1);
            free(args[i]);
            args[i] = remainder;
        }
        i++;
    }
    return args;
}

/*
 * Gets an array of characters, returns tokens.
 */
char** tokenize(char* line) {
    char** args = malloc(ARGS_SIZE * sizeof(char*));
    char* token;
    unsigned long tokens_written = 0;

    /*
     * get the first token, and check whether it's NULL. if it's NULL, command
     * from main.c is empty, so initialize args[0] so we don't check an
     * uninitialized value while free'ing args.
     */
    if((token = strtok(line, " ")) == NULL) {
        /* if it's NULL, realloc args, and initialize args[0] */
        args = realloc(args, sizeof(char*));
        args[0] = NULL;
        /* don't forget token is on the heap */
        free(token);
        /* return */
        return args;
    }
    /* token is not NULL */
    args[0] = malloc(strlen(token) + 1); /* sizeof(char) = 1 */
    /* get the token in args */
    strcpy(args[0], token);
    tokens_written++;

    /* get the rest of the tokens */
    while(tokens_written < ARGS_SIZE) {
        /* if the token is not NULL, write it to args */
        if((token = strtok(NULL, " ")) != NULL) {
            /* sizeof(char) = 1 */
            args[tokens_written] = malloc(strlen(token) + 1);
            strcpy(args[tokens_written], token);
            tokens_written++;
        }
        /* if it is NULL, we're at the end of our tokens, so break */
        else { break; }
    }

    /*
     * Add a single NULL at the end of the array, because exec's require the
     * last element in the array to be a NULL
     */
    args = realloc(args, (tokens_written + 1)* sizeof(char*));
    args[tokens_written] = NULL;

    return args;
}
