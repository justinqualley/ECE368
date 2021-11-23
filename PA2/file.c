#include "file.h"

void txt_to_b(char* input, char* output){
    int num;
    FILE *fp1, *fp2;
    char ch;
    fp1 = fopen(input, "r");
    if (!fp1) {
            printf("Unable to open the input file!!\n");
            return;
    }
    fp2 = fopen(output, "wb");
    if (!fp2) {
        printf("Unable to open the output file!!\n");
        return;
    }
    while (fread(&num, sizeof(int), 1, fp1) > 0) {
        fread(&ch, sizeof(char), 1, fp1);
        fwrite(&num, sizeof(int), 1, fp2);
        fwrite(&ch, sizeof(char), 1, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    return;
}

void tree_to_b(Tnode *root, char* output){
    int num = 0;
    FILE *fp1;
    char ch = '\0';
    fp1 = fopen(output, "wb");
    if (!fp1) {
        printf("Unable to open the output file!!\n");
        return;
    }
    traverse(root, num, ch, fp1);
    fclose(fp1);
    return;
}

void traverse(Tnode* node, int num, char ch, FILE *fp1)
{
    if (node == NULL) { return; }
    //printf("%d ", node->key);
    if(node -> right != NULL && node -> left != NULL){
        ch = 0x3;
    }else if(node->right != NULL){
        ch = 0x1;
    }else if(node->left != NULL){
        ch = 0x2;
    }else{
        ch = 0x0;
    }
    num = node->key;
    fwrite(&num, sizeof(int), 1, fp1);
    fwrite(&ch, sizeof(char), 1, fp1);
    traverse(node->left, num, ch, fp1);
    traverse(node->right, num, ch, fp1);
}
