#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "initReader.h" */
#define MAXINPUT 65535


char * commandHandler();
int validCommand(char *input, char *command);
void first();

int main(){
    char *command, *input;
    input = (char*) malloc(sizeof(char)* MAXINPUT);
    while(1) {
        command = commandHandler(input);
        if (validCommand(command,"add")) {
            first(input);
        } else if (validCommand(command,"help")) {
            printf("hello\n"); 
        } else if (validCommand(command,"set")) {
            printf("hello\n");
        } else if (validCommand(command,"print")) {
            printf("hello\n");
        } else if (validCommand(command,"find")) {
            printf("hello\n");
        } else if (validCommand(command,"list")) {
            printf("hello\n");
        } else if (validCommand(command,"search")) {
            printf("hello\n");
        }else if (validCommand(command,"delete")) {
            printf("hello\n");
        } else if (validCommand(command,"quit")) {
            free(input);
            exit(0);
        }
    }
}

char * commandHandler(char * input){
    int i = 0;
    char c;
    while((c = getchar()) != ' ' && c != '\n' && c != '\t') {
        input[i] = c;
        ++i;
    }
    input[i] = '\0';
    return input;
}

int validCommand(char *input, char *command){
    return (strcmp(input, command) == 0);
}

void first(char * input){
    char c;
    int i = 0;
    while((c = getchar()) != '\n') {
        input[i] = c;
        ++i;
    }
    input[i] = '\0';
    printf("%s\n", input);
}