#ifndef __LLIST_H__
#define __LLIST_H__

typedef struct ll_node {
  char date[11];
  char time[9];
  char license[13];
  int status;
  struct ll_node *next;
} ll_node;

void push(ll_node** head_ref, char date[], char time[], char license[], int status);
void hienthi(ll_node *node);

#endif