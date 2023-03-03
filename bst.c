#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

const char dataOutputFilename[] = "change_log.txt";

node* newNode(char date[], char time[], char license[])
{
  node* temp = (node*)malloc(sizeof(node));
  strcpy(temp->date, date);
  strcpy(temp->time, time);
  strcpy(temp->license, license);
  temp->left = temp->right = NULL;
  return temp;
}

void inorder(node* root)
{
  if (root != NULL) {
    inorder(root->left);
    printf("%s \t %s %s\n", root->license, root->date, root->time);
    inorder(root->right);
  }
}

int count_tree(node *root){
  if(root == NULL){
    return 0;
  }
  else{
    return 1 + count_tree(root->left) + count_tree(root->right);
  }
}

void insert(node** node, char license[], char date[], char time[])
{
  if (*node == NULL)
  {
    *node = newNode(date, time, license);
  }
  else if (strcmp(license, (*node)->license) < 0)
  {
    insert(&(*node)->left, license, date, time);
  }
  else if (strcmp(license, (*node)->license) > 0)
    insert(&(*node)->right, license, date, time);
}

int da_co_xe(node* root, char license[])
{
  if (root != NULL) {
    da_co_xe(root->left, license);
    if (strcmp(root->license, license) == 0){
      return 1;
    }    
    da_co_xe(root->right, license);
  }
}

void gui_xe(node** node, char license[], char date[], char time[])
{
  FILE *f = fopen(dataOutputFilename, "a");
  if (da_co_xe((*node), license) == 1) {
    printf("%s : Loi bien so da ton tai\n", license);
  }
  else{
    if (*node == NULL)
      *node = newNode(date, time, license);
    insert(&(*node), license, date, time);
    printf("%s : Gui xe thanh cong %s %s\n", license, date, time);
    fprintf(f, "%s %s %s %d\n", date, time, license, 1);
  }
}

node* minValueNode(node* node)
{
  struct node* current = node;

  while (current && current->left != NULL)
      current = current->left;

  return current;
}

void deleteNode(node** root, char license[])
{
  node *temp = *root;
  printf("%s\n", (*root)->license);
  if (temp != NULL)
    if (strcmp(license, temp->license) < 0)
      deleteNode(&temp->left, license);
    else if (strcmp(license, temp->license) > 0)
      deleteNode(&temp->right, license);

    else {
        if (temp->left == NULL && temp->right == NULL) {
          printf("ok1\n");
          free(temp);
          inorder(*root);
        }
        else if (temp->left == NULL) {
          printf("ok2");
          temp = temp->right;
        }
        else if (temp->right == NULL) {
          printf("ok3");
          temp = temp->left;
        }
        else{
          printf("ok4");
          strcpy(temp->license, minValueNode(temp->right)->license);
        }
    }
}

void freeTree(node** tree) {
  if (*tree != NULL) {
    freeTree(&(*tree)->left);
    freeTree(&(*tree)->right);
    free(*tree);
  }
}