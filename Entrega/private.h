/*
 * File: private.h
 * Author: Pedro Pereira
 */

#ifndef __PRIVATE_H__
#define __PRIVATE_H__

/* Struct used to implement the AVL Tree*/
struct Node{
    char * key;
    struct Node *left;
    struct Node *right;
    int height;
};

/* Struct used to implement the Linked List*/
struct Tree{
    char * valor;
    char * path;
    struct Tree *next;
    struct Node *Node;
};

#define MAXINPUT 65524
#define MAX_COMMAND_SIZE 7
#define MAX_ARGUMENTS 65524-7

#endif