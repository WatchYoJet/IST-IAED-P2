#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "initReader.h" */
#define MAXINPUT 65524
#define MAX_COMMAND_SIZE 7
struct Node{
    char * key;
    struct Node *left;
    struct Node *right;
    int height;
};

struct Tree{
    char * valor;
    char * path;
    struct Tree *next;
    struct Node *Node;
};

int isCommand(char *input, char *command);
void helpCommand();
void quitCommand();
struct Tree* setCommmand(char path[], char value[], struct Tree *root);
struct Tree* checkRootTree(struct Tree *root);
struct Tree* pathExists(struct Tree *root, char path[]);
void searchCommand(char value[], struct Tree *root);
void printCommand(struct Tree *root);
void listCommand(struct Tree *root, char path[]);
void findCommand(struct Tree *root, char path[]);

int max(int a, int b);

int height(struct Node *N){
    if (N == NULL) return 0;
    return N->height;
}

int max(int a, int b){
    if (a > b) return a;
    else return b;
}

struct Node * newNode(char key[]){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = malloc(strlen(key) + 1);
    strcpy(node->key, key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}

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

int getBalance(struct Node *N){
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

struct Node * insert(struct Node* node, char key[]){
    int balanceFactor;
    if (node == NULL)
        return(newNode(key));
    if (strcmp(key, node->key) < 0)
        node->left = insert(node->left, key);
    else if (strcmp(key, node->key) > 0)
        node->right = insert(node->right, key);
    else return node;
    node->height = 1 + max(height(node->left), height(node->right));
    balanceFactor = getBalance(node);
    if (balanceFactor > 1){
        if (strcmp(key, node->left->key) > 0) 
            node->left =  leftRotate(node->left);
        return rightRotate(node);
    } 
    if (balanceFactor < -1){
        if (strcmp(key, node->right->key) < 0) 
            node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

struct Node * minValueNode(struct Node* node){
    struct Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

void preOrder(struct Node *root){
    if(root != NULL){
        preOrder(root->left);
        puts(root->key);
        preOrder(root->right);
    }
}


void finnish(struct Node *root){
    root = root->left;
    if(root != NULL){
        free(root);
        finnish(root);
    }
}

struct Node* deleteNode(struct Node* root, char key[]){
    struct Node* temp;
    int balance;
    if (root == NULL)
        return root;
  
    if ( strcmp(key, root->key) < 0 )
        root->left = deleteNode(root->left, key);
    else if(strcmp(key, root->key) > 0)
        root->right = deleteNode(root->right, key);
    else{
        if( (root->left != NULL) || (root->right != NULL) ){
            temp = minValueNode(root->right);  
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        else{
            temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else *root = *temp;
            free(temp);
        }
    }
    if (root == NULL)
      return root;
    root->height = 1 + max(height(root->left),height(root->right));
  
    balance = getBalance(root);
    if (balance > 1){
        if(getBalance(root->left) < 0) root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1){
        if (getBalance(root->right) > 0) root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main(){
    struct Node *root = NULL;
    root = insert(root, "nice!");
    preOrder(root);
    puts("--------------");
    root = insert(root, "ola!");
    preOrder(root);
    puts("--------------");
    root = insert(root, "amazing!");
    preOrder(root);
    puts("-------DELETE------");
    root = deleteNode(root, "ola!");
    preOrder(root);
    puts("--------NADA----");
    root = deleteNode(root, "ola!");
    preOrder(root);
    puts("--------------");
    return 0;
}