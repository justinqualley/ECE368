#include"file.h"
/*
The binary graph file argv[1] is an input file in binary format. Given a graph of m rows and n
columns, 0 < m,n ≤ SHRT MAX, the first two short’s stored in binary graph file are m and n, respectively.
Here, SHRT MAX is the largest short integer (see limits.h).
After those two short’s, the file is followed by a total of m×n short’s. All m×n short’s are within
the range of [0,SHRT MAX].
Out of these m×n short’s, the first n short’s are in row 0. Out of these n short’s, the first short is
at column 0 and the last short is at column n − 1. The next n short’s are in row 1. The last group of n
short’s are in row m−1.
The total size of the file is (2+mn)×sizeof(short) bytes. You may assume that all input files are all
correct
*/ 
short** read_graph(char* filename, short* m, short* n){
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL){
        fprintf(stderr, "Failed to open given binary file");
        return NULL;
    }
    fread(m, sizeof(short), 1, fptr);
    fread(n, sizeof(short), 1, fptr);
    short** graph = malloc((*m) * sizeof(short*));
    for(int i=0; i< *m; i++){
        graph[i] = malloc((*n) * sizeof(short));;
    }
    for(int i = 0; i < *m; i++){
        for(int j = 0; j < *n; j++){
            fread(&(graph[i][j]), sizeof(short), 1, fptr);
        }
    }
    fclose(fptr);
    return graph;
}
void graph_to_txt(short** graph, char* filename, short m, short n){
    FILE *fptr = fopen(filename, "w");
    fprintf(fptr, "%hd %hd\n", m, n);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            fprintf(fptr, "%hd", graph[i][j]);
            if(j < n - 1){
                fputc(' ', fptr);
            }
        }
        fputc('\n', fptr);
    }
    fclose(fptr);
}

void fastest_times(int* times, char* filename, short n){
    FILE* fptr = fopen(filename, "w");
    fwrite(&n, sizeof(n), 1, fptr);
    for(int i = 0; i < n; i++){
        fwrite(&(times[i]), sizeof(times[i]), 1, fptr);
    }
    fclose(fptr);
}

void fastest_path(Node* vertices, char* filename){
    FILE* fptr = fopen(filename, "w");
    int dist = vertices[0].dist;
    fwrite(&dist, sizeof(dist), 1, fptr);
    int v = 0;
    while((vertices[v]).cost >= 0){
        v++;
    }
    fwrite(&v, sizeof(v), 1, fptr);
    //printf("v: %d\n", v);
    short i, j;
    for(int k = v-1; k >= 0; k--){
        i = (vertices[k]).i;
        j = (vertices[k]).j;
        //printf("(%hd, %hd) ", i, j);
        fwrite(&i, sizeof(short), 1, fptr);
        fwrite(&j, sizeof(short), 1, fptr);
    }
    //printf("\n");
    fclose(fptr);
}
