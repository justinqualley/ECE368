#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include <getopt.h>
#include "tree.h"
#include "file.h"
#include "eval.h"
#define COUNT 10

void print2DUtil(Tnode *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Tnode *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
void printInorder(Tnode* node)
{
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInorder(node->left);
 
    /* then print the data of node */
    printf("%d ", node->key);
 
    /* now recur on right child */
    printInorder(node->right);
}

int main(int argc, char **argv){
    if(argc >= 5){
        return EXIT_FAILURE;
    }
    int c, bflag = 0, eflag = 0;
    c = getopt(argc, argv, "be:");
    switch (c){
    case 'b': bflag = 1;
              break;
        //Check for valid number if input arguments
        //Option "-b": Building a height-balanced BST
        //perform height balancing search and insert
        //create pre-order traversal output
    case 'e': eflag = 1;
              break;
        //Option "-e": Evaluating a height-balanced BST
        //readInput
        //evaluate if valid file, is a BST, and is height balanced
      default:
        return EXIT_FAILURE;
    }
    if(bflag){
        char *filename = argv[2];
        //txt_to_b(filename, argv[3]);
        Tnode **root = malloc(sizeof(Tnode));
        if(root == NULL){
            fprintf(stderr, "Error: Line 75 malloc failed\n");
        }
        buildTree(root, filename);
        printInorder(*root);
        printf("\n");
    }else if(eflag){
        int size;
        int *array = loadArray(argv[2], &size);
        /*for(int i = 0; i < size; i++){
            printf("%d ",array[i]);
        }*/
        //size = sizeof(*array) / sizeof(array[0]);
        //printf("size: %d\n", size);
        int *st = malloc(size*sizeof(int)); //Stack
        int top = -1;
        if(isbst(array, size, top, st)){
            printf("can\n");
        }else{
            printf("can't\n");
        }
    }
    return EXIT_SUCCESS;
}

