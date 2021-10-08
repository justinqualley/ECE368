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
/*void pushTailList(Node *node, List **h){ //add to tail
    List *item = malloc(sizeof(List));
    if(item == NULL){
        return;
    }
    item->node = node;
    item->next = NULL;
    if(*h == NULL){
        *h = item;
    }else{
        List *scan = *h;
        while(scan->next != NULL){
            scan = scan->next;
        }
        scan->next = item;
    }
}
void pushLinked(Node **h, long value){ //add to head
    Node *item = malloc(sizeof(Node));
    if(item == NULL){
        return;
    }
    item->value = value;
    item->next = *h;
    *h = item;
}*/
static void swapNodes(Node** head_ref, int x, int y)
{
    // Nothing to do if x and y are same
    if (x == y)
        return;
 
    // Search for x (keep track of prevX and CurrX
    Node *prevX = NULL, *currX = *head_ref;
    while (currX && currX->value != x) {
        prevX = currX;
        currX = currX->next;
    }
 
    // Search for y (keep track of prevY and CurrY
    Node *prevY = NULL, *currY = *head_ref;
    while (currY && currY->value != y) {
        prevY = currY;
        currY = currY->next;
    }
 
    // If either x or y is not present, nothing to do
    if (currX == NULL || currY == NULL)
        return;
 
    // If x is not head of linked list
    if (prevX != NULL)
        prevX->next = currY;
    else // Else make y as new head
        *head_ref = currY;
 
    // If y is not head of linked list
    if (prevY != NULL)
        prevY->next = currX;
    else // Else make x as new head
        *head_ref = currX;
 
    // Swap next pointers
    Node* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
    //free?
}
#ifdef TEST_SORTLIST
Node *List_Shellsort(Node *list, long *n_comp){
    if(list == NULL){
        return NULL;
    }
    long x = 0;                                               //Made all variables long for very large test cases
    int val1, val2;
    int k, size = 0;
    Node *scan = list; 
    while (scan != NULL) 
    { 
        ++size; 
        scan = scan->next; 
    }
    for(x = 1; h(x) < size; x++){}                            //Find x such that h(x) <= size
    for(long s = 1; s < x; s++){                              //Pass x - 1
        long kMax = h(x - s);                                    //Recusive call to generate k
        Node *i = malloc(sizeof(Node));
        i = list;
        Node *j = malloc(sizeof(Node));
        j = list;
        k = kMax;
        while(k-- > 0){
            j = j->next;
        }
        for(; j != NULL; i = i->next, j = j->next){
            val1 = i->value;
            val2 = j->value;
            if(i->value > j->value){
                if(i == list){
                    list = j;
                }
                Node *temp = malloc(sizeof(Node));
                temp = i;
                i = j;
                j = temp; //Do I need this?
                
                swapNodes(&list, val1, val2);

            }
        }
    }
    return list;
}
#endif
