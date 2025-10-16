#include "list.h"
#include <stdlib.h>

/**
 * Returns the head of the linked list.
 * 
 * @param head Pointer to the first node of the linked list.
 * @return The head of the linked list. If the list is empty (NULL), returns NULL.
 */
struct ll_node *ll_head(struct ll_node *head) {
    return head;
}

/**
 * Returns the tail (last node) of the linked list.
 * 
 * @param head Pointer to the first node of the linked list.
 * @return The tail of the linked list. If the list is empty (NULL), returns NULL.
 */
struct ll_node *ll_tail(struct ll_node *head) {
    if (head == NULL) {
        return NULL;
    }
    struct ll_node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    return current;
}

/**
 * Returns the number of nodes in the linked list.
 * 
 * @param head Pointer to the first node of the linked list.
 * @return The number of nodes in the list. If the list is empty (NULL), returns 0.
 */
int ll_size(struct ll_node *head) {
    if (head == NULL) {
        return 0;
    }
    int count = 0;
    struct ll_node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * TODO: Describe what the function does
 */
/**
 * Searches through the linked list for a node containing the specified value.
 * 
 * @param head  Pointer to the first node of the linked list
 * @param value The value to search for
 * @return      Pointer to the first node containing the value, or NULL if not found
 */
struct ll_node *ll_find(struct ll_node *head, int value) {
    if (head == NULL) {
        return NULL;
    }
    struct ll_node *current = head;
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

/**
 * Converts a linked list to an array.
 * Creates a new dynamically allocated array containing all values from the list.
 * 
 * @param head Pointer to the first node of the linked list
 * @return     Pointer to newly allocated array, or NULL if list is empty
 */
int *ll_toarray(struct ll_node *head) {
    // Handle empty list
    if (head == NULL) {
        return NULL;
    }
    
    // First, count the number of elements
    int size = ll_size(head);
    
    // Allocate memory for the array
    int *array = (int*)malloc(size * sizeof(int));
    if (array == NULL) {
        return NULL; // malloc failed
    }
    
    // Fill the array with values from the list
    struct ll_node *current = head;
    int index = 0;
    while (current != NULL) {
        array[index] = current->data;
        current = current->next;
        index++;
    }
    
    return array;
}

/**
 * Creates a new linked list node with the specified data.
 * 
 * @param data The data to store in the new node
 * @return     Pointer to the newly created node, or NULL if malloc fails
 */
struct ll_node *ll_create(int data) {
    // Allocate memory for a new node
    struct ll_node *new_node = (struct ll_node*)malloc(sizeof(struct ll_node));
    if (new_node == NULL) {
        return NULL; // malloc failed
    }
    
    // Initialize the node
    new_node->data = data;
    new_node->next = NULL;
    
    return new_node;
}

/**
 * Destroys an entire linked list by freeing all nodes.
 * 
 * @param head Pointer to the first node of the linked list to destroy
 */
void ll_destroy(struct ll_node *head) {
    // Handle empty list
    if (head == NULL) {
        return;
    }
    
    // Traverse the list and free each node
    struct ll_node *current = head;
    while (current != NULL) {
        struct ll_node *next = current->next;
        free(current);
        current = next;
    }
}

/**
 * Appends a new node with the specified data to the end of the linked list.
 * 
 * @param head Pointer to the first node of the linked list
 * @param data The data to store in the new node
 */
void ll_append(struct ll_node *head, int data) {
    // Handle empty list - this shouldn't happen based on test cases
    if (head == NULL) {
        return;
    }
    
    // Create a new node
    struct ll_node *new_node = ll_create(data);
    if (new_node == NULL) {
        return; // malloc failed
    }
    
    // Find the last node in the list
    struct ll_node *tail = ll_tail(head);
    
    // Append the new node to the tail
    tail->next = new_node;
}

/**
 * Creates a linked list from an array of integers.
 * 
 * @param data Pointer to the array of integers
 * @param len  Length of the array
 * @return     Pointer to the head of the newly created linked list, or NULL if empty array
 */
struct ll_node *ll_fromarray(int* data, int len) {
    // Handle empty array
    if (data == NULL || len <= 0) {
        return NULL;
    }
    
    // Create the first node
    struct ll_node *head = ll_create(data[0]);
    if (head == NULL) {
        return NULL; // malloc failed
    }
    
    // If there's only one element, return the head
    if (len == 1) {
        return head;
    }
    
    // Keep track of the tail for efficient appending
    struct ll_node *tail = head;
    
    // Add the remaining elements
    for (int i = 1; i < len; i++) {
        struct ll_node *new_node = ll_create(data[i]);
        if (new_node == NULL) {
            // Clean up on failure
            ll_destroy(head);
            return NULL;
        }
        
        tail->next = new_node;
        tail = new_node;
    }
    
    return head;
}

/**
 * Removes the first node containing the specified value from the linked list.
 * 
 * @param head  Pointer to the first node of the linked list
 * @param value The value to remove from the list
 * @return      Pointer to the (possibly new) head of the list
 */
struct ll_node *ll_remove(struct ll_node *head, int value) {
    // Handle empty list
    if (head == NULL) {
        return NULL;
    }
    
    // Special case: removing the head node
    if (head->data == value) {
        struct ll_node *new_head = head->next;
        free(head);
        return new_head;
    }
    
    // Search for the node to remove
    struct ll_node *current = head;
    while (current->next != NULL) {
        if (current->next->data == value) {
            // Found the node to remove
            struct ll_node *node_to_remove = current->next;
            current->next = node_to_remove->next;
            free(node_to_remove);
            return head; // Head didn't change
        }
        current = current->next;
    }
    
    // Value not found, return original head
    return head;
}

