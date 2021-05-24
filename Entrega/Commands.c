/*
 * File: Commands.c
 * Author: Pedro Pereira
 * Description: All handlers of commands
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


/* Function used to free all the AVL tree */
void finish_Node(struct Node *root){
    if(root == NULL) return;
    finish_Node(root->left);
    finish_Node(root->right);
    free(root->key);
    root->key = NULL;
}

/* Quit Command- Leaves the program "freeing" all the mallocs  */
void quitCommand(struct Tree *root){
    struct Tree *temp, *prev = root;
    int val= 0;
    if (root == NULL) exit(0);
    temp = root->next;
    while(prev != NULL){
        free(prev->valor);
        free(prev->path);
        if (prev->Node != NULL)finish_Node(prev->Node);
        if (prev->Node != NULL)free(prev->Node);
        prev = temp;
        if (val == 1) break;
        if (temp == NULL) val = 1;
        else temp = temp->next;
    }
    if (root != NULL) root = NULL;
    exit(0);
}

/* Help Command- displays all the commands */
void helpCommand(){
    puts(HELP_MESSAGE);
    /* help command */
    puts(QUIT_MESSAGE);
    /* quit command */
    puts(SET_MESSAGE);
    /* set command */
    puts(PRINT_MESSAGE);
    /* print command */
    puts(FIND_MESSAGE);
    /* find command */
    puts(LIST_MESSAGE);
    /* list command */
    puts(SEARCH_MESSAGE);
    /* search command */
    puts(DELETE_MESSAGE);
    /* delete command */
}


/* Verifies if the element of the Linked List is NULL, if so, crates it*/
struct Tree* checkRootTree(struct Tree *root){
    if (root == NULL){
        root = (struct Tree*)malloc(sizeof(struct Tree));
        if (root == NULL){puts("No memory."); quitCommand(root);}
        root->next = NULL;
        root->Node = NULL;
        root->valor = malloc(2);
        if (root->valor == NULL){puts("No memory."); quitCommand(root);}
        strcpy(root->valor, "");
        root->path = malloc(2);
        if (root->path == NULL){puts("No memory."); quitCommand(root);}
        strcpy(root->path, "");
    }
    return root;
}

/* Gives the next element of the LL (Next Null Element)*/
struct Tree* nextNull(struct Tree *root){
    struct Tree *temp = root;
    if (root->next == NULL) return root;
    while(temp != NULL){
        if(temp->next == NULL){
            temp->next = checkRootTree(temp->next);
            temp = temp->next;
            break;
        }
        temp = temp->next;
    }
    return temp;
}

/* Sets the new value to a certain element of the Linked List*/
struct Tree* setValue(struct Tree *root, char value[]){
    if (root->valor != NULL)free(root->valor);
    root->valor = malloc(strlen(value) + 1);
    if (root->valor == NULL){puts("No memory."); quitCommand(root);}
    strcpy(root->valor, value);
    return root;
}

/* Sets the new path to a certain element of the Linked List*/
struct Tree* setPath(struct Tree *root, char path[]){
    if (root != NULL){
        if (root->path != NULL) free(root->path);
        root->path = malloc(strlen(path) + 1);
        if (root->path == NULL){puts("No memory."); quitCommand(root);}
        root->path[0] = '\0';
        strcpy(root->path, path);
        return root;
    }
    return root;
}

/* This function gets a path and value, verifies if the path is already created
*  if so, changes the value. If not, it creates the path and adds the value*/
struct Tree* setCommmand(char path[], char value[], struct Tree *root){
    char *token=NULL, pathHandler[MAXINPUT], *token2=NULL, pote[MAXINPUT];
    struct Tree *temp=NULL;
    int val = 0;
    pathHandler[0] = '\0';
    pote[0] = '\0';
    strcat(pote, "/");
    strcpy(pathHandler,path);
    token = strtok(pathHandler, "/");
    while(token != NULL){
        token2 = strtok(NULL, "/");
        strcat(pote, token);
        if (token2 != NULL) strcat(pote, "/");
        token = token2;
    }
    strcpy(pathHandler,"/");
    token = strtok(path, "/");
    if(root == NULL){
        val = 1;
        root = checkRootTree(root);
        root = setPath(root,"/");
    }
    root->Node = insert(root->Node, token);
    temp = pathExists(root,pote);
    if (temp != NULL){
        temp = setValue(temp, value);
        return root;
    }
    temp = setHandler(pathHandler,root,token, val);
    temp = setValue(temp, value);
    return root;
}


