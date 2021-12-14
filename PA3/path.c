#include "path.h"

Node shortest(Node*** graph, Node** pq, short** cost, int size, int m, int n, int is, int js){
    int i, j, p, q;                                                 //Indexing variables
    init_graph(graph, cost, m, n);
    print_graph(graph, cost, m, n);
    //short tempDist = (graph[is][js])->dist;
    (graph[is][js])->dist = 0;                                       //Init src
    heapify(pq, size); 
    Node *u = NULL;                                                 //Node we will operate on each iteration
    while(size > 0){                                                //while pq not empty

        u = extract_min(pq, &size);                                 //extract the shortest path

        i = u->i;                                                   //Find it's location i.e. identifier
        j = u->j;                                                 
        if(i < m - 1){ p = i + 1; q = j;     explore(graph, pq, cost, size, i, j, p, q); } //Check bottom
        if(i > 0)    { p = i - 1; q = j;     explore(graph, pq, cost, size, i, j, p, q); } //Check top
        if(j < n - 1){ p = i;     q = j + 1; explore(graph, pq, cost, size, i, j, p, q); } //Check right
        if(j > 0)    { p = i;     q = j - 1; explore(graph, pq, cost, size, i, j, p, q); } //Check left
    }
    print_path(graph, pq, &size, m, n);                                                    //Print the distance and vertices of all exit possibilities
    /*for(i = 0; i < m*n; i++){
        printf("(%d, %d)\n ", (pq[i])->i, (pq[i])->i);
    }
    for(i = 0; i < size; i++){
        free(pq[i]);
    }
    free(pq);
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            free(graph[i][j]);
        }
        free(graph[i]);
    }
    free(graph);*/
    return *(pq[0]);                                                                      //Print path adds each dist back into PQ so we can easily get the shortest path
}
void print_graph(Node*** graph, short** cost, int m, int n){
    for(int i = 0; i < m; i++){                                         //Print out the graph to check we're good to start
        for(int j = 0; j < n; j++){
            printf("%d ", (graph[i][j])->cost);
        }
        printf("\n");
    }
}
void init_graph(Node*** graph, short** cost, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            (graph[i][j])->dist = SHRT_MAX;                                //Init distance to each node is infinity
            (graph[i][j])->cost = cost[i][j];                              //Cost to travel to this node
            (graph[i][j])->pred = NULL;
            (graph[i][j])->i = i;                                          //It's position we will use as it's identifier
            (graph[i][j])->j = j;
            (graph[i][j])->visited = false;
        }
    }
}
void print_path(Node*** graph, Node** pq, int* size, int m, int n){
    Node *scan = NULL;                                                                              //Node to scan over linked list of paths
    for(int i = 0; i < n; i++){                                                                     //Search through bottom row
        scan = (graph[m-1][i])->pred;                                                                
        printf("dist: %d, (%d, %d)", (graph[m-1][i])->dist, (graph[m-1][i])->i,(graph[m-1][i])->j);
        insert_node(pq, graph[m-1][i], size);                                                        //Insert each node back into PQ so we can extract min later
        //(*times)[i] = (graph[m-1][i])->dist;
        while(scan != NULL){
            printf("(%d, %d)", scan->i,scan->j);                                                    //Print out vertices of the path
            scan = scan->pred;
        }
        printf("\n");
    }
}
void explore(Node*** graph, Node **pq, short** cost, int size, int i, int j, int p, int q){
    if((graph[p][q])->dist > cost[p][q] + (graph[i][j])->dist && !(graph[p][q])->visited){     //Update distance to node required
        (graph[p][q])->dist = cost[p][q] + (graph[i][j])->dist;                               //d[v] = d[u] + w<u,v>
        (graph[p][q])->pred = graph[i][j];                                                    //pred[v] = u
        heapify(pq, size);                                                                  //Update(PQ)
    }
    (graph[i][j])->visited = true;                                                           
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
