#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

void push(ll_node** head_ref, char date[], char time[], char license[], int status)
{
    ll_node* new_node = (ll_node*)malloc(sizeof(ll_node));
    strcpy(new_node->date, date);
    strcpy(new_node->time, time);
    strcpy(new_node->license, license);
    new_node->status = status;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void hienthi(ll_node *node)
{
  while (node != NULL)
  {
    printf("%s %s %s %d\n", node->date, node->time, node->license, node->status);
    node = node->next;
  }
}