#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "shell_list.h"

#ifdef TEST_READLIST
Node *List_Load_From_File(char *filename){

}
#endif

#ifdef TEST_SAVELIST
int List_Save_To_File(char *filename, Node *list){

}
#endif

#ifdef TEST_SORTLIST
Node *List_Shellsort(Node *list, long *n_comp){
    
}
#endif
