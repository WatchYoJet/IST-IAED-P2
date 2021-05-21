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
    int deep;
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

struct Node *  NewNode(char key[], struct Node *  left, struct Node *  right){
    struct Node *  node = (struct Node * )malloc(sizeof(struct Node * ));
    node->key = malloc(strlen(key) + 1);
    strcpy(node->key, key);
    node->left = left;
    node->right = right;
    node->height = 1;
    return node;
}

int height(struct Node *  h){
    if (h == NULL) return 0;
    return h->height;
}

void NewNodeHeight(struct Node * h){
    int height_l = height(h->left);
    int height_r = height(h->right);
    h->height = height_l > height_r ? height_l + 1 : height_r + 1;
}

struct Node *  rotL(struct Node *  h){
    struct Node *  x = h->right;
    h->right = x->left;
    x->left = h;
    NewNodeHeight(h);
    NewNodeHeight(x);
    return x;
}

struct Node *  rotR(struct Node *  h){
    struct Node *  x = h->left;
    h->left = x->right;
    x->right = h;
    NewNodeHeight(h);
    NewNodeHeight(x);
    return x;
}

struct Node *  rotLR(struct Node *  h){
    if (h==NULL) return h;
    h->left = rotL(h->left);
    return rotR(h);
}
struct Node *  rotRL(struct Node *  h){
    if (h==NULL) return h;
    h->right = rotR(h->right);
    return rotL(h);
}
int Balance(struct Node *  h) {
    if(h == NULL) return 0;
    return height(h->left) - height(h->right);
}

struct Node *  getbalance(struct Node *  h) {
    int balanceFactor;
    if (h==NULL) return h;
    balanceFactor= Balance(h);
    if (balanceFactor>1) {
        if ( Balance(h->left) >= 0 ) h = rotR(h);
        else h=rotLR(h);
    }
    else if(balanceFactor<-1){
        if (Balance(h->right)<=0) h = rotL(h);
        else h = rotRL(h);
    }
    else NewNodeHeight(h);
    return h;
} 

struct Node *  insert(struct Node *  h, char key[]){
    if (h == NULL) return NewNode(key, NULL, NULL);
    if (strcmp(key, h->key) < 0) h->left = insert(h->left, key);
    else h->right = insert(h->right, key);
    h = getbalance(h);
    return h;
}

struct Node * max(struct Node *  h){
    for (;h != NULL && h->right != NULL; h = h ->right );
    return h;
}

struct Node * minValueNode(struct Node *  h){
    for (;h != NULL && h->left != NULL; h = h ->left );
    return h;
}

struct Node * deleteNode(struct Node * root, char key[]){
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
}

void preOrder(struct Node *  h){
    if (h == NULL)return;
    preOrder(h->left);
    printf("%s ", h->key);
    preOrder(h->right);
}

void finnish(struct Node *root){
    root = root->left;
    if(root != NULL){
        free(root);
        finnish(root);
    }
}

int main(){
    char command[MAX_COMMAND_SIZE],input[MAXINPUT];
    char path[MAXINPUT], value[MAXINPUT], arguments[MAXINPUT- MAX_COMMAND_SIZE];
    struct Tree *root = NULL;
    while(1) {
        strcpy(arguments, "\0");
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
        root->deep = NULL;
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
    if (root->path != NULL) free(root->path);
    root->path = malloc(strlen(path) + 1);
    strcpy(root->path, path);
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
    char *token, pathHandler[MAXINPUT]="/", *token2, *formpath;
    struct Tree *temp, *temp2;
    int val = 1;

    formpath = pathFormatter(path);

    token = strtok(path, "/");
    if(root == NULL){
        root = checkRootTree(root);
        root = setPath(root,pathHandler);
    }
    root->Node = insert(root->Node, token);
    temp = root;

    if (pathExists(root,formpath) != NULL){
        temp = pathExists(root,formpath);
        temp = setValue(temp, value);
        return root;
    }

    temp = nextNull(root);
    while( token != NULL ) { 
        /* TODO- meter isto numa so funçao*/
        token2 = strtok(NULL, "/");
        strcat(pathHandler, token);
        if(pathExists(root, pathHandler) == NULL) 
            temp = setPath(temp, pathHandler);
        temp2 = temp;
        temp = pathExists(root, pathHandler);
        if (temp != temp2) val = 0;
        if (temp == NULL) temp = temp2;
        temp->Node = insert(temp->Node, token);
        if (token2 != NULL){
            temp->Node = insert(temp->Node, token2);
            strcat(pathHandler, "/");
            temp = setValue(temp, "\0");
        }
        temp = temp2;
        if (token2 != NULL && val){
            temp->next = checkRootTree(temp->next);
            temp = temp->next;
        }
        token = token2;
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
            if(strcmp(temp->path,path) == 0)return temp;
    }
    return NULL;
}


void searchCommand(char value[], struct Tree *root){
    while (root != NULL){
        if (!strcmp(root->valor, value)){
            puts(root->path);
            break;
        }
        root = root->next;
    }
}

void printCommand(struct Tree *root){
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