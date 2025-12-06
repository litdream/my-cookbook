#ifndef RAY_BST_H
#define RAY_BST_H

#include <stdbool.h>

#define MAX_BST_SIZE   1000

struct node {
	int data;
	struct node *left;
	struct node *right;
};
typedef struct node BSTNode;

BSTNode* bst_insert(BSTNode *root, int data);
bool  bst_exists(BSTNode *root, int data);

int bst_minimum(BSTNode *root);
int bst_maximum(BSTNode *root);

int bst_height(BSTNode *root);
// int bst_size(BSTNode *root);


#endif   // RAY_BST_H
