#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
  int value;
  struct Node * next;
  struct Node * prev;
} ListNode;

typedef struct
{
  ListNode * head;
  ListNode * tail;
} List;

void printList(List * intlist)
{
  if (intlist == NULL)
    {
      return;
    }
  printf("-------------------------\n");
  ListNode * ln = intlist -> head;
  ListNode * p;
  printf("from head: \n");
  while (ln != NULL)
    {
      p = ln -> next;
      printf("%d\n", ln -> value);
      ln = p;
    }
  printf("from tail: \n");
  ln = intlist -> tail;
  while (ln != NULL)
    {
      p = ln -> prev;
      printf("%d\n", ln -> value);
      ln = p;
    }
}

void addNode(List * intlist, int value)
{
  if (intlist == NULL)
    {
      return;
    }
  ListNode * n = malloc(sizeof(ListNode));
  n -> value = value;
  n -> next = NULL;
  n -> prev = NULL;
  if ((intlist -> head) == NULL)
    {
      // first node inserted into the list
      intlist -> head = n;
      intlist -> tail = n;
      return; // <---- LOCATION A
    }
  // not first node inserted into the list
  n -> prev = intlist -> tail;
  (intlist -> tail) -> next = n;
  intlist -> tail = n;
}

bool deleteNode(List * intlist, int value)
// delete the node whose value matches
// if no node has this value, the list is unchanged
// if multiple nodes stores this value, delete the first node
{
  if (intlist == NULL)
    {
      return false;
    }
  if ((intlist -> head) == NULL)
    {
      return false;
    }
  ListNode * p = intlist -> head;
  
  // is ln in the list?
  while ((p != NULL) && ((p -> value) != value))
    {
      p = p -> next;
    }

  if (p == NULL) // ln not in the list
    {
      return false; // cannot delete
    }

  if (p == (intlist -> head))
    {
      // delete the first node
      ListNode * n = (intlist -> head) -> next;
      if (n != NULL)
	{
	  // the first node is not the only node
	  n -> prev = NULL;
	}
      free (intlist -> head);
      intlist -> head = n;
      if ((intlist -> head) == NULL)
	{
	  // empty list
	  intlist -> tail = NULL;
	}
      return true; // <--- LOCATION B
    }

  if (p == (intlist -> tail))
    {
      // delete the last node
      ListNode * n = (intlist -> tail) -> prev;
      if (n != NULL)
	{
	  // the last node is not the only node
	  n -> next = NULL;
	}
      free (intlist -> tail);
      intlist ->  tail = n;
      if ((intlist -> tail) == NULL)
	{
	  // empty list
	  intlist -> head = NULL;
	}
      return true; // <--- LOCATION C
    }

  // neither head nor tail

  (p -> next) -> prev = p -> prev;
  (p -> prev) -> next = p -> next;
  free (p); 
  return true;
}

void deleteList(List * intlist)
// delete the entire list, free all memory
{
  if (intlist == NULL)
    {
      // nothing to do
      return; 
    }
  ListNode * h = intlist -> head;
  ListNode * p; 
  while (h != NULL)
    {
      p = h -> next;
      free (h);
      h = p;
    }
  free (intlist);
}

int main (int argc, char ** argv)
{
  List * intlist;
  intlist = malloc(sizeof(List));
  intlist -> head = NULL;
  intlist -> tail = NULL; // <--- LOCATION D
  int counter;
  for (counter = 0; counter < 10; counter ++)
    {
      printf("\n\nadd %d\n", counter);
      addNode(intlist, counter);
      printList(intlist);
    }
  int arr[] = {5, 4, 3, 1, 0, 5, 7, 8, 14, -2};
  for (counter = 0; counter < 10; counter ++)
    {
      int value = arr[counter];
      printf("\n\ndelete %d\n", value);
      deleteNode(intlist, value);
      printList(intlist);
    }
  deleteList(intlist);
  return EXIT_SUCCESS;
}
