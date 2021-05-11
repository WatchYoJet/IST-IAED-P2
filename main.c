#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "initReader.h" */
#define MAXINPUT 65535


char * commandHandler();
int isCommand(char *input, char *command);
void helpCommand();
void first();

int main(){
    char *command, *input;
    input = (char*) malloc(sizeof(char)* MAXINPUT);
    while(1) {
        command = commandHandler(input);
        if (isCommand(command,"add")) first(input);

        else if (isCommand(command,"help")) helpCommand();

        else if (isCommand(command,"set")) printf("hello\n");

        else if (isCommand(command,"print")) printf("hello\n");

        else if (isCommand(command,"find")) printf("hello\n");

        else if (isCommand(command,"list")) printf("hello\n");

        else if (isCommand(command,"search")) printf("hello\n");

        else if (isCommand(command,"delete")) printf("hello\n");
        
        else if (isCommand(command,"quit")) {
            free(input);
            exit(0);
        }
        else printf("ups!\n");
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

int isCommand(char *input, char *command){
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

void helpCommand(){
    puts("help: Imprime os comandos disponíveis.");
    puts("quit: Termina o programa.");
    puts("set: Adiciona ou modifica o valor a armazenar.");
    puts("print: Imprime todos os caminhos e valores.");
    puts("find: Imprime o valor armazenado.");
    puts("list: Lista todos os componentes imediatos de um sub-caminho.");
    puts("search: Procura o caminho dado um valor.");
    puts("delete: Apaga um caminho e todos os subcaminhos.");
}