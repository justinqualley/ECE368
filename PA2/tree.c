#include "tree.h"

Tnode* getSuccessor(Tnode* curr)
{
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
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
        if(root->left == NULL){
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
        Tnode *tmp = getSuccessor(root->right);
        root->key = tmp->key;
        root->right = delete(root->right, tmp->key);
    }
    return root;
}
Tnode* insert(Tnode *root, int key){
    Tnode *pcurr = NULL;
    Tnode *pya = NULL;
    Tnode *curr = root;
    Tnode *ya = root;
    Tnode *n = NULL;
    while(curr != NULL){
        //prev = curr;
        if(key <= curr->key){
            n = curr->left;
        }else{
            n = curr->right;
        }
        if(n != NULL && n->height != 0){
            pya = curr;
            ya = n;
        }
        pcurr = curr;
        curr = n;
    }
    n = newNode(key, NULL, NULL);
    n->height = 0;
    if(pcurr == NULL){
        root = n;
    }else{
        if(key < pcurr->key){
            pcurr->left = n;
        }else{
            pcurr->right = n;
            curr = ya;
            while(curr != n){
                if(key < curr->key){
                    curr->height += 1;
                    curr = curr->left;
                }else{
                    curr->height -= 1;
                    curr = curr->right;
                }
            }
            if((ya->height < 2) && (ya->height > -2)){
                return root;
            }
            Tnode* child = malloc(sizeof(Tnode));
            if(key < ya->key){
                child = ya->left;
            }else{
                child = ya->right;
            }
            // the subtree rooted at ya needs balancing 
            // curr points to the new root of the subtree 
            // pya has to point to curr after rebalancing 
            // both ya and child are unbalanced in the same 
            // direction 
            if ((ya->height == 2) && (child->height == 1)){   
                curr = cr(ya); // clockwise rotation   
                ya->height = 0;   
                child->height = 0;
            }
            if ((ya->height == -2) && (child->height == -1)){   
                curr = ccr(ya); // clockwise rotation   
                ya->height = 0;   
                child->height = 0;
            }
            if((ya->height == 2) && (child->height == -1)){
                ya->left = ccr(child);
                curr = cr(ya); //SEGFAULT
                if(curr->height == 0){
                    ya->height = 0;
                    child->height = 0;
                }else{
                    if(curr->height == 1){
                        ya->height = -1;
                        child->height = 0;
                    }else{
                        ya->height = 0;
                        child->height = 1;
                    }
                    curr->height = 0;
                }
            }
            if((ya->height == -2) && (child->height == 1)){
                ya->right = cr(child);
                curr = ccr(ya);
                if(curr->height == 0){
                    ya->height = 0;
                    child->height = 0;
                }else{
                    if(curr->height == -1){
                        ya->height = 1;
                        child->height = 0;
                    }else{
                        ya->height = 0;
                        child->height = -1;
                    }
                    curr->height = 0;
                }
            }
            if(pya == NULL){
                root = curr;
            }else{
                if(key < pya->key){
                    pya->left = curr;
                }else{
                    pya->right = curr;
                }
            }
            return root;
        }
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
    n->left = left;
    n->right = right;
    //printf("Created Node: %d\n", key);
    return n;
}


void postOrder(){

}

Tnode* cr(Tnode *old_root){
    Tnode *new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    return new_root;
}

Tnode* ccr(Tnode *old_root){
    Tnode *new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    return new_root;
}
