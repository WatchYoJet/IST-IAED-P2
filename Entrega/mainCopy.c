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
void printing(struct Tree *root);
void searchCommand(char value[], struct Tree *root);
void printCommand(struct Tree *root);
void listCommand(struct Tree *root, char path[]);

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
    node->key = malloc(strlen(key) + 1);
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
        --mallocCounter;
        finnish(root);
    }
}

/*struct Node * deleteNode(struct Node * root, char key[]){
    if (root == NULL) return root;
    if (strcmp(key, root->key) < 0) root->left = deleteNode(root->left, key);
    else if( strcmp(key,root->key) > 0) root->right = deleteNode(root->right, key);
    else{
        if( (root->left == NULL) || (root->right == NULL) ){
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else *root = *temp;
            free(temp->key);
            free(temp);
        }
        else{
            struct Node * temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (root == NULL) return root;
    else return getbalance(root);
}*/

int main(){
    char command[MAX_COMMAND_SIZE]="",input[MAXINPUT]="";
    char path[MAXINPUT]="", value[MAXINPUT]="", arguments[MAXINPUT- MAX_COMMAND_SIZE]="";
    struct Tree *root = NULL;
    while(1){
        strcpy(arguments,"\0");
        fgets(input, MAXINPUT, stdin);
        sscanf(input, "%s %[^\n]", command, arguments);
        sscanf(arguments, "%s %[^\n]" ,path, value);

        if (isCommand(command,"help")) helpCommand();

        else if (isCommand(command,"set"))root = setCommmand(path, value, root); 

        else if (isCommand(command,"print")) printCommand(root);

        else if (isCommand(command,"find")) printf("hello\n");

        else if (isCommand(command,"list")) listCommand(root, arguments);

        else if (isCommand(command,"search")) searchCommand(arguments,root);

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
        root->valor= NULL;
    }
    return root;
}

void printing(struct Tree *root){
    while (root != NULL){
        printf("%s\n", root->path);
        root = root->next;
    }
}

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

struct Tree* setValue(struct Tree *root, char value[]){
    if (root->valor != NULL) free(root->valor);
    root->valor = malloc(strlen(value) + 1);
    strcpy(root->valor, value);
    return root;
}

struct Tree* setPath(struct Tree *root, char path[]){
    if (root != NULL){
        if (root->path != NULL) free(root->path);
        root->path = malloc(strlen(path) + 1);
        strcpy(root->path, path);
        return root;
    }
    return root;
}

char * pathFormatter(char path[]){
    char *token, *token2, pathHandler[MAXINPUT]="/", jar[MAXINPUT];
    strcpy(jar, path);
    token = strtok(jar, "/");
    while(token != NULL){
        token2 = strtok(NULL, "/");
        strcat(pathHandler, token);
        if (token2 != NULL) strcat(pathHandler, "/");
        token = token2;
    }
    token = malloc(strlen(pathHandler) + 1);
    return token;
}



/* set ola/tudobem?/hmmhereitgoes/works!/Ithinkso WORKS!! */
struct Tree* setCommmand(char path[], char value[], struct Tree *root){
    char *token, pathHandler[MAXINPUT]="/", *token2, pote[MAXINPUT]="/";
    struct Tree *temp, *temp2;
    int val = 1, val2 = 1, count=0, val3 = 0;
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
        val3 = 1;
        root = checkRootTree(root);
        root = setPath(root,"/");
    }
    root->Node = insert(root->Node, token);
    if (pathExists(root,pote) != NULL){
        temp = pathExists(root,pote);
        temp = setValue(temp, value);
        return root;
    }
    temp = nextNull(root);
    while( token != NULL ) {
        /* TODO- meter isto numa so funçao*/
        token2 = strtok(NULL, "/");
        if (count == 0 && val3){
        temp->next = checkRootTree(temp->next);
        temp = temp->next;
        }
        strcat(pathHandler, token);
        strcpy(pote, pathHandler);
        if(pathExists(root, pathHandler) == NULL) 
            temp = setPath(temp, pathHandler);
        temp2 = temp;
        temp = pathExists(root, pathHandler);
        strcat(pote, token);
        if (temp != temp2) val = 0;
        if (!strcmp(pote, temp->path)) val2 = 0;
        if (temp != NULL && temp != temp2 && val2)
            temp->Node = insert(temp->Node, token2);
        if (token2 != NULL){
            strcat(pathHandler, "/");
            temp = setValue(temp, "\0");
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
    temp = setValue(temp, value);
    return root;
}


/*Tenho de fazer uma funçao que verifica se o path existe ou nao,
se sim, adiciona a esse mesmo*/

struct Tree* pathExists(struct Tree *root, char path[]){
    struct Tree *temp;
    for (temp = root; temp != NULL; temp = temp->next){
        if (temp->path != NULL)
            if(!strcmp(temp->path,path))return temp;
    }
    return NULL;
}

void searchCommand(char value[], struct Tree *root){
    root= root->next;
    while (root != NULL){
        if (!strcmp(root->valor, value)){
            puts(root->path);
            break;
        }
        root = root->next;
    }
}

void printCommand(struct Tree *root){
    root = root->next;
    while (root != NULL){
        printf("%s %s\n", root->path, root->valor);
        root = root->next;
    }
}

void listCommand(struct Tree *root, char path[]){
    char *token, pathHandler[MAXINPUT]="/";
    if (strlen(path) != 0){
        token = strtok(path, "/");
        while( token != NULL ) {
            strcat(pathHandler, token);
            token = strtok(NULL, "/");
            if (token != NULL) strcat(pathHandler, "/");
        }
        while (root != NULL){
            if (!strcmp(root->path, pathHandler)) preOrder(root->Node);
            root = root->next;
        }
    }
    else preOrder(root->Node);
}