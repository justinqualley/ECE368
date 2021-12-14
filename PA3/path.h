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
void init_graph(Node*** graph, short** cost, int m, int n);
void print_graph(Node*** graph, short** cost, int m, int n);
void heapify_node(Node* arr[], int i, int n);
Node shortest(Node*** graph, Node** pq, short** cost, int size, int m, int n, int is, int js);
Node* extract_min(Node* arr[], int *n);
void delete_root(Node* arr[], int *n);
void heapify(Node* pq[], int size);
void explore(Node*** graph, Node **pq, short** cost, int size, int i, int j, int p, int q);
void swap_node(Node **a, Node **b);
void print_path(Node*** graph, Node** pq, int* size, int m, int n);

