#include<stdbool.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct _Node {
   int dist;
   int i;
   int j;
   short cost;
} Node;
void shortest(short**, int m, int n, int start);
short* extract_min(short* arr[], int *n);
void delete_root(short* arr[], int *n);
void insert(short* arr[], short* num, int *n);
bool checkBounds(int i, int j, int m, int n);
void heapify(short* arr[], int i, int n);
void swap(short **a, short **b);

