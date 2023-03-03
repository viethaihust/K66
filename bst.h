#ifndef __BST_H__
#define __BST_H__

typedef struct node {
  char date[11];
  char time[9];
  char license[13];
  struct node *left, *right;
} node;

void insert(node** node, char license[], char date[], char time[]);
void gui_xe(node** node, char license[], char date[], char time[]);
void inorder(node* root);
int count_tree(node *root);
int da_co_xe(node* root, char license[]);
node* minValueNode(node* node);
void deleteNode(node** root, char license[]);
void freeTree(node** tree);
void luu_ra_file(node* root, char filename[]);

#endif