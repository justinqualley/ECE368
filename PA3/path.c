#include "path.h"

short shortest(Node*** grid, Node** pq, short** cost, int size, int m, int n, int is, int js){
    int i, j;
    for(i = 0; i < m; i++){                                         //Print out the grid to check we're good to start
        for(j = 0; j < n; j++){
            printf("%d ", (grid[i][j])->cost);
        }
        printf("\n");
    }
    printf("\n");
    Node *u = NULL;                                                 //Node we will operate on each iteration
    (grid[is][js])->dist = 0;                                       //Init src
    heapify(pq, size); 
    int p;                                                          //Indexing variable for adjacent nodes
    int q;                                                          //Indexing variable for adjacent nodes
    while(size > 0){                                                //while pq not empty
        u = extract_min(pq, &size);                                 //extract the shortest path
        i = u->i;                                                   //Find it's location i.e. identifier
        j = u->j;                                                 
        if(i < m - 1){ p = i + 1; q = j;     explore(grid, pq, cost, size, i, j, p, q); } //Check bottom
        if(i > 0)    { p = i - 1; q = j;     explore(grid, pq, cost, size, i, j, p, q); } //Check top
        if(j < n - 1){ p = i;     q = j + 1; explore(grid, pq, cost, size, i, j, p, q); } //Check right
        if(j > 0)    { p = i;     q = j - 1; explore(grid, pq, cost, size, i, j, p, q); } //Check left
    }
    print_path(grid, pq, &size, m, n);                                                    //Print the distance and vertices of all exit possibilities
    size = (pq[0])->dist;
    /*for(i = 0; i < m*n; i++){
        printf("(%d, %d)\n ", (pq[i])->i, (pq[i])->i);
    }
    for(i = 0; i < size; i++){
        free(pq[i]);
    }
    free(pq);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            free(grid[i][j]);
        }
        free(grid[i]);
    }
    free(grid);*/
    return size;                                                                         //Print path adds each dist back into PQ so we can easily get the shortest path
}
void print_path(Node*** grid, Node** pq, int* size, int m, int n){
    Node *scan = NULL;                                                                              //Node to scan over linked list of paths
    for(int i = 0; i < n; i++){                                                                     //Search through bottom row
        scan = (grid[m-1][i])->pred;                                                                
        printf("dist: %d, (%d, %d)", (grid[m-1][i])->dist, (grid[m-1][i])->i,(grid[m-1][i])->j);
        insert_node(pq, grid[m-1][i], size);                                                        //Insert each node back into PQ so we can extract min later
        while(scan != NULL){
            printf("(%d, %d)", scan->i,scan->j);                                                    //Print out vertices of the path
            scan = scan->pred;
        }
        printf("\n");
    }
}
void explore(Node*** grid, Node **pq, short** cost, int size, int i, int j, int p, int q){
    if((grid[p][q])->dist > cost[p][q] + (grid[i][j])->dist && !(grid[p][q])->visited){     //Update distance to node required
        (grid[p][q])->dist = cost[p][q] + (grid[i][j])->dist;                               //d[v] = d[u] + w<u,v>
        (grid[p][q])->pred = grid[i][j];                                                    //pred[v] = u
        heapify(pq, size);                                                                  //Update(PQ)
    }
    (grid[i][j])->visited = true;                                                           
}
void heapify(Node* pq[], int size){
    for(int k = (size/2) - 1; k >= 0; k--){
        heapify_node(pq, k, size);
    }
}
void heapify_node(Node* arr[], int i, int n){
    if (n == 1){
        return;
    }else{
        int min = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && (arr[l])->dist < (arr[min])->dist){
            min = l;
        }
        if (r < n && (arr[r])->dist < (arr[min])->dist){
            min = r;
        }
        if (min != i){
            swap_node(&arr[i], &arr[min]);
            heapify_node(arr, n, min);
        }
    }
}
Node* extract_min(Node* arr[], int *n){
    Node* min = arr[0];
    swap_node(&arr[0], &arr[*n - 1]);
    *n -= 1;
    for(int i = (*n/2) - 1; i >= 0; i--){
        heapify_node(arr, i, *n);
    }
    return min;
}
void delete_root(Node* arr[], int *n){
    swap_node(&arr[0], &arr[*n - 1]);
    *n -= 1;
    for(int i = (*n/2) - 1; i >= 0; i--){
        heapify_node(arr, i, *n);
    }
}
void insert_node(Node* arr[], Node *s, int *n){
    if(*n == 0){
        arr[0] = s;
        *n += 1;
    }else{
        arr[*n] = s;
        *n += 1;
        for(int i = (*n/2) - 1; i >= 0; i--){
            heapify_node(arr, i, *n);
        }
    }
}
void swap_node(Node **a, Node **b){
    //printf("time to swap\n");
    Node *temp = *b;
    *b = *a;
    *a = temp;
}
