#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "shell_list.h"

static int h(int i){
    if(i == 1){
        return 1;
    }else{
        int out = 3 * h(i-1) + 1;
        return out;
    }
}
static void append(Node **h, long val){
    Node *n = malloc(sizeof(Node));
    if(n == NULL){
        fprintf(stderr, "Malloc failed");
        return;
    }
    n->value = val;
    n->next = NULL;
    if(*h == NULL){
        *h = n;
    }else{
        Node *temp = *h;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = n;
    }
}
#ifdef TEST_READLIST
Node *List_Load_From_File(char *filename){
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL){                       //What should I return?
        return NULL;
    }
    Node *h = malloc(sizeof(Node));         //Head of list
    if(h == NULL){
        return NULL;
    }
    long value;                             //add if else malloc fails
    fread(&value, sizeof(long), 1, fptr);   //Read and store first value
    h->value = value;
    h->next = NULL;
    while(fread(&value, sizeof(long), 1, fptr) > 0){ //while still values to read
        append(&h, value);                            //add to end of list
    }
    fclose(fptr);
    return h;
}
#endif

#ifdef TEST_SAVELIST
int List_Save_To_File(char *filename, Node *list){
    FILE * fptr = fopen(filename, "wb");
    if(fptr == NULL || list == NULL){
        return 0;
    }
    long value = list->value;
    int written = 0;
    while(list != NULL){
        value = list->value;
        if(fwrite(&value, sizeof(long), 1, fptr) > 0){
            written++;
        }
        list = list->next;
    }
    fclose(fptr);
    return written;
}
#endif
static void swap(Node **i, Node **j)
{
    Node *tmp = *i;
    *i = *j;
    *j = tmp;
}

#ifdef TEST_SORTLIST
Node *List_Shellsort(Node *list, long *n_comp){
    *n_comp = 0;
    if(list == NULL){
        return NULL;
    }
    long x = 0;                                               //Made all variables long for very large test cases
    long val1, val2;
    int k, size = 0;
    Node *scan = list; 
    while (scan != NULL) 
    { 
        ++size; 
        scan = scan->next; 
    }
    for(x = 1; h(x) < size; x++){}                            //Find x such that h(x) <= size
    for(long t = 1; t < x; t++){                              //Pass x - 1
        long kMax = h(x - t);                                    //Recusive call to generate k
        Node **i = &list;
        Node **j = &list;
        k = kMax;
        while((*j)->next != NULL && k-- > 0){ //
            j = &(*j)->next;
        }
        while(*j != NULL){                                    
            val1 = (*i)->value;
            val2 = (*j)->value;
            if(val1 > val2){
                *n_comp = *n_comp + 1;
                if(*i == list){
                    *i = list;
                }
                swap(i ,j);
                swap(&(*i)->next, &(*j)->next);
                //need to go back now and check rest of sublist
            }
            i = &(*i)->next;
            j = &(*j)->next;
        }
    }
    return list;
}
#endif
