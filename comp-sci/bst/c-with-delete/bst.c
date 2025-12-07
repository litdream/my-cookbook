#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static BSTNode*
node_create(int data) {
	BSTNode* rtn = (BSTNode*)malloc(sizeof(BSTNode));
	if (!rtn) {
		perror("Memory alloc error.\n");
		exit(1);
	}
	rtn->data = data;
	rtn->left = NULL;
	rtn->right = NULL;
	return rtn;
}


// parameter:
//   - root:  tree to insert
//   - data:  data to insert.  Must be Unique.
//            If data already exists, NULL will be returned.
// return:
//   - new root pointer:  for successful insert.
//   - NULL:  if data is already inserted before.
//
BSTNode*
bst_insert(BSTNode *root, int data) {
	if ( root == NULL ) 
		return node_create(data);

	BSTNode *cur = root;
	BSTNode *par = NULL;
	while ( cur != NULL ) {
		par = cur;		
		if (data < cur->data) {
			cur = cur->left;
		} else if (data > cur->data) {
			cur = cur->right;
		} else {
			// Should not happen.
			// PRE: data must be unique.
			return NULL;
		}
	}

	if ( data < par->data )
		par->left = node_create(data);
	else
		par->right = node_create(data);
	return root;
}


static BSTNode*
search(BSTNode *root, int data) {
	if (root == NULL) 
		return NULL;

	if (data == root->data) {
		// FOUND!
		return root;
	} else if ( data < root->data) {
		return search(root->left, data);
	} else {
		return search(root->right, data);
	}
}
bool
bst_exists(BSTNode *root, int data) {
	return search(root, data) != NULL;
}


// Find minimum value of the sub-tree
// PRE:  root is not NULL.  Minimum can't be determined in empty tree.
//
int
bst_minimum(BSTNode *root) {
	BSTNode *cur = root;
	while ( cur->left != NULL ) 
		cur = cur->left;
	return cur->data;
}

// Find maximum value of the sub-tree
// PRE:  root is not NULL.  Minimum can't be determined in empty tree.
//
int
bst_maximum(BSTNode *root) {
	BSTNode *cur = root;
	while ( cur->right != NULL ) 
		cur = cur->right;
	return cur->data;
}

int bst_height(BSTNode *root) {
	if (root == NULL)
		return -1;

	int left_height = bst_height(root->left);
	int right_height = bst_height(root->right);
	return (left_height > right_height) ? 1 + left_height : 1 + right_height;
}

// Helper function to find the node with minimum value in a tree
// Used for finding in-order successor
static BSTNode*
find_min_node(BSTNode *root) {
	BSTNode *cur = root;
	while (cur->left != NULL)
		cur = cur->left;
	return cur;
}

// Delete a node with given data from the BST
// parameter:
//   - root:  tree to delete from
//   - data:  data to delete
// return:
//   - new root pointer after deletion
//     - recursively calling down subtree.
//
BSTNode*
bst_delete(BSTNode *root, int data) {
	if (root == NULL)
		return NULL;

	// Search down the subtree
	if (data < root->data) {
		root->left = bst_delete(root->left, data);
	} else if (data > root->data) {
		root->right = bst_delete(root->right, data);
	} else {
		// Found the node to delete

		// Case 1: Leaf Node
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL;
		}

		// Case 2: Having only right child
		if (root->left == NULL) {
			BSTNode *temp = root->right;
			free(root);
			return temp;
		}

		// Case 3: Having only left child
		if (root->right == NULL) {
			BSTNode *temp = root->left;
			free(root);
			return temp;
		}

		// Case 4: 2 Children:  
		//   Swap with successor, and delete the successor 
		//   in the subtree.
		BSTNode *successor = find_min_node(root->right);
		root->data = successor->data;
		root->right = bst_delete(root->right, successor->data);
	}

	return root;
}

