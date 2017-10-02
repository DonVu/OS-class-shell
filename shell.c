//
//  main.c
//  Shell
//
//  Created by Don Vu on 9/30/17.
//  Copyright © 2017 Don Vu. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int tokenize(char *args[], char *command){
    int i = 0;
    
    const char delim[2] = " ";
    args[i] = strtok(command, delim);
    
    
    while (args[i] != NULL){
        printf("token: %s\n", args[i]);
        
        ++i;
        args[i] = strtok(NULL, delim);
    }
    
    return i;
}

#define MAX_LINE 80

int main (void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    char exit_str[] = "exit\n";
    
    while (should_run) {
        printf("osh>");
        fflush(stdout);
        
        char command[MAX_LINE];
        int num = 0;
        
        fgets(command, (MAX_LINE/2 +1), stdin);
        
        printf("Your command is: %s\n", command);
        
        if (!(strcmp(command, exit_str))){
            return 0; /* User exits the shell */
        }
        
        num = tokenize(args, command);
        
        /* creating child process to run commands */
        pid_t pid;
        
        pid = fork();
        
        if (pid < 0) { /* error occurred */
            fprintf(stderr, "Fork failed.");
            return 1;
        }
        else if (pid == 0) { /* child process */
            execvp(args[0], args);
            /* error occurred during execvp */
            fprintf(stderr, "Error running execvp\n");
            exit(0);
        }
        else { /* parent process */
            /* the parent process will run
             concurrently if "&" is added to
             the end of the user's command */
            if ((strcmp(args[num - 1], "&") != 0)){
                wait(NULL);
            }
            
        }
        memset(command, '\0', MAX_LINE);
        memset(args, '\0', MAX_LINE/2 + 1);
    }
    
    return 0;
}