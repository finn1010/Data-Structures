#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

typedef struct LinkedList {
    struct Node *tail;
    struct Node *head;
} LinkedList;

LinkedList *initialise();
void destroy(LinkedList *list);
int size(LinkedList *list);
bool empty(LinkedList *list);
int valueAt(LinkedList *list, int index);
void pushFront(LinkedList *list, int value);
void popFront(LinkedList *list);
void pushBack(LinkedList *list, int value);
void popBack(LinkedList *list);
int front(LinkedList *list);
int back(LinkedList *list);
void insert(LinkedList *list, int value, int index);
void erase(LinkedList *list, int index);
int value_n_from_end(LinkedList *list, int n);
void reverse(LinkedList *list);
void remove_value(LinkedList *list, int value);
void printList(LinkedList *list);
void check_address(void *p);

#endif  // LINKEDLIST_H
