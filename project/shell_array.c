#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "shell_array.h"

static int h(int i){
    if(i == 1){
        return 1;
    }else{
        int out = 3 * h(i-1) + 1;
        return out;
    }
}
/*static void printArray(long * arr, int size){
    for(int i = 0; i < size; i++){
        printf("%ld\n",arr[i]);
    }
    printf("Done\n");
}*/

#ifdef TEST_READARRAY
long* Array_Load_From_File(char *filename, int *size){
    long *arr = NULL;
   
    FILE * fptr = fopen(filename, "rb"); // open a file whose name is filename for reading
    if(fptr == NULL) {                   // if fopen fails, return false. Do NOT fclose
      *size = 0;
      return arr;
    }
    fseek(fptr, 0, SEEK_END);
    *size = ftell(fptr) / sizeof(long);      //Number of items in array
    arr = malloc(*size*sizeof(long));  
    fseek(fptr, 0, SEEK_SET);               //Set back to top for reading
    fread(arr, sizeof(long), *size, fptr);
    fclose(fptr);
    return arr;
}
#endif
#ifdef TEST_SAVEARRAY
int Array_Save_To_File(char *filename, long *array, int size){
    FILE * fptr = fopen(filename, "wb");
    if(fptr == NULL){
        return 0;
    }
    int written = fwrite(array, sizeof(long), size, fptr);
    fclose(fptr);
    free(array);
    return written;
}
#endif
#ifdef TEST_SORTARRAY
void Array_Shellsort(long *array, int size, long *n_comp){
    long x = 0;                                               //Made all variables long for very large test cases
    for(x = 1; h(x) < size; x++){}                            //Find x such that h(x) <= size
    for(long s = 1; s < x; s++){                              //Pass x - 1
        long k = h(x - s);                                    //Recusive call to generate k
        for(long j = k; j <= (size-1); j++){                  //Scan through array
            long temp_r = array[j];                           //Store in temp if swap neccessary
            long i = j;                                        
            while(i >= k && array[i-k] > temp_r){             //Insertion sort on smaller lists
                *n_comp = *n_comp + 1;
                array[i] = array[i-k];                        //Swap if the higher indexed is lesser
                i = i-k;
            } 
        array[i] = temp_r;                                    //Other half of the swap
        }
    }
}
#endif

