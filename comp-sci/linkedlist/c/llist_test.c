#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

// Helper to print test results
void test_result(const char* test_name, int success) {
    printf("%s: %s\n", test_name, success ? "PASSED" : "FAILED");
}

// Helper to compare arrays for the sort test
int compare_arrays(int* a, int* b, int size) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void list_to_array(ListNode* head, int* arr) {
    int i = 0;
    ListNode* current = head;
    while (current != NULL) {
        arr[i++] = current->data;
        current = current->next;
    }
}


int main() {
    ListNode* head = NULL;
    int success;

    // Test 1: Push and check size
    head = push(head, 10);
    head = push(head, 5);
    head = push(head, 30);
    head = push(head, 2);

    int count = 0;
    ListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    test_result("Push and Size", count == 4);

    // Test 2: Min and Max
    test_result("Min", min(head)->data == 2);
    test_result("Max", max(head)->data == 30);
    
    // Test 3: Sort
    head = sort(head);
    int sorted_arr[4];
    list_to_array(head, sorted_arr);
    int expected_arr[] = {2, 5, 10, 30};
    success = compare_arrays(sorted_arr, expected_arr, 4);
    test_result("Sort", success);
    
    // Test 4: Sort empty list
    ListNode* empty_head = NULL;
    empty_head = sort(empty_head);
    test_result("Sort Empty List", empty_head == NULL);

    // Test 5: Sort single element list
    ListNode* single_head = NULL;
    single_head = push(single_head, 1);
    single_head = sort(single_head);
    test_result("Sort Single Element List", single_head->data == 1 && single_head->next == NULL);


    // Free the list
    while (head != NULL) {
        ListNode* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
