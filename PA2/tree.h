#include "hbt.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

Tnode* insert(Tnode *root, int key);
Tnode* delete(Tnode *root, int key);
void destroy(Tnode *root);
Tnode* balance(Tnode *root);
Tnode* newNode(int key, Tnode *left, Tnode *right);
void buildTree(Tnode **root, char *filename, int *valid);
Tnode *preBuild(int *preorder, int *status, int *i, int size);
int getBalance(Tnode *root);
int getHeight(Tnode *node);
int max(int x, int y);
Tnode* cr(Tnode* old_root);
Tnode* ccr(Tnode* old_root);
