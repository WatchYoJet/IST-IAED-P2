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

int removeSpacesHandler(char input[]){
    int count = 0, usable = 0, reset=0;
    while(input[count] != '\0'){
        if (input[count] != ' '&& input[count] != '\n' && input[count] != '\t'){
            ++usable;
            usable += reset;
            reset = 0;
        }
        else ++reset;
        ++count;
    }
    return usable;
}

int main(){
    char command[MAX_COMMAND_SIZE]="",input[MAXINPUT]="";
    char path[MAXINPUT]="", value[MAXINPUT]="", arguments[MAXINPUT- MAX_COMMAND_SIZE]="";
    int max = 0;
    struct Tree *root = NULL;
    while(1){
        arguments[0]='\0';
        value[0]='\0';
        path[0]='\0';
        fgets(input, MAXINPUT, stdin);
        max = removeSpacesHandler(input);
        input[max] = '\0';
        sscanf(input, "%s %[^\n]", command, arguments);
        sscanf(arguments, "%s %[^\n]" ,path, value);
        if (isCommand(command,"help")) helpCommand();
        else if (isCommand(command,"set"))root = setCommmand(path, value, root); 
        else if (isCommand(command,"print")) printCommand(root);
        else if (isCommand(command,"find")) findCommand(root, arguments);
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
        root->valor = malloc(2);
        strcpy(root->valor, "");
        root->path = malloc(2);
        strcpy(root->path, "");
    }
    return root;
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
        root->path[0] = '\0';
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
    char *token=NULL, pathHandler[MAXINPUT], *token2=NULL, pote[MAXINPUT];
    struct Tree *temp=NULL, *temp2=NULL;
    int val = 1, val2 = 1, count=0, val3 = 0;
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
        val3 = 1;
        root = checkRootTree(root);
        root = setPath(root,"/");
    }
    root->Node = insert(root->Node, token);
    temp = pathExists(root,pote);
    if (temp != NULL){
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
    struct Tree *temp=NULL;
    for (temp = root; temp != NULL; temp = temp->next){
        if (temp->path != NULL)
            if(!strcmp(temp->path,path))return temp;
    }
    return NULL;
}

void searchCommand(char value[], struct Tree *root){
    int AV=1;
    if(root != NULL) root = root->next;
    while (root != NULL){
        if (!strcmp(root->valor, value)){
            puts(root->path);
            AV = 0;
            break;
        }
        root = root->next;
    }
    if (AV) puts("not found");
}

void printCommand(struct Tree *root){
    if(root != NULL) root = root->next;
    while (root != NULL){
        if (strcmp(root->valor,""))
            printf("%s %s\n", root->path, root->valor);
        root = root->next;
    }
}

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
            if (!strcmp(root->path, pathHandler)){
                preOrder(root->Node);
                AV = 0; 
            }
            root = root->next;
        }
        if (AV) puts("not found");
    }
    else if(root != NULL) preOrder(root->Node);
}

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
        if (!strcmp(root->path, pathHandler)){
            if (!strcmp(root->valor, "")) valE2 = 1;
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