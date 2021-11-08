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
