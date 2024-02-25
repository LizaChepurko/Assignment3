#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

// Node structure for a string list
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// StrList structure
struct _StrList {
    Node* head;
    size_t size;
};

// Function to create a new node with given data
Node* Node_alloc(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data); 
    newNode->next = NULL;
    return newNode;
}
void Node_free(Node* node) {
    free(node->data);
	free(node);
}

StrList* StrList_alloc() {
    StrList* newList = (StrList*)malloc(sizeof(StrList));
    if (newList != NULL) {
        newList->head = NULL;
        newList->size = 0;
    }
    return newList;
}

void StrList_free(StrList* StrList) {
    if (StrList == NULL){
        return;
    }
	Node* p1= StrList->head;
	Node* p2;
	while(p1) {
		p2= p1;
		p1= p1->next;
		Node_free(p2);
	}
	free(StrList);
}

size_t StrList_size(const StrList* StrList) {
    if (StrList == NULL)
        return 0;
    return StrList->size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if (StrList == NULL)
        return;

    Node* newNode = Node_alloc(data);
    if (newNode == NULL)
        return;

    if (StrList->head == NULL) {
        StrList->head = newNode;
    } else {
        Node* current = StrList->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    StrList->size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL || index < 0 || index > StrList->size){
        return;
    }
    if (index == StrList->size) {
        StrList_insertLast(StrList, data);
        return;
    }
    Node* newNode = Node_alloc(data);
    if (newNode == NULL){
        return;
    }
    if (index == 0) {
        newNode->next = StrList->head;
        StrList->head = newNode;
    } else {
        Node* current = StrList->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        
    }
    StrList->size++;
}

char* StrList_firstData(const StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL)
        return NULL;
    return StrList->head->data;
}

void StrList_print(const StrList* StrList) {
    if (StrList == NULL)
        return;

    Node* current = StrList->head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void StrList_printAt(const StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || index >= StrList->size)
        return;

    Node* current = StrList->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    printf("%s\n", current->data);
}

int StrList_printLen(const StrList* StrList) {
    if (StrList == NULL)
        return 0;

    int totalLen = 0;
    Node* current = StrList->head;
    while (current != NULL) {
        totalLen += strlen(current->data);
        current = current->next;
    }
    return totalLen;
}

int StrList_count(StrList* StrList, const char* data) {
    if (StrList == NULL)
        return 0;

    int count = 0;
    Node* current = StrList->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0)
            count++;
        current = current->next;
    }
    return count;
}

void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL)
        return;

    Node* current = StrList->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev == NULL) {
                StrList->head = current->next;
                free(current->data);
                free(current);
                current = StrList->head;
            } else {
                prev->next = current->next;
                free(current->data);
                free(current);
                current = prev->next;
            }
            StrList->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void StrList_removeAt(StrList* StrList, int index) {
    if (StrList == NULL || index < 0 || index >= StrList->size)
        return;

    Node* current = StrList->head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        StrList->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->data);
    free(current);
    StrList->size--;
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
    if (StrList1 == NULL || StrList2 == NULL)
        return 0;

    if (StrList1->size != StrList2->size)
        return 0;

    Node* current1 = StrList1->head;
    Node* current2 = StrList2->head;
    while (current1 != NULL) {
        if (strcmp(current1->data, current2->data) != 0)
            return 0;
        current1 = current1->next;
        current2 = current2->next;
    }
    return 1;
}

StrList* StrList_clone(const StrList* StrList1) {
    if (StrList1 == NULL){
        return NULL;
    }

	StrList* ret= StrList_alloc();
	const Node* old= StrList1->head;
	Node* * copy= &(ret->head);
	ret->size= StrList1->size;
	while(old) {
		*copy= Node_alloc(old->data);
		old= old->next;
		copy= &((*copy)->next);
	}
	return ret;
}

void StrList_reverse(StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL)
        return;

    Node* prev = NULL;
    Node* current = StrList->head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    StrList->head = prev;
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL)
        return;

    // Bubble sort implementation for simplicity
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    /* Checking for empty list */
    if (StrList->head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = StrList->head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) {
                char* temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL)
        return 1; // Considered sorted if empty or has only one element

    Node* current = StrList->head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0)
            return 0;
        current = current->next;
    }
    return 1;
}