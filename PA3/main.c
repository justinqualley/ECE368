#include<stdio.h>
#include<stdlib.h>
#include"file.h"
#include"path.h"

/*
./pa3 binary grid file text grid file fastest times file fastest path file
*/
int main(int argc, char **argv){
    short m;
    short n;
    short **cost = read_grid(argv[1], &m, &n);
    //grid_to_txt(grid, argv[2], m, n);
    int* fastestPath = malloc(n * sizeof fastestPath);
    int i;
    int j;
    int size = 0;
    Node *vertex;                                                   //Structure to hold each data for each vertex of graph
    Node **pq = malloc(m*n * sizeof *pq);                           //Array of pointers to nodes that functions as a priority queue
    Node ***grid = malloc(m * sizeof(Node**));                      //2D Array of pointers to nodes that function as our graph
    for(i = 0; i < m; i++){ grid[i] = malloc(n * sizeof(Node*)); }  //Allocate 2D array of pointers
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            vertex = malloc(sizeof *vertex);
            grid[i][j] = vertex;
            insert_node(pq, vertex, &size);                     //Put each vertex in the PQ
        }
    }
    for(int k = 0; k < n; k++){
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                (grid[i][j])->dist = SHRT_MAX;                                //Init distance to each node is infinity
                (grid[i][j])->cost = cost[i][j];                              //Cost to travel to this node
                (grid[i][j])->pred = NULL;
                (grid[i][j])->i = i;                                          //It's position we will use as it's identifier
                (grid[i][j])->j = j;
                (grid[i][j])->visited = false;
            }
        }
        fastestPath[i] = shortest(grid, pq, cost, size, m, n, 0, k);
        printf("Fastest: %d\n", fastestPath[i]);
    }
    free(fastestPath);
}
