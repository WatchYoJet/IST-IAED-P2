#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "initReader.h" */
#define MAXINPUT 65523
#define MAX_COMMAND_SIZE 6


int isCommand(char *input, char *command);
void helpCommand();
void quitCommand();
void setCommmand(char path[], char value[]);

int main(){
    char command[MAX_COMMAND_SIZE],input[MAXINPUT];
    char path[MAXINPUT], value[MAXINPUT], arguments[MAXINPUT- MAX_COMMAND_SIZE];
    while(1) {
        fgets(input, MAXINPUT, stdin);
        sscanf(input, "%s %[^\n]", command, arguments);
        sscanf(arguments, "%s %[^\n]" ,path, value);

        if (isCommand(command,"help")) helpCommand();

        else if (isCommand(command,"set")) setCommmand(path, value);

        else if (isCommand(command,"print")) printf("hello\n");

        else if (isCommand(command,"find")) printf("hello\n");

        else if (isCommand(command,"list")) printf("hello\n");

        else if (isCommand(command,"search")) printf("hello\n");

        else if (isCommand(command,"delete")) printf("hello\n");
        
        else if (isCommand(command,"quit")) quitCommand();
        else if (isCommand(command,"q")) quitCommand();
    }
}

int isCommand(char *input, char *command){
    return (strcmp(input, command) == 0);
}

/* q */
void quitCommand(){
    exit(0);
}

/* help */
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

/* set ola/tudobem?/hmmhereitgoes/works!/Ithinkso WORKS!! */
void setCommmand(char path[], char value[]){
    const char s[1] = "/";
    char *token;

    printf("%s\n", value);
    token = strtok(path, s);
    while( token != NULL ) {
        printf( "%s\n", token );

        
        token = strtok(NULL, s);
    }
}