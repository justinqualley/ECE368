#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include <getopt.h>
#include "tree.h"
#include "file.h"
#include "eval.h"

void printInorder(Tnode* node)
{
    if (node == NULL) { return; }
    printInorder(node->left);
    printf("%d ", node->key);
    printInorder(node->right);
}
void printPreorder(Tnode* node)
{
    if (node == NULL) { return; }
    printf("%d ", node->key);
    printPreorder(node->left);
    printPreorder(node->right);
}

int main(int argc, char **argv){
    int out[3] = {0, 0, 0};
    if(argc >= 5){
        return EXIT_FAILURE;
    }
    int c, bflag = 0, eflag = 0;
    c = getopt(argc, argv, "be:");
    switch (c){
    case 'b': bflag = 1;
              break;
    case 'e': eflag = 1;
              break;
    default: return EXIT_FAILURE;
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
        tree_to_b(*root, argv[3]);
    }else if(eflag){
        int size;                                                   //Size of the preorder traversal of the tree
        int vflag;                                                  //Flag to set if on load, valid input file
        int *preorder = loadArray(argv[2], &size, &vflag);          //Load input into preorder[] array
        out[0] = vflag;
        if(preorder == NULL){
            fprintf(stdout, "%d,X,X", out[0]);
        }
        int *st = malloc(size*sizeof(int));                         //Create stack to validate if BST
        int top = -1;                                               //Init stack to size of array and set top to empty
        if(isbst(preorder, size, top, st)){                         
            out[1] = 1;
        }else{
            out[1] = 0;
        }
        Tnode *root = malloc(sizeof(Tnode));                        //Root node of BST to build
        if(root == NULL){
            fprintf(stderr, "Error: Line 75 malloc failed\n");
        }
        root = preBuild(preorder, 0, size-1);                       //Build BST
        printInorder(root); printf("\n");
        if(isbalanced(root)){
            out[2] = 1;
        }else{
            out[2] = 0;
        }
        printf("%d,%d,%d\n", out[0], out[1], out[2]);
    }
    return EXIT_SUCCESS;
}

