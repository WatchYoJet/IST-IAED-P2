#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char * key; 
    struct Node *  left; 
    struct Node *  right;
    int height;    
};

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

int main(){
    struct Node *root = NULL;
    root = insert(root, "ola!");
    root = insert(root, "ola/amigos");
    root = insert(root, "amigos!");
    root = insert(root, "amongus");
    root = insert(root, "dinis!");
    preOrder(root);
    root = deleteNode(root, "dinis!");
    puts("\n------------");
    preOrder(root);
    root = deleteNode(root, "amongus");
    puts("\n------------");
    preOrder(root);
    root = deleteNode(root, "amigos!");
    puts("\n------------");
    preOrder(root);
    root = deleteNode(root, "ola/amigos");
    puts("\n------------");
    preOrder(root);
    return 0;
}
