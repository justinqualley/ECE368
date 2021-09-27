#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "list_of_list.h"
#include "shell_array.h"
#include "shell_list.h"
void printArray(long * arr, int size){
    for(int i = 0; i < size; i++){
        printf("%ld\n",arr[i]);
    }
    printf("Done\n");
}
int main(int argc, char * * argv){
    int size;
    long n_comp = 0;
    long *arr;
    int written;
    arr = Array_Load_From_File(argv[1], &size);
    Array_Shellsort(arr, size, &n_comp);
    written = Array_Save_To_File(argv[2], arr, size);
    printArray(arr, size);
}


