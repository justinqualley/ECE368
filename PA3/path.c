#include "path.h"

void shortest(short** grid, int m, int n, int start){
    int size = 0;
    int i;
    //Node *newNode;
    short **pq;
    pq = malloc(m*n * sizeof *pq);
    for(i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            insert(pq, &grid[i][j], &size);  //Put each vertex in the PQ
        }
    }
    printf("Priority Queue: \n");
    for(int k = 0; k < size; k++){
        printf("%d ", *(pq[k]));               //Print out PQ
    }
    printf("\n");
    short *d = malloc(n * sizeof *d);       //Init shortest distance to each vertex at top
    for(i = 0; i < n; i++){
        d[i] = SHRT_MAX;                    //Set that distance to be infinty
    }
    //int adjX[] = {0,0,1,-1};
    //int adjY[] = {-1,1,0,0};
    /*while(size > 0){
        short* u = extract_min(pq, &size);
        for(int i=0; i<4; i++){
            int neighRow = row + adjY[i];
            int neighCol = col + adjX[i];
            if(min(neighRow, neighCol) >= 0 && neighRow < matrix.length && neighCol < matrix[0].length){
            //process node
            }
        }
    }*/
}
bool checkBounds(int i, int j, int m, int n){
    bool out = true;
    if(i < 0){ //We are at top edge
        out = false;
    }
    if(i > m){ //We are at the bottom edge
        out = false;
    }
    if(j < 0){ //We are at the left edge
        out = false;
    }
    if(j > n){ //We are at the right edge
        out = false;
    }
    return out;
}
void heapify(short* arr[], int i, int n){
    if (n == 1){
        return;
    }else{
        int min = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l] < arr[min]){
            min = l;
        }
        if (r < n && arr[r] < arr[min]){
            min = r;
        }
        if (min != i){
            swap(&arr[i], &arr[min]);
            heapify(arr, n, min);
        }
    }
}
short* extract_min(short* arr[], int *n){
    short* min = arr[0];
    delete_root(arr, n);
    return min;
}
void delete_root(short* arr[], int *n){
    swap(&arr[0], &arr[*n - 1]);
    *n -= 1;
    for(int i = (*n/2) - 1; i >= 0; i--){
        heapify(arr, i, *n);
    }
}
void insert(short* arr[], short* num, int *n){
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
}
void swap(short **a, short **b){
    short* temp = *b;
    *b = *a;
    *a = temp;
}
