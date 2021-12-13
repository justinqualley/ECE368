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
    short **grid = read_grid(argv[1], &m, &n);
    //grid_to_txt(grid, argv[2], m, n);
    shortest(grid, m, n, 0);
}
