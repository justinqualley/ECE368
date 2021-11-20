#include "tree.h"

Tnode* minSearch(Tnode* root)
{
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Tnode *maxSearch(Tnode* root){
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

Tnode* delete(Tnode *root, int key){
    if(root == NULL){
        return root;
    }
    if(key < root->key){
        root->left = delete(root->left, key);
    }else if(key > root->key){
        root->right = delete(root->right, key);
    }else{
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            Tnode *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }else{ // One child case
                *root = *temp; // Copy the contents of
            }              // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            Tnode *tmp = maxSearch(root->left);
            root->key = tmp->key;
            root->left = delete(root->left, tmp->key);
        }
        /*if(root->left == NULL){
            Tnode* tmp = root->right;
            free(root);
            //printf("deleted %d\n", root->key);
            return tmp;
        }else if(root->right == NULL){
            Tnode* tmp = root->left;
            free(root);
            //printf("deleted %d\n", root->key);
            return tmp;
        }
        Tnode *tmp = getPredecessor(root);
        root->key = tmp->key;
        root->right = delete(root->right, tmp->key);*/
    }
    if(root == NULL){
        return root;
    }
    int b = getBalance(root);
    if(b > 1 && root->left->height >= 0){
        return cr(root);
    }
    if(b < -1 && root->right->height <= 0){
        return ccr(root);
    }
    if(b > 1 && root->left->height < 0){
        root->left = ccr(root->left);
        return cr(root);
    }
    if(b < -1 && root->left->height > 0){
        root->right = cr(root->right);
        return ccr(root);
    }
    return root;
}
Tnode* insert(Tnode *root, int key){
    if(root == NULL){
        return newNode(key, NULL, NULL);
    }
    if(key <= root->key){
        root->left = insert(root->left, key);
    }else{
        root->right = insert(root->right, key);
    }
    int b = getBalance(root);
    root->height = b;
    //Unbalanced on left
    if(b > 1 && key <= root->left->key){
        return cr(root);
    }
    //Unbalanced on right
    if(b < -1 && key > root->right->key){
        return ccr(root);
    }
    //Unbalanced on left but prior rotation required
    if(b > 1 && key > root->left->key){ //
        root->left = ccr(root->left);
        return cr(root);
    }
    //Unbalanced on right but prior rotation required
    if(b < -1 && key <= root->right->key ){ ////
        root->right = cr(root->right);
        return ccr(root);
    }
    return root;
}

void buildTree(Tnode **root, char *filename)
{
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL){                       //What should I return?
        return;
    }
    int value;
    char op;
    while(fread(&value, sizeof(int), 1, fptr) > 0 && fread(&op, sizeof(char), 1, fptr) > 0){ 
        if(op == 'i'){
            //printf("insert %d:\n", value);
            *root = insert(*root, value);
        }else if(op == 'd'){
            //printf("delete %d:\n", value);
            *root = delete(*root, value);
        }
    }
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
    //printf("cr\n");
    Tnode *new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    old_root->height = getBalance(old_root);
    new_root->height = getBalance(new_root);
    return new_root;
}
Tnode* ccr(Tnode *old_root){
    //printf("ccr\n");
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

Tnode* preBuild(int *a, int lidx, int ridx){   
    if (lidx > ridx){
        //printf("NULL return\n");
        return NULL;
    }   
    Tnode *root = malloc(sizeof(*root));   
    if (root != NULL) {     
        root->key = a[lidx]; 
        //printf("key: %d\n", root->key);    
        int partition_idx = lidx + 1;     
        while (partition_idx <= ridx && a[partition_idx] <= a[lidx]){ partition_idx++; }    
        //printf("go left\n");
        root->left = preBuild(a, lidx+1,partition_idx-1);     
        //printf("go right\n");
        root->right = preBuild(a, partition_idx, ridx);   
    }     
    return root; 
}

