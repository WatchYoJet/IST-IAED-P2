#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char ola[20], ola2[10], ola3[10];

int main(){
    printf("?:");
    fgets(ola, 20, stdin);
    sscanf(ola, "%s %[^\n]", ola2, ola3);
    puts(ola2);
    if(strlen(ola3) == 0) puts("works!");
    return 0;
}