#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "initReader.h" */
#define MAXINPUT 65535
#define MAX_COMMAND_SIZE 6


int isCommand(char *input, char *command);
void helpCommand();
void first(char input[]);
void quitCommand();


int main(){
    char command[MAX_COMMAND_SIZE], arguments[MAXINPUT- MAX_COMMAND_SIZE];
    while(1) {
        printf("?: ");
        fgets(arguments, MAXINPUT, stdin);
        sscanf(arguments, "%s %[^\n]", command, arguments);

        if (isCommand(command,"add")) first(arguments);

        else if (isCommand(command,"help")) helpCommand();

        else if (isCommand(command,"set")) printf("hello\n");

        else if (isCommand(command,"print")) printf("hello\n");

        else if (isCommand(command,"find")) printf("hello\n");

        else if (isCommand(command,"list")) printf("hello\n");

        else if (isCommand(command,"search")) printf("hello\n");

        else if (isCommand(command,"delete")) printf("hello\n");
        
        else if (isCommand(command,"q")) quitCommand();

        else printf("ups!\n");
    }
}

int isCommand(char *input, char *command){
    return (strcmp(input, command) == 0);
}

/* add ola/tudo bem?/hmm here it goes/works!/I think so */
void first(char input[]){
    const char s[1] = "/";
    char *token;

    token = strtok(input, s);
    while( token != NULL ) {
       printf( " %s\n", token );
       token = strtok(NULL, s);
    }
}

void quitCommand(){
    exit(0);
}

void helpCommand(){
    puts("help: Imprime os comandos disponíveis.");
    /* help command */
    puts("quit: Termina o programa."); 
    /* quit command */
    puts("set: Adiciona ou modifica o valor a armazenar."); 
    /* set command */
    puts("print: Imprime todos os caminhos e valores."); 
    /* print command */
    puts("find: Imprime o valor armazenado."); 
    /* find command */
    puts("list: Lista todos os componentes imediatos de um sub-caminho.");
    /* list command */
    puts("search: Procura o caminho dado um valor.");
    /* search command */
    puts("delete: Apaga um caminho e todos os subcaminhos.");
    /* delete command */
}