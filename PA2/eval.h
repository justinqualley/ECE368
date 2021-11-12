#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

int* loadArray(char *filename, int *size);
bool isbst(int* preorder, int size, int top, int *stack);
bool isempty(int top);
int getTop(int *stack, int *top);
int pop(int *stack, int *top);
void push(int *stack, int item, int *top, int size);

void buildBST_helper(int preIndex, int n, int pre[],int min, int max);
bool canRepresentBST(int arr[], int N);
