#include "tree.h"
#define INT_MAX 2147483647
#define INT_MIN -2147483647

void destroy(Tnode *root){
    if(root == NULL) { 
        return; 
    }
    destroy(root->left);
    destroy(root->right);
    free(root);
}
Tnode* balance(Tnode *root){
    int b = getBalance(root);                           
    root->height = b;                                   //Set the new balance after deletion
    if(b > 1 && root->left->height >= 0){               //If unbalanced on left
        return cr(root);
    }
    if(b < -1 && root->right->height <= 0){             //If unbalanced on right
        return ccr(root);
    }
    if(b > 1 && root->left->height < 0){                //If unbalanced on left, but prior rotation required
        root->left = ccr(root->left);
        return cr(root);
    }
    if(b < -1 && root->right->height > 0){              //If unbalanced on right, but prior rotation required
        root->right = cr(root->right);
        return ccr(root);
    }
    return root;
}
Tnode* delete(Tnode *root, int key){
    if(root == NULL){                                   //If tree already empty
        return root;
    }
    if(key < root->key){                                //Binary search
        root->left = delete(root->left, key);           //
    }else if(key > root->key){                          //
        root->right = delete(root->right, key);         //
    }else{                                              //Key found
        if(root->left == NULL){                         //Has a right branch we need to connect
            Tnode* tmp = root->right;
            free(root);
            return tmp;
        }else if(root->right == NULL){
            Tnode* tmp = root->left;                    //Has a left branch we need to connect
            free(root);
            return tmp;
        }
        Tnode* inprd = root->left;                      //Has two branches, need inorder predecessor
        while (inprd->right != NULL) {                  
            inprd = inprd->right;
        }
        root->key = inprd->key;
        inprd->key = INT_MAX;                           //Set inorder to number we can uniquely find in case of duplicates when searching
        root->left = delete(root->left, inprd->key);    //Delete node and recursively maintain balance
    }
    if(root == NULL){                                   //If we deleted the last node
        return root;
    }
    root = balance(root);                               //Balance at every node we visted w/ recursion
    return root;
}
Tnode* insert(Tnode *root, int key){
    if(root == NULL){                                   //If we have reached the insertion point
        return newNode(key, NULL, NULL);
    }
    if(key <= root->key){                               //Binary search
        root->left = insert(root->left, key);
    }else{
        root->right = insert(root->right, key);
    }
    root = balance(root);                               //Check balance at each node we visit
    return root;
}

Tnode* buildTree(Tnode *root, char *filename, int *valid)
{
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL){      
        root = NULL;                
        return root;
    }
    int value;
    char op;
    while(fread(&value, sizeof(int), 1, fptr) > 0 && fread(&op, sizeof(char), 1, fptr) > 0){ 
        if(op == 'i'){
            root = insert(root, value);
        }else if(op == 'd'){
            root = delete(root, value);
        }
    }
    if(!(ftell(fptr) % (sizeof(char) + sizeof(int)))){  //If we built a tree but of wrong format
        *valid = 1;
    }
    return root;
}

Tnode* newNode(int key, Tnode *left, Tnode *right){
    Tnode *n = malloc(sizeof(Tnode));
    if(n == NULL){
        fprintf(stderr, "Error Line 25: malloc failed");
    }
    n->key = key;
    n->height = 0;
    n->left = left;
    n->right = right;
    return n;
}
Tnode* cr(Tnode *old_root){
    Tnode *new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    old_root->height = getBalance(old_root);
    new_root->height = getBalance(new_root);
    return new_root;
}
Tnode* ccr(Tnode *old_root){
    Tnode *new_root = old_root->right;
    old_root->right = new_root->left;
    new_root->left = old_root;
    old_root->height = getBalance(old_root);
    new_root->height = getBalance(new_root);
    return new_root;
}
int getBalance(Tnode *root){
    if(root == NULL){
        return 0;
    }else{
        return getHeight(root->left) - getHeight(root->right);
    }
}
int getHeight(Tnode *node){
    if(node == NULL){
        return 0;
    }
    return 1 + max(getHeight(node->left), getHeight(node->right));
}
int max(int x, int y){
    return x >= y ? x : y;
}

Tnode* preBuild(int *preorder, int *status, int *i, int size){   
    char code = status[*i];
    Tnode *root = newNode(preorder[(*i)++], NULL, NULL); 
    switch(code){
        case 1: root->right = preBuild(preorder, status, i, size);  //Right child node
                break;
        case 2: root->left = preBuild(preorder, status, i, size);   //Left child node
                break;
        case 3: root->left = preBuild(preorder, status, i, size);   //Two children
                root->right = preBuild(preorder, status, i, size);
                break;
        default: return root;
    }
    return root;
}

