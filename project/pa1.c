#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include <getopt.h>
#include "list_of_list.h"
#include "shell_array.h"
#include "shell_list.h"


void printList(Node* h)
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
    long *arr;
    int written;
    if(aflag == 1){
        arr = Array_Load_From_File(argv[2], &size);
        Array_Shellsort(arr, size, &n_comp);
        written = Array_Save_To_File(argv[3], arr, size);
        size = written;
    }else if(lflag == 1){
        Node* h = List_Load_From_File(argv[2]);
        printList(h);
        //List_Shellsort(arr, &n_comp);
        //written = List_Save_To_File(argv[3], arr);
    }
    
    return EXIT_SUCCESS;
}


