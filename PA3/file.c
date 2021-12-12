#include"file.h"
/*
The binary grid file argv[1] is an input file in binary format. Given a grid of m rows and n
columns, 0 < m,n ≤ SHRT MAX, the first two short’s stored in binary grid file are m and n, respectively.
Here, SHRT MAX is the largest short integer (see limits.h).
After those two short’s, the file is followed by a total of m×n short’s. All m×n short’s are within
the range of [0,SHRT MAX].
Out of these m×n short’s, the first n short’s are in row 0. Out of these n short’s, the first short is
at column 0 and the last short is at column n − 1. The next n short’s are in row 1. The last group of n
short’s are in row m−1.
The total size of the file is (2+mn)×sizeof(short) bytes. You may assume that all input files are all
correct
*/ 
short** read_grid(char* filename, short* m, short* n){
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL){
        fprintf(stderr, "Failed to open given binary file");
        return NULL;
    }
    fread(m, sizeof(short), 1, fptr);
    fread(n, sizeof(short), 1, fptr);
    short *buffer = malloc(sizeof(short) * (*m * *n));
    if(buffer == NULL){ fprintf(stderr, "malloc failed"); }
    short **grid = malloc(sizeof(short)* *m);
    if(grid == NULL){ fprintf(stderr, "malloc failed"); }
    for (int i = 0; i < *m; i++){
        grid[i] = &buffer[i * *n];
    }
    for(int i = 0; i < *m; i++){
        for(int j = 0; j < *n; j++){
            fread(&(grid[i][j]), sizeof(short), 1, fptr);
        }
    }
    fclose(fptr);
    return grid;
}
void grid_to_txt(short** grid, char* filename, short m, short n){
    FILE *fptr = fopen(filename, "w");
    fprintf(fptr, "%hd %hd\n", m, n);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            fprintf(fptr, "%hd", grid[i][j]);
            fputc(' ', fptr);
        }
        fputc('\n', fptr);
    }
    fclose(fptr);
}
