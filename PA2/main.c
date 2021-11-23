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
        int valid = 0;
        Tnode **root = malloc(sizeof(Tnode));
        if(root == NULL){
            fprintf(stderr, "Error: Line 75 malloc failed\n");
        }
        buildTree(root, filename, &valid);
        if(root == NULL){ 
            fprintf(stdout, "%d\n", -1); 
            return EXIT_FAILURE; 
        }
        tree_to_b(*root, argv[3]);
        if(valid == 0) { 
            fprintf(stdout, "%d\n", 0);
            return EXIT_FAILURE; 
        }
        fprintf(stdout, "%d\n", 1);
        destroy(*root);
        free(root);
    }else if(eflag){
        int size;                                                   //Size of the preorder traversal of the tree
        int vflag;                                                  //Valid input file flag
        int *preorder = NULL;                                       //Load keys into array
        int *status = NULL;                                         //Load children status into array
        loadArray(argv[2], &size, &vflag, &preorder, &status);      //Load input into preorder[] array
        out[0] = vflag;
        if(preorder == NULL){                                       //Exit action when invalid file
            fprintf(stdout, "%d,X,X", out[0]);
            return EXIT_FAILURE;
        }
        int *st = malloc(size*sizeof(int));                         //Create stack to validate if BST
        int top = -1;                                               //Init stack to size of array and set top to empty
        if(isbst(preorder, size, top, st)){ out[1] = 1; }           //If bst set first element to 1
        free(st);
        /*Tnode *root = malloc(sizeof(Tnode));                        //Root node of BST to build
        if(root == NULL){
            fprintf(stderr, "Error: Line 75 malloc failed\n");
        }
        int *ip = malloc(sizeof(int));
        int i = 0;
        *ip = i;
        root = preBuild(preorder, status, ip, size);                //Build BST if valid
        if(isbalanced(root)){ out[2] = 1; }                         //If height-balanced set second element to 1
        destroy(root);                                              //No longer need tree in memory
        free(ip);
        //free(st);
        fprintf(stdout, "%d,%d,%d\n", out[0], out[1], out[2]);      //Final evaluation display*/
    }
    return EXIT_SUCCESS;
}

