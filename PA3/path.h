#include<stdbool.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct _Node {
   short dist;
   short cost;
   struct _Node *pred;
   int i;
   int j;
   bool visited;
} Node;
void insert_node(Node* arr[], Node *s, int *n);
void status(Node ***grid, int x, int y, int n, int m);
void heapify_node(Node* arr[], int i, int n);
void shortest(short**, int m, int n, int start);
Node* extract_min(Node* arr[], int *n);
void delete_root(Node* arr[], int *n);
void insert(short* arr[], short* num, int *n);
bool checkBounds(int i, int j, int m, int n);
void heapify(Node* pq[], int size);
void explore(Node*** grid, Node **pq, short** cost, int size, int i, int j, int p, int q);
void swap(short **a, short **b);
void swap_node(Node **a, Node **b);
int min(int a, int b);
bool find(Node* arr[], Node* n, int size);

