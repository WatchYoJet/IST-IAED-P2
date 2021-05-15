#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXINPUT 65535

int mallocCounter = 0;


struct Node{
    char key[MAXINPUT];
    char valor[MAXINPUT];
    struct Node *left;
    struct Node *right;
    int height;
};
  
int max(int a, int b);
  
int height(struct Node *N){
    if (N == NULL)
        return 0;
    return N->height;
}
  
int max(int a, int b){
    if (a > b) return a;
    else return b;
}
  

struct Node* newNode(char key[]){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    ++mallocCounter;

    strcpy(node->key, key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}
  
struct Node *rightRotate(struct Node *y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;
  
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
  

    return x;
}
  
struct Node *leftRotate(struct Node *x){
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(struct Node *N){
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}
  
struct Node* insert(struct Node* node, char key[]){

    if (node == NULL)
        return(newNode(key));
  
    if (strcmp(key, node->key) < 0)
        node->left = insert(node->left, key);
    else if (strcmp(key, node->key) > 0)
        node->right = insert(node->right, key);
    else return node;
  
    node->height = 1 + max(height(node->left), height(node->right));
  
    if (getBalance(node) > 1 && strcmp(key, node->left->key) < 0)
        return rightRotate(node);

    if (getBalance(node) < -1 && strcmp(key, node->right->key) > 0)
        return leftRotate(node);

    if (getBalance(node) > 1 && strcmp(key, node->left->key) > 0){
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (getBalance(node) < -1 && strcmp(key, node->right->key) < 0){
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
  

struct Node* deleteNode(struct Node* root, char key[]){
    if (root == NULL)
        return root;

    if (strcmp(key, root->key) < 0)
        root->left = deleteNode(root->left, key);

    else if(strcmp(key, root->key) > 0)
        root->right = deleteNode(root->right, key);

    else{
        if( (root->left == NULL) || (root->right == NULL) ){
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else *root = *temp; 
            free(temp);
            --mallocCounter;
        }
        else{
            struct Node* temp = minValueNode(root->right);
            strcpy(root->key, temp->key);
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
      return root;

    root->height = 1 + max(height(root->left), height(root->right));

    if (getBalance(root) > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
  
    if (getBalance(root) > 1 && getBalance(root->left) < 0){
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
  
    if (getBalance(root) < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
  
    if (getBalance(root) < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
  
    return root;
}
  
void preOrder(struct Node *root){
    if(root != NULL){
        preOrder(root->left);
        printf("%s ", root->key);
        preOrder(root->right);
    }
}
  
int main(){
  struct Node *root = NULL;
  
    root = insert(root, "um");
    root = insert(root, "dois");
    root = insert(root, "tres");
    printf("Before:\n");
    preOrder(root);
    root = deleteNode(root, "tres");  
    printf("\nAfter: \n");
    preOrder(root);


    printf("\n\n----------------\nmallocCounter: %d\n", mallocCounter);
    return 0;
}