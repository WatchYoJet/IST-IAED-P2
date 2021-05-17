#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "initReader.h" */
#define MAXINPUT 65523
#define MAX_COMMAND_SIZE 6
struct Node{
    char key[MAXINPUT];
    char valor[MAXINPUT];
    struct Node *left;
    struct Node *right;
    int height;
};

struct Tree{
    char path[MAXINPUT];
    struct Tree *next;
    struct Node *Node;
};

int isCommand(char *input, char *command);
void helpCommand();
void quitCommand();
struct Tree* setCommmand(char path[], char value[], struct Tree *root);
struct Tree* pathExists(struct Tree *root, char path[]);
void printing(struct Tree *root);

int mallocCounter = 0;

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

struct Node * newNode(char key[]){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    ++mallocCounter;
    strcpy(node->key, key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}

struct Node * rightRotate(struct Node *y){
    struct Node *x = y->left;
    struct Node *z = x->right;

    x->right = y;
    y->left = z;
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

struct Node * leftRotate(struct Node *x){
    struct Node *y = x->right;
    struct Node *z = y->left;

    y->left = x;
    x->right = z;
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(struct Node *N){
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

struct Node * insert(struct Node* node, char key[]){

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

struct Node * deleteNode(struct Node * root, char key[]){
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

void finnish(struct Node *root){
    root = root->left;
    if(root != NULL){
        free(root);
        --mallocCounter;
        finnish(root);
    }
}

/*int main(){
    struct Node *root = NULL;

    root = insert(root, "um");
    root = insert(root, "dois");
    root = insert(root, "quatro");
    root = insert(root, "cinco");
    root = insert(root, "tres");   
    printf("ROOT:\n");
    preOrder(root);
    printf("\nOLA:\n");

    printf("\n\n----------------\nmallocCounter: %d\n", mallocCounter);
    return 0;
}*/

int main(){
    char command[MAX_COMMAND_SIZE],input[MAXINPUT];
    char path[MAXINPUT], value[MAXINPUT], arguments[MAXINPUT- MAX_COMMAND_SIZE];
    struct Tree *root = NULL;
    while(1) {
        fgets(input, MAXINPUT, stdin);
        sscanf(input, "%s %[^\n]", command, arguments);
        sscanf(arguments, "%s %[^\n]" ,path, value);

        if (isCommand(command,"help")) helpCommand();

        else if (isCommand(command,"set")){
            root = setCommmand(path, value, root);
            puts("---------");
            printing(root);
            puts("---------");
        } 

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

struct Tree* checkRootTree(struct Tree *root){
    if (root == NULL){
        root = (struct Tree*)malloc(sizeof(struct Tree));
        root->next = NULL;
        root->Node = NULL;
    }
    return root;
}


void printing(struct Tree *root){
    while (root != NULL){
        printf("%s\n", root->path);
        root = root->next;
    }
}


/* set ola/tudobem?/hmmhereitgoes/works!/Ithinkso WORKS!! */
struct Tree* setCommmand(char path[], char value[], struct Tree *root){
    char *token, pathHandler[MAXINPUT] = "/", *token2;
    struct Tree *temp, *temp2;

    root = checkRootTree(root);
    temp = root;
    token = value;
    token = strtok(path, "/");
    while(temp != NULL && temp != root){
        if(temp->next == NULL){
            temp->next = checkRootTree(temp->next);
            temp = temp->next;
            break;
        }
        temp = temp->next;
    }
    while( token != NULL ) {
        token2 = strtok(NULL, "/");
        strcat(pathHandler, token);
        if (token2 != NULL) strcat(pathHandler, "/");
        strcpy(temp->path,pathHandler);
        temp2 = temp;
        temp = pathExists(root, pathHandler);
        temp->Node = insert(temp->Node, token);
        preOrder(temp->Node);
        printf("\n");
        temp = temp2;
        if (token2 != NULL){
            temp->next = checkRootTree(temp->next);
            temp = temp->next;
        }
        token = token2;
    }
    strcpy(temp->Node->valor, value);
    return root;
}


/*Tenho de fazer uma funçao que verifica se o path existe ou nao,
se sim, adiciona a esse mesmo*/

struct Tree* pathExists(struct Tree *root, char path[]){
    struct Tree *temp;
    for (temp = root; temp != NULL; temp = temp->next){
        if(!strcmp(temp->path,path)){
            return temp;
        }
    }
    return NULL;
}