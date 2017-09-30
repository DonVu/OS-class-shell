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

#define MAX_LINE 80

int main (void){
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    //char exit_str[] = "exit\n";
    
    while (should_run) {
        printf("osh>");
        fflush(stdout);
        
        int i = 0;
        char command[MAX_LINE];
        fgets(command, (MAX_LINE/2 +1), stdin);
        
        args[i] = command;
        
        printf("Your command is: %s", args[i]);
        
        if (!(strcmp(args[i], "exit\n"))){
            should_run = 0; /* User exits the shell */
        }
        
        ++i;
    }
    return 0;
}
