#include <stdio.h>
#include <ctype.h>
#include "tree.h"

void txt_to_b(char* input, char* output);
void traverse(Tnode* node, int num, char ch, FILE *fp1);
void tree_to_b(Tnode *root, char* output);