/* This function is used to help the set function, by devinding the path,
*  checking it it exists one by one*/
struct Tree* setHandler(char path[], struct Tree *root, char *token, int val3){
    char *token2=NULL, pote[MAXINPUT];
    struct Tree *temp=NULL, *temp2=NULL, *temp3=NULL;
    int val = 1, val2 = 1, count=0;
    temp = nextNull(root);
    while( token != NULL ) {
        token2 = strtok(NULL, "/");
        if (count == 0 && val3){
        temp->next = checkRootTree(temp->next);
        temp = temp->next;
        }
        strcat(path, token);
        strcpy(pote, path);
        temp3 = pathExists(root, path);
        if(temp3 == NULL)temp = setPath(temp, path);
        temp2 = temp;
        if(temp3 != NULL) temp = temp3;
        strcat(pote, token);
        if (temp != temp2) val = 0;
        if (cmp1LetterEqual(pote, temp->path)) val2 = 0;
        if (temp != NULL && temp != temp2 && val2)
            temp->Node = insert(temp->Node, token2);
        if (token2 != NULL){
            strcat(path, "/");
        }
        temp = temp2;
        if ((token2 != NULL && val)){
            if(token2 != token)
                temp->Node = insert(temp->Node, token2);
            temp->next = checkRootTree(temp->next);
            temp = temp->next;
        }
        token = token2;
        val = 1;
        val2 = 1;
        ++count;
    }
    return temp;
}

/* This function defines if the path already exists in the Linked List,
*  returning it if so (or NULL if not) */
struct Tree* pathExists(struct Tree *root, char path[]){
    struct Tree *temp=NULL;
    for (temp = root; temp != NULL; temp = temp->next){
        if (temp->path != NULL)
            if(cmp1LetterEqual(temp->path,path))return temp;
    }
    return NULL;
}

/* This function searches a value on all the Linked List printing its path*/
void searchCommand(char value[], struct Tree *root){
    int AV=1;
    if(root != NULL) root = root->next;
    while (root != NULL){
        if (cmp1LetterEqual(root->valor, value)){
            puts(root->path);
            AV = 0;
            break;
        }
        root = root->next;
    }
    if (AV) puts("not found");
}

/* This function prints all the paths with values*/
void printCommand(struct Tree *root){
    if(root != NULL) root = root->next;
    while (root != NULL){
        if (!cmp1LetterEqual(root->valor,""))
            printf("%s %s\n", root->path, root->valor);
        root = root->next;
    }
}

/* This path prints all the "childs" that a certain path has*/
void listCommand(struct Tree *root, char path[]){
    char *token, pathHandler[MAXINPUT]="/";
    int AV=1;
    if (strlen(path) != 0){
        token = strtok(path, "/");
        while( token != NULL ) {
            strcat(pathHandler, token);
            token = strtok(NULL, "/");
            if (token != NULL) strcat(pathHandler, "/");
        }
        while (root != NULL){
            if (cmp1LetterEqual(root->path, pathHandler)){
                traversal (root->Node);
                AV = 0; 
            }
            root = root->next;
        }
        if (AV) puts("not found");
    }
    else if(root != NULL) traversal (root->Node);
}

/* This function prints the value of a certain path*/
void findCommand(struct Tree *root, char path[]){
    char *token, pathHandler[MAXINPUT]="/";
    int valE1 = 1 , valE2 = 0;
    if(root != NULL) root = root->next;
    token = strtok(path, "/");
    while( token != NULL ) {
        strcat(pathHandler, token);
        token = strtok(NULL, "/");
        if (token != NULL) strcat(pathHandler, "/");
    }
    while (root != NULL){
        if (cmp1LetterEqual(root->path, pathHandler)){
            if (cmp1LetterEqual(root->valor, "")) valE2 = 1;
            else{
                puts(root->valor);
                valE1 = 0;
                break;
            }
        }
        root = root->next;
    }
    if (valE2) puts("no data");
    else if (valE1) puts("not found");
}

/* This function "deletes" a certain path
*  (Missing implementation of "freeing" it and removing all childs)
*/
struct Tree* deleteCommand(struct Tree *root, char path[]){
    struct Tree *temp=NULL, *prev=root;
    char *token, pathHandler[MAXINPUT]="/", lastPath[MAXINPUT]="";
    if (cmp1LetterEqual(path,"")){
        root->next = NULL;
        return root;}
    token = strtok(path, "/");
    while( token != NULL ) {
        strcat(pathHandler, token);
        token = strtok(NULL, "/");
        if (token != NULL){
            strcat(pathHandler, "/");
            strcpy(lastPath,token);
        }
    }
    temp = pathExists(root, pathHandler);
    if (temp == NULL){
        puts("not found");
        return root;
    }
    while(prev->next != temp) prev = prev->next;
    if (temp->next == NULL) prev->next = NULL;
    else prev->next = temp->next;
    return root;
}