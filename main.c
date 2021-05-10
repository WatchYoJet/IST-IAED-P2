#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXINPUT 65535

int main()
{
    while(1) {
        char command[10], arguments[MAXINPUT];
        fgets(arguments, MAXINPUT, stdin);
        sscanf(arguments, "%s", command);
        printf("%s\n", command);
    };
    return 0;
}