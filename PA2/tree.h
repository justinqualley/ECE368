#include "hbt.h"
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

Tnode* insert(Tnode *root, int key);
Tnode* delete(Tnode *root, int key);
Tnode* getSuccessor(Tnode* curr);
Tnode* newNode(int key, Tnode *left, Tnode *right);
void buildTree(Tnode **root, char *filename);
Tnode *preBuild(int *a, int lidx, int ridx);
int getHeight(Tnode *node);
int max(int x, int y);

Tnode* cr(Tnode* old_root);

Tnode* ccr(Tnode* old_root);
