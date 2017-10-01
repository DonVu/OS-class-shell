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

void tokenize(char *args[], char *command){
    int i = 0;
    
    const char delim[2] = " ";
    args[i] = strtok(command, delim);
    
    
    while (args[i] != NULL){
        printf("token: %s\n", args[i]);
        
        ++i;
        args[i] = strtok(NULL, delim);
    }
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
        
        
        fgets(command, (MAX_LINE/2 +1), stdin);
        
        printf("Your command is: %s", command);
        
        if (!(strcmp(command, exit_str))){
            should_run = 0; /* User exits the shell */
        }
        
        tokenize(args, command);
        
        
    }
    
    return 0;
}