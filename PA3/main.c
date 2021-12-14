#include<stdio.h>
#include<stdlib.h>
#include"file.h"
#include"path.h"

/*
./pa3 binary graph file text graph file fastest times file fastest path file
*/
int main(int argc, char **argv){
    short m;
    short n;
    short **cost = read_graph(argv[1], &m, &n);
    //graph_to_txt(graph, argv[2], m, n);
    int* times = malloc(n * sizeof times);
    //Node* fastest = malloc(m+n * sizeof times);
    //Node* tempPath = NULL;
    int i;
    int j;
    int size = 0;
    Node* vertices = malloc(n*m * sizeof(Node));
    Node* path = malloc(sizeof(Node));
    Node* prev = malloc(1* sizeof(Node));
    prev->dist = SHRT_MAX;
    //path = prev;
    Node *vertex;                                                   //Structure to hold each data for each vertex of graph
    Node **pq = malloc(m*n * sizeof *pq);                           //Array of pointers to nodes that functions as a priority queue
    Node ***graph = malloc(m * sizeof(Node**));                      //2D Array of pointers to nodes that function as our graph
    //Node path;
    for(i = 0; i < m; i++){ graph[i] = malloc(n * sizeof(Node*)); }  //Allocate 2D array of pointers
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            vertex = malloc(sizeof *vertex);
            graph[i][j] = vertex;
            insert_node(pq, vertex, &size);                     //Put each vertex in the PQ
        }
    }
    Node* scan = NULL;
    for(int k = 0; k < n; k++){
        *path = shortest(graph, pq, cost, size, m, n, 0, k); //path is the exit node with least distance for each entry
        times[k] = path->dist;
        printf("\n");
        if(path->dist < prev->dist){
            printf("changed\n");
            *prev = *path;
            scan = path;
            i = 0;
            while(scan != NULL){
                vertices[i] = *(scan);
                scan = scan->pred;
                i++;
            }
            (vertices[i]).cost = -1;
        }
    }
    printf("Fastest Times:\n");
    for(i = 0; i < n; i++){
        printf("%d ", times[i]);
    }
    printf("\n");
    printf("Fastest Path:\n");
    i = 0;
    while((vertices[i]).cost >= 0){
        printf("(%d, %d) ", (vertices[i]).i, (vertices[i]).j);
        i++;
    }
    printf("cost: %d\n", vertices[0].dist);
   /* Node* scan = NULL;
    printf("Fastest:\n");
    for(i = 0; i < n; i++){
        scan = &paths[i];
        printf("cost: %d", scan->dist);
        while(scan != NULL){
            printf("(%d, %d)", scan->i,scan->j);                                                    //Print out vertices of the path
            scan = scan->pred;
        }
        printf("\n");
    printf("Fastest: %d ", prev->dist);
    *scan = *prev;
    while(scan != NULL){
        printf("(%d, %d)", scan->i,scan->j);                                                    //Print out vertices of the path
        scan = scan->pred;
    }
    printf("\n");*/
    //free(times);
}
