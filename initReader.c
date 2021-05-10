#include "initReader.h"


char * commandHandler(){
    int i = 0;
    char c;
    static char *command;
    while((c = getchar()) != ' ' && c != '\n' && c != '\t') {
        printf("heheh");
        command[i] = c;
        ++i;
    }
    return command;
}