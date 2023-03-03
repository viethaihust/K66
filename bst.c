#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

node* newNode(char date[], char time[], char license[])
{
  node *temp = (node*)calloc(10, sizeof(node));
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
  if (root == NULL) return -1;
  if (strcmp(root->license, license) == 0) return 1;
  if (strcmp(root->license, license) > 0) return da_co_xe(root->left, license);
  return da_co_xe(root->right, license);
}

void gui_xe(node** node, char license[], char date[], char time[])
{
  if (*node == NULL)
    *node = newNode(date, time, license);
  insert(&(*node), license, date, time);
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
  if ((*root) != NULL)
  {
    if (strcmp(license, (*root)->license) < 0) {
      deleteNode(&(*root)->left, license);   
    }
    else if (strcmp(license, (*root)->license) > 0) {
      deleteNode(&(*root)->right, license);
    }
    else if (strcmp(license, (*root)->license) == 0) {
      if ((*root)->left == NULL && (*root)->right == NULL) {
        (*root) = NULL;
      }
      else if ((*root)->left == NULL) {
        (*root) = (*root)->right;
      }
      else if ((*root)->right == NULL) {
        (*root) = (*root)->left;
      }
      else {
        strcpy((*root)->license, minValueNode((*root)->right)->license);
        deleteNode(&(*root)->right, minValueNode((*root)->right)->license);
      }
    }
  }
}

void freeTree(node** tree) {
  if (*tree != NULL) {
    freeTree(&(*tree)->left);
    freeTree(&(*tree)->right);
    free(*tree);
    *tree = NULL;
  }
}