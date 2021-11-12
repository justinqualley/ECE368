#include "eval.h"
#define INT_MAX 2147483647
#define INT_MIN -2147483648
/*
BST Criteria:
The left subtree of a node contains only nodes with keys lesser than the node’s key.
The right subtree of a node contains only nodes with keys greater than the node’s key.
The left and right subtree each must also be a binary search tree.
*/
/*
HB Criteria:
A tree is height-balanced if every node has balance 0, 1, or –1
*/
int* loadArray(char *filename, int *size){
    int *arr = NULL;
   
    FILE * fptr = fopen(filename, "rb"); // open a file whose name is filename for reading
    if(fptr == NULL) {                   // if fopen fails, return false. Do NOT fclose
      *size = 0;
      return arr;
    }
    fseek(fptr, 0, SEEK_END);
    *size = ftell(fptr) / (sizeof(int) + sizeof(char));      //Number of items in array
    arr = malloc(*size*sizeof(int));  
    int num;
    int ch;
    if(arr == NULL){
        fprintf(stderr, "Malloc failed");
        return arr;
    }
    fseek(fptr, 0, SEEK_SET);               //Set back to top for reading
    int i = 0;
    while (fread(&num, sizeof(int), 1, fptr) > 0) {
        //printf("added %d\n", num);
        arr[i] = num;
        fread(&ch, sizeof(char), 1, fptr);
        i++;
    }
    fclose(fptr);
    return arr;
}

bool isbst(int* preorder, int size, int top, int *stack)
{
    int root = INT_MIN;
    for (int i=0; i < size; i++){
        int tmp = getTop(stack, &top);
        if(i == size-1 && preorder[i] < tmp){ return false; }                       //If the last node added is on the left, we need right to be complete
        else if(i == 1 && preorder[i] > stack[top]){ return false; }                //If we go right immedeiately CAN I DO THIS?
        else if(preorder[i] < root){ return false; }                                //If in the right subtree we find a node less than root
        while(!isempty(top) && preorder[i]>stack[top]){ root = pop(stack, &top); }  //Keep setting new root by traversing through right tree when neccessary
        push(stack, preorder[i],  &top, size);                                      //Push if stack empty are we are traversing left
    }
    return true;
}
bool isempty(int top){
    return (top < 0);
}
int getTop(int *stack, int *top){
    return stack[*top];
}
int pop(int *stack, int *top){
    int tmp = stack[*top];
    (*top)--;
    return tmp;
}
void push(int *stack, int item, int *top, int size){
    if(*top >= size -1){
        printf("stack empty\n");
        return; 
    }
    stack[++(*top)] = item;
    return;
}
/*void buildBST_helper(int preIndex, int n, int pre[],int min, int max){
    if (preIndex >= n)
        return;
 
    if (min <= pre[preIndex] && pre[preIndex] <= max) {
        // build node_
        int rootData = pre[preIndex];
        preIndex++;
 
        // build left subtree
        buildBST_helper(preIndex, n, pre, min, rootData);
 
        // build right subtree
        buildBST_helper(preIndex, n, pre, rootData, max);
    }
    // else
    // return NULL;
}*/
 
/*bool canRepresentBST(int arr[], int N)
{
    // code here
    int min = INT_MIN, max = INT_MAX;
    int preIndex = 0;
 
    buildBST_helper(preIndex, N, arr, min, max);
 
    return preIndex == N;
}*/
