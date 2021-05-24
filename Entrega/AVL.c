/*
 * File: AVL.c
 * Author: Pedro Pereira
 * Description: AVL - self balancing Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

/* This function is used to make the strcmp faster*/
int cmp1LetterEqual(char *arg1, char *arg2){
    if (arg1[0] != arg2[0])return 0;
    else return (strcmp(arg1, arg2) == 0);
}
/* This function is used to make the strcmp faster*/
int cmp1LetterBigger(char *arg1, char *arg2){
    if (arg1[0] > arg2[0])return 1;
    else return (strcmp(arg1, arg2) > 0);
}
/* Return the height of a certain node */
int height(struct Node *N){
    if (N == NULL) return 0;
    return N->height;
}
/* Returns the biggest mumber between two*/
int max(int a, int b){
    if (a > b) return a;
    else return b;
}
/* Creates a newNode for the tree, giving it a key and height of 1*/
struct Node * newNode(char key[]){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = malloc(strlen(key) + 1);
    strcpy(node->key, key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}
/* Funtion used to handle the right rotation of the tree for
*  if to balance on itself */
struct Node * rightRotate(struct Node *h){
    struct Node *x = h->left;
    int height_left, height_right;
    h->left = x->right;
    x->right = h;
    height_left = height(h->left); height_right = height(h->right);
    h->height = height_left > height_right ? height_left + 1 :
    height_right + 1;
    height_left = height(x->left); height_right = height(x->right);
    x->height = height_left > height_right ? height_left + 1 :
    height_right + 1;
    return x; 
}

/* Funtion used to handle the left rotation of the tree for
*  if to balance on itself*/
struct Node * leftRotate(struct Node *h){
    struct Node *x = h->right;
    int height_left, height_right;
    h->right = x->left;
    x->left = h;
    height_left = height(h->left); height_right = height(h->right);
    h->height = height_left > height_right ? height_left + 1 :
    height_right + 1;
    height_left = height(x->left); height_right = height(x->right);
    x->height = height_left > height_right ? height_left + 1 :
    height_right + 1;
    return x;
}

/* Returns the balance factor of a node */ 
int getBalance(struct Node *N){
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

/* This function uses all of the above to add a node into the tree,
*  balancing itself*/
struct Node * insert(struct Node* node, char key[]){
    int balanceFactor;
    if (node == NULL)
        return(newNode(key));
    if (cmp1LetterBigger(node->key, key))
        node->left = insert(node->left, key);
    else if (cmp1LetterBigger(key, node->key))
        node->right = insert(node->right, key);
    else return node;
    node->height = 1 + max(height(node->left), height(node->right));
    balanceFactor = getBalance(node);
    if (balanceFactor > 1){
        if (cmp1LetterBigger(key, node->left->key)) 
            node->left =  leftRotate(node->left);
        return rightRotate(node);
    } 
    if (balanceFactor < -1){
        if (cmp1LetterBigger(node->right->key,key))
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
/* This function returns the lowest Node in the tree (with less "value")*/
struct Node * minValueNode(struct Node* node){
    struct Node* current = node;
    while (current!= NULL && current->left != NULL)
        current = current->left;

    return current;
}
/* This function prints all the tree with order */
void traversal(struct Node *root){
    if(root != NULL){
        traversal(root->left);
        puts(root->key);
        traversal(root->right);
    }
}