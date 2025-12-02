#ifndef RAY_LINKEDLIST_H
#define RAY_LINKEDLIST_H


#include <stdio.h>

struct list_node {
	int data;
	struct list_node *next;
};
typedef struct list_node ListNode;


// Return *head,
//  - Mostly the same as head,
//  - if head changes, new head will return.
ListNode* push(ListNode *head, int data);
ListNode* unlink(ListNode *head, ListNode *node);
ListNode* delete(ListNode *head, ListNode *delnode);
ListNode* sort(ListNode *head);

// Return searched node.
ListNode* search(ListNode *head, int niddle);
ListNode* min(ListNode *head);
ListNode* max(ListNode *head);

// void function
void print_list(ListNode *head);


#endif // RAY_LINKEDLIST_H
