#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "tree.h"

int* loadArray(char *filename, int *size, int *vflag);
bool isbst(int *preorder, int size, int top, int *stack);
bool isbalanced(Tnode *root);
bool isempty(int top);
int getTop(int *stack, int *top);
int pop(int *stack, int *top);
void push(int *stack, int item, int *top, int size);

void buildBST_helper(int preIndex, int n, int pre[],int min, int max);
bool canRepresentBST(int arr[], int N);
