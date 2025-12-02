#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

ListNode*
push (ListNode *head, int data) {
	ListNode *rtn = malloc(sizeof(ListNode));
	if (rtn == NULL) {
		perror("Node Alloc Failed");
		return NULL;
	}
	memset(rtn, '\0', sizeof(ListNode));
	rtn->data = data;
	
	if (head == NULL) {
		return rtn;
	}

	ListNode *cur = head;
	while (cur->next != NULL) 
		cur = cur->next;
	cur->next = rtn;
	return head;
}

// PRE: ul_node must exist in the list.
//    - search(head, ul_node) MUST NOT return NULL
//    - unlink() returns NULL, only when the last node is ul_node;
//    - Otherwise, returns non-NULL of new head.
ListNode*
unlink(ListNode *head, ListNode *ul_node) {
	ListNode *rtn;
	if (head == ul_node) {
		rtn = ul_node->next;
		return rtn;
	}
	
	ListNode *cur = head;
	while (cur->next != ul_node) 
		cur = cur->next;
	cur->next = ul_node->next;
	return head;
}

// PRE: delnode must exist in the list.
//    - search(head, delnode) MUST NOT return NULL
ListNode*
delete(ListNode *head, ListNode *delnode) {
	ListNode *rtn;
	ListNode *new_head = unlink(head, delnode);
	free(delnode);
	return new_head;
}

ListNode*
search(ListNode *head, int niddle) {
	ListNode *srch=head;
	while (srch->data != niddle) {
		srch = srch->next;
		if (srch == NULL)
			break;
	}
	return srch;
}

ListNode*
min(ListNode *head) {
	ListNode *cur = head;
	ListNode *min_node = cur;
	while (cur != NULL) {
		if (cur->data < min_node->data)
			min_node = cur;
		cur = cur->next;
	}
	return min_node;
}

ListNode*
max(ListNode *head) {
	ListNode *cur = head;
	ListNode *max_node = cur;
	while (cur != NULL) {
		if (cur->data > max_node->data)
			max_node = cur;
		cur = cur->next;
	}
	return max_node;
}



ListNode*
sort(ListNode *head) {
	if (head == NULL || head->next == NULL) {
		return head;
	}
	
	ListNode *cur = head;
	while (cur->next != NULL) {
		ListNode *min_node = min(cur);
		
		// swap
		int temp = cur->data;
		cur->data = min_node->data;
		min_node->data = temp;
		
		cur = cur->next;
	}
	return head;
}
