#include "linkedlist.h"
#include <string.h>
#include <stdio.h>


LinkedList *initialise(){
    LinkedList *list = malloc(sizeof(LinkedList));
    check_address(list);
    list->head = NULL;
    list->tail = NULL;

    return list;
}

int size(LinkedList *list){
    int size = 0;
    struct Node *current = list->head;
    while(current != NULL){
        size ++;
        current = current -> next;
    }
    return size;
}

bool empty(LinkedList *list){
    return size(list) == 0;    

}
int valueAt(LinkedList *list, int index) {
    struct Node *current = list->head;
    int current_index = 0;
    int value = 0;  // Initialize value

    while (current_index <= index && current != NULL) {
        if (current_index == index) {
            value = current->data;  
            break;
        }
        current = current->next;
        current_index++;
    }

    return value;
}
void pushFront(LinkedList *list, int value){
    struct Node *node = list->head;
    struct Node *prior = malloc(sizeof(struct Node));
    prior->data = value;    
    prior->next = node;
    list->head = prior;
    if (list->tail == 0){
        list->tail = prior;
    }
}
void popFront(LinkedList *list){
    if (list->head == NULL){
        printf("Cannot pop front of empty list");
        exit(EXIT_FAILURE);
    }
    struct Node *head = list->head;
    struct Node *next_node;
    next_node = head->next;
    list->head = next_node;

    if (list->tail == head){
        list->tail = list->head;
    }
    free(head);
}

void pushBack(LinkedList *list, int value){
    struct Node *node = malloc(sizeof(struct Node));
    node->data = value;
    node->next = NULL;
    if (list->tail == NULL){
        list->tail = list->head = node;
    } else{
    list->tail->next = node;
    list->tail = list->tail->next;
    };
}

void popBack(LinkedList* list) {
    if (list->tail == NULL) {
        printf("Cannot pop back from an empty list\n");
        exit(EXIT_FAILURE);
    }

    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
    } else {
        struct Node *current = list->head;
        struct Node *last = NULL;

        while (current->next != NULL) {
            last = current;
            current = current->next;
        }

        free(current);

        if (last != NULL) {
            last->next = NULL;
            list->tail = last;
        } else {
            list->head = list->tail = NULL;
        }
    }
}
int front(LinkedList *list){
    if (list->head == NULL){
        printf("empty list\n");
        exit(EXIT_FAILURE);
    }
    return list->head->data;
}

int back(LinkedList *list){
    if (list->head == NULL){
        printf("empty list\n");
        exit(EXIT_FAILURE);
    }
    return list->tail->data;
}

void destroy(LinkedList *list){
    struct Node *current = list -> head;
    struct Node *next;
    while (current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void insert(LinkedList *list, int value, int index){
    struct Node *current = list->head;
    struct Node *last = NULL;  // Initialize last to NULL

    int current_index = 0;
    while (index > current_index && current != NULL) {
        ++current_index;
        last = current;
        current = current->next;
    }

    if (current_index < index) {
        printf("Index out of bounds");
        exit(EXIT_FAILURE);
    }

    struct Node *node = malloc(sizeof(struct Node));
    check_address(node);

    node->data = value;
    node->next = NULL;  

    if (index == 0 && list->head == NULL){
        list->head = list->tail = node;  
    } else if (index == 0){
        node->next = list->head;
        list->head = node;
    } else if (current == NULL) { 
        last->next = node;
        list->tail = node; 
    } else {
        last->next = node;
        node->next = current;
    }
}

void erase(LinkedList *list, int index){
    struct Node *current = list->head;
    struct Node *prev = list->head;

    if (list->head == NULL){
        printf("Empty list");
        exit(EXIT_FAILURE);
    }
    int current_index = 0;
    while(index > current_index && current_index != 0){
        ++current_index;
        prev = current;
        current = current->next;
    }
    if (index == 0){
        list->head = current->next;
        if (list->tail == current){
            list->tail = list->head;
        }
    } else {
        prev->next = current->next;
        if (list->tail == current){
            list->tail = prev;
        }
    }
    free(current);
}
int value_n_from_end(LinkedList *list, int n){
    struct Node *node = list->head;
    struct Node *lagged = list->head;

    for (int i = 0; i < n; i++){
        if (node){
            node = node->next;
        } else{
            printf("List is not long enough");
            exit(EXIT_FAILURE);
        }
    }
    while(node){
        node = node->next;
        lagged = lagged->next;
    }
    return lagged->data;
}

void reverse(LinkedList *list){
    struct Node *current = list->head;
    struct Node *prev = NULL;
    struct Node *next;

    list->tail = list->head;
    
    while (current){
        next = current->next;
        current->next = prev;
        prev=current;
        current=next;
    }
    list->head = prev;
}

void remove_value(LinkedList *list, int value) {
    struct Node *current = list->head;
    struct Node *prev = NULL;

    while (current) {
        if (current->data == value) {
            if (prev) {
                prev->next = current->next;
                if (current == list->tail) {
                    list->tail = prev;
                }
                free(current);
                current = prev->next; 
            } else {
                list->head = current->next;
                if (current == list->tail) {
                    list->tail = NULL;
                }
                free(current);
                current = list->head;  
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}


void printList(LinkedList *list){
    struct Node *current = list->head;
    while (current){
        printf("%d ", current->data); 
        current = current->next;
    }
    printf("\n");  
}

void check_address(void *p){
    if (p == NULL){
        exit(EXIT_FAILURE);
    }
}