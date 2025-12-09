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

#define ARGS_SIZE 255
char *command;

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
            if(strcmp(args[0], "cd") == 0) {
                char* dirname;
                if((dirname = getenv("HOME")) == 0) {
                    perror("ERR");
                }
                else {
                    if(args[1] == NULL || args[1][0] == '\0') {
                        chdir(dirname);
                    }
                    else if(args[2] != NULL) {
                        printf("Too many arguments.\n");
                    }
                    else {
                        dirname = args[1];
                        if(chdir(dirname) != 0) {
                            perror("ERR");
                        }
                    }
                }
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
