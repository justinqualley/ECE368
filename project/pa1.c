#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include <getopt.h>
#include "list_of_list.h"
#include "shell_array.h"
#include "shell_list.h"


/*static void printList(Node* h)
{
  if (h == NULL)
    {
      return;
    }
  printf("-------------------------\n");
  Node * p;
  printf("from head: \n");
  while (h != NULL)
    {
      p = h -> next;
      printf("%ld\n", h -> value);
      h = p;
    }
}*/

static void deleteList(Node** h)
{
   Node* scan = *h;
   Node* next;
   while (scan != NULL)
   {
       next = scan->next;
       free(scan);
       scan = next;
   }
   *h = NULL;
}
int main(int argc, char * * argv){
    if(argc != 4){
        return EXIT_FAILURE;
    }
    int c;
    int aflag = 0;
    int lflag = 0;
    while((c = getopt(argc, argv, "al:")) != -1){
        switch (c){
            case 'a':
                aflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
      default:
        return EXIT_FAILURE;
      }
    }
    int size;
    long n_comp = 0;
    long *arr = NULL;
    int written;
    if(aflag == 1){
        arr = Array_Load_From_File(argv[2], &size);
        if(arr == NULL){
          free(arr);
          return EXIT_FAILURE;
        }
        Array_Shellsort(arr, size, &n_comp);
        written = Array_Save_To_File(argv[3], arr, size);
        if(written != size){
          fprintf(stderr, "Only wrote %d numbers but expected to write %d numbers\n", written, size);
        }
        fprintf(stdout, "%ld\n", n_comp);
        free(arr);
    }else if(lflag == 1){
        Node* h = List_Load_From_File(argv[2]);
        if(h == NULL){
          free(arr);
          return EXIT_FAILURE;
        }
        Node *scan = h; 
        size = 0;
        while (scan != NULL) 
        { 
          ++size; 
          scan = scan->next; 
        }
        h = List_Shellsort(h, &n_comp);
        written = List_Save_To_File(argv[3], h);
        if(written != size){
          fprintf(stderr, "Only wrote %d numbers but expected to write %d numbers\n", written, size);
        }
        fprintf(stdout, "%ld\n", n_comp);
        deleteList(&h);
    }
    
    return EXIT_SUCCESS;
}


