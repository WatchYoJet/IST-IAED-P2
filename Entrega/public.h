/*
 * File: public.h
 * Author: Pedro Pereira
 */

#ifndef __PUBLIC_H__
#define __PUBLIC_H__


int max(int a, int b);
int cmp1LetterEqual(char *arg1, char *arg2);
int cmp1LetterBigger(char *arg1, char *arg2);
int height(struct Node *N);
struct Node * newNode(char key[]);
struct Node * rightRotate(struct Node *h);
struct Node * leftRotate(struct Node *h);
int getBalance(struct Node *N);
struct Node * insert(struct Node* node, char key[]);
struct Node * minValueNode(struct Node* node);
void traversal(struct Node *root);
int isCommand(char *input, char *command);
void finish_Node(struct Node *root);
void quitCommand(struct Tree *root);
void helpCommand();
struct Tree* checkRootTree(struct Tree *root);
struct Tree* nextNull(struct Tree *root);
struct Tree* setValue(struct Tree *root, char value[]);
struct Tree* setPath(struct Tree *root, char path[]);
struct Tree* setCommmand(char path[], char value[], struct Tree *root);
struct Tree* pathExists(struct Tree *root, char path[]);
void searchCommand(char value[], struct Tree *root);
void printCommand(struct Tree *root);
void listCommand(struct Tree *root, char path[]);
void findCommand(struct Tree *root, char path[]);
struct Tree* deleteCommand(struct Tree *root, char path[]);
struct Tree* setHandler(char path[], struct Tree *root, char *token, int val3);


#define HELP_MESSAGE "help: Imprime os comandos disponíveis."
#define QUIT_MESSAGE "quit: Termina o programa."
#define SET_MESSAGE "set: Adiciona ou modifica o valor a armazenar."
#define PRINT_MESSAGE "print: Imprime todos os caminhos e valores."
#define FIND_MESSAGE "find: Imprime o valor armazenado."
#define LIST_MESSAGE "list: Lista todos os componentes imediatos de um "\
"sub-caminho."
#define SEARCH_MESSAGE "search: Procura o caminho dado um valor."
#define DELETE_MESSAGE "delete: Apaga um caminho e todos os subcaminhos."

#endif