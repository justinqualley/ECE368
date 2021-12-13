#include "path.h"

void shortest(short** cost, int m, int n, int start){
    int size = 0;
    int i;
    int j;
    Node *vertex;                                                   //Structure to hold each data for each vertex of graph
    Node **pq = malloc(m*n * sizeof *pq);                           //Array of pointers to nodes that functions as a priority queue
    Node ***grid = malloc(n * sizeof(Node**));                      //2D Array of pointers to nodes that function as our graph
    for(i = 0; i < n; i++){ grid[i] = malloc(m * sizeof(Node*)); }  //Allocate 2D array of pointers
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            vertex = malloc(sizeof *vertex);
            vertex->dist = SHRT_MAX;                                //Init distance to each node is infinity
            vertex->cost = cost[i][j];                              //Cost to travel to this node
            vertex->pred = NULL;
            vertex->i = i;                                          //It's position we will use as it's identifier
            vertex->j = j;
            grid[i][j] = vertex;
            insert_node(pq, grid[i][j], &size);                     //Put each vertex in the PQ
        }
    }
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            printf("%d ", (grid[i][j])->cost);
        }
        printf("\n");
    }
    printf("\n");
    Node *u = NULL;
    (grid[0][0])->dist = 0;
    int p;
    int q;
    while(size > 0){
        u = extract_min(pq, &size);
        i = u->i;
        j = u->j;
        
        if(i < m - 1){ p = i+1; q = j; explore(grid, pq, cost, size, i, j, p, q);  }
            /*if((grid[i+1][j])->dist > cost[i+1][j] + (grid[i][j])->dist && !(grid[i+1][j])->visited){
                (grid[i+1][j])->dist = cost[i+1][j] + (grid[i][j])->dist;
                (grid[i+1][j])->pred = grid[i][j];
            }
            heapify(pq, size);
        }*/
        if(i > 0){ p = i-1; q = j; explore(grid, pq, cost, size, i, j, p, q);  }
            /*if((grid[i-1][j])->dist > cost[i-1][j] + (grid[i][j])->dist && !(grid[i-1][j])->visited){
                (grid[i-1][j])->dist = cost[i-1][j] + (grid[i][j])->dist;
                (grid[i-1][j])->pred = grid[i][j];
            }
            heapify(pq, size);
        }*/
        if(j < n - 1){ p = i; q = j+1; explore(grid, pq, cost, size, i, j, p, q);  }
            /*if((grid[i][j+1])->dist > cost[i][j+1] + (grid[i][j])->dist && !(grid[i][j+1])->visited){
                (grid[i][j+1])->dist = cost[i][j+1] + (grid[i][j])->dist;
                (grid[i][j+1])->pred = grid[i][j];
            }
            heapify(pq, size);
        }*/
        if(j > 0){ p = i; q = j - 1; explore(grid, pq, cost, size, i, j, p, q);  }
            /*if((grid[i][j-1])->dist > cost[i][j-1] + (grid[i][j])->dist && !(grid[i][j-1])->visited){
                (grid[i][j-1])->dist = cost[i][j-1] + (grid[i][j])->dist;
                (grid[i][j-1])->pred = grid[i][j];
            }
            heapify(pq, size);
        }*/
        //(grid[i][j])->visited = true;
        if(j == m - 1){
            printf("reached bottom\n");
        }
    }
}
void explore(Node*** grid, Node **pq, short** cost, int size, int i, int j, int p, int q){
    if((grid[p][q])->dist > cost[p][q] + (grid[i][j])->dist && !(grid[p][q])->visited){
        (grid[p][q])->dist = cost[p][q] + (grid[i][j])->dist;
        (grid[p][q])->pred = grid[i][j];
    }
    heapify(pq, size);
    (grid[i][j])->visited = true;
}
void status(Node ***grid, int x, int y, int n, int m){
    if(x < n - 1){
            printf("Right:\n");
            printf("dist: %d pred: (%d, %d)\n", (grid[x+1][y])->dist, (grid[x+1][y])->pred->i, (grid[x+1][y])->pred->j);
        }
        if(x > 0){
            printf("Left:\n");
            printf("dist: %d pred: (%d, %d)\n", (grid[x-1][y])->dist, (grid[x-1][y])->pred->i, (grid[x-1][y])->pred->j);
        }
        if(y < m - 1){
            printf("Top:\n");
            printf("dist: %d pred: (%d, %d)\n", (grid[x][y+1])->dist, (grid[x][y+1])->pred->i, (grid[x][y+1])->pred->j);
        }
        if(y > 0){
            printf("Bottom:\n");
            printf("dist: %d pred: (%d, %d)\n", (grid[x][y-1])->dist, (grid[x][y-1])->pred->i, (grid[x][y-1])->pred->j);
        }
}
int min(int a, int b){
    return (a > b) ? b : a;
}
bool find(Node* arr[], Node* n, int size){
    for(int i = 0; i < size; i++){
        if(n == arr[i]){
            return true;
        }
    }
    return false;
}

void heapify(Node* pq[], int size){
    for(int k = (size/2) - 1; k >= 0; k--){
        heapify_node(pq, k, size);
    }
}
void heapify_node(Node* arr[], int i, int n){
    //printf("heapify\n");
    //for(i = 0; i < n; i++){
        //printf("cost: %d i: %d j: %d\n", (arr[0])->dist, (arr[0])->i, (arr[0])->j);
    //}
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
            //printf("cost: %d i: %d j: %d\n", (arr[0])->dist, (arr[0])->i, (arr[0])->j);
            heapify_node(arr, n, min);
        }
    }
}
Node* extract_min(Node* arr[], int *n){
    //printf("extract min\n");
    Node* min = arr[0];
    swap_node(&arr[0], &arr[*n - 1]);
    *n -= 1;
    for(int i = (*n/2) - 1; i >= 0; i--){
        heapify_node(arr, i, *n);
    }
    //printf("cost: %d i: %d j: %d\n", (arr[0])->dist, (arr[0])->i, (arr[0])->j);
    return min;
}
void delete_root(Node* arr[], int *n){
    swap_node(&arr[0], &arr[*n - 1]);
    *n -= 1;
    for(int i = (*n/2) - 1; i >= 0; i--){
        heapify_node(arr, i, *n);
    }
}
/*void insert(short* arr[], short* num, int *n){
    if(*n == 0){
        arr[0] = num;
        *n += 1;
    }else{
        arr[*n] = num;
        *n += 1;
        for(int i = (*n/2) - 1; i >= 0; i--){
            heapify(arr, i, *n);
        }
    }
}*/
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
void swap(short **a, short **b){
    //printf("time to swap\n");
    short* temp = *b;
    *b = *a;
    *a = temp;
}
void swap_node(Node **a, Node **b){
    //printf("time to swap\n");
    Node *temp = *b;
    *b = *a;
    *a = temp;
}
