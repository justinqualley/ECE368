#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "list_of_list.h"
#include "shell_array.h"
#include "shell_list.h"
int main(int argc, char * * argv){
    if(argc != 3){
        return EXIT_FAILURE;
    }
    int size;
    long n_comp = 0;
    long *arr;
    int written;
    arr = Array_Load_From_File(argv[1], &size);
    Array_Shellsort(arr, size, &n_comp);
    written = Array_Save_To_File(argv[2], arr, size);
    return EXIT_SUCCESS;
}


