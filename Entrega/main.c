/*
 * File: main.c
 * Author: Pedro Pereira
 * Description: File system
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

/* Verifies the command */
int isCommand(char *input, char *command){
    return (cmp1LetterEqual(input, command));
}

int main(){
    char command[MAX_COMMAND_SIZE]="",input[MAXINPUT]="";
    char path[MAXINPUT]="", value[MAXINPUT]="", arguments[MAX_ARGUMENTS]="";
    struct Tree *root = NULL;
    while(1){
        arguments[0]='\0';
        value[0]='\0';
        path[0]='\0';
        fgets(input, MAXINPUT, stdin);
        sscanf(input, "%s %[^\n]", command, arguments);
        sscanf(arguments, "%s %[^\n]" ,path, value);
        if (isCommand(command,"help")) helpCommand();
        else if (isCommand(command,"set"))root = setCommmand(path, value, root); 
        else if (isCommand(command,"print")) printCommand(root);
        else if (isCommand(command,"find")) findCommand(root, arguments);
        else if (isCommand(command,"list")) listCommand(root, arguments);
        else if (isCommand(command,"search")) searchCommand(arguments,root);
        else if (isCommand(command,"delete")) deleteCommand(root, arguments);
        else if (isCommand(command,"quit")) quitCommand(root);
    }
}