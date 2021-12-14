#include<stdio.h>
#include<stdlib.h>
#include"file.h"
//#include"path.h"

/*
./pa3 binary graph file text graph file fastest times file fastest path file
*/
int main(int argc, char **argv){
    short m;                                                         //Number of rows
    short n;                                                         //Number of cols
    short **cost = read_graph(argv[1], &m, &n);                      //Store input binary as 2d cost matric
    //graph_to_txt(cost, argv[2], m, n);                               //Create text-viewable version of binary input
    int* times = malloc(n * sizeof times);                           //Fastest times for each exit option for each entry
    int i, j;                                                        //For indexing through array
    int size = 0;                                                    //Size of the PQ
    Node* vertices = malloc(n*m * sizeof(Node));                     //Stores the vertices of the shortest path
    Node* path = malloc(sizeof(Node));                               //Pointer to hold potential shortest path
    Node* prev = malloc(sizeof(Node));                               //Pointer to hold shortest path
    prev->dist = SHRT_MAX;                                          
    Node *vertex; 
    Node **pq;
    pq = malloc((m)*(n) * sizeof(Node*));                            //Array of pointers to nodes that functions as a priority queue
    Node ***graph = malloc(m * sizeof(Node**));                      //2D Array of pointers to nodes that function as our graph
    for(i = 0; i < m; i++){ graph[i] = malloc(n * sizeof(Node*)); }  //Allocate 2D array of pointers
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            vertex = malloc(sizeof(Node));
            vertex->dist = SHRT_MAX;                                 //Init distance to each node is infinity
            vertex->cost = cost[i][j];                               //Cost to travel to this node
            vertex->pred = NULL;
            vertex->i = i;                                           //It's position we will use as it's identifier
            vertex->j = j;
            vertex->visited = false;
            graph[i][j] = vertex;   
            insert_node(pq, vertex, &size);                          //Put each vertex in the PQ
        }                                                            //Now graph and pq point towards the same data. Easy updating!
    }
    Node* scan = NULL;                                                
    for(int k = 0; k < n; k++){
        *path = shortest(graph, pq, cost, size, m, n, 0, k);        //Returns the exit node with least distance for each entry
        times[k] = path->dist;                                      //Store this distance
        if(path->dist < prev->dist){                                //If our new shortest path is the shortest we've encountered
            *prev = *path;                                          //Exchange DATA not ADDRESSES
            scan = path;                                            
            i = 0;
            while(scan != NULL){
                vertices[i] = *(scan);                              //Store the path using linked-list
                scan = scan->pred;
                i++;
            }
            (vertices[i]).cost = -1;                                //Stop condition, required because the length of the path could be > rows
        }
    }
    //printf("Fastest Times:\n");
    fastest_times(times, argv[3], n);
    //for(i = 0; i < n; i++){
        //printf("%d ", times[i]);
    //}
    //printf("\n");
    //printf("Fastest Path:\n");
    fastest_path(vertices, argv[4]);
    //i = 0;
    //while((vertices[i]).cost >= 0){
        //printf("(%d, %d) ", (vertices[i]).i, (vertices[i]).j);
        //i++;
    //}
    //printf("cost: %d\n", vertices[0].dist);
    for (i = 0; i < m; i++){
        free(cost[i]);
    }
    free(cost); 
    free(times);
    free(vertices);
    free(path);
    free(prev);
    free(pq);
    for (i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            free((graph)[i][j]); 
        }
        free(graph[i]) ;    
    }
    free(graph);
}
