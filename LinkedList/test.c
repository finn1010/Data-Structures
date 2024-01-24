#include "test.h"
#include "linkedlist.h"
void run_all_tests() {
  test_size();
  test_push_front();
  test_empty();
  test_front();
  test_back();
  test_pop_front();
  test_push_back();
  test_pop_back();
  test_insert();
  test_value_at();
  test_erase();
  test_value_n_from_end();
  test_reverse();
//   test_reverse_single();
//   test_reverse_empty();
  test_remove();
}

void test_size(){
    int listSize = 0;
    LinkedList *list = initialise();
    listSize = size(list);
    assert(listSize == 0);
    pushFront(list, 3);
    pushFront(list, 2);
    int listSize1 = size(list);
    assert(listSize1 == 2);
    destroy(list);
}

void test_push_front(){
    LinkedList *list = initialise();
    int listSize = size(list);
    assert(listSize == 0);
    pushFront(list, 3);
    pushFront(list, 2);
    int listSize1 = size(list);
    assert(listSize1 == 2);
    destroy(list);
}

void test_empty(){
    LinkedList *list = initialise();
    pushFront(list, 2);
    assert(front(list) == 2);
    pushFront(list, 24);
    assert(front(list) == 24);
    destroy(list);  
}

void test_front(){
    LinkedList *list = initialise();
    pushFront(list,2);
    assert(front(list) == 2);
}

void test_back(){
    LinkedList *list = initialise();
    pushFront(list, 3);
    pushBack(list,2);
    assert(back(list) == 2);
    destroy(list);
}
void test_pop_front(){
    LinkedList *list = initialise();
    pushFront(list,33);
    pushFront(list,45);
    assert(front(list) == 45);
    popFront(list);
    assert(front(list) == 33);
    destroy(list);
}
void test_push_back(){
    LinkedList *list = initialise();
    pushFront(list,11);
    assert(back(list) == 11);
    pushBack(list, 22);
    assert(back(list) == 22);
    destroy(list);
}
void test_pop_back(){
    LinkedList *list = initialise();
    pushBack(list, 11);
    pushBack(list,22);
    assert(back(list)==22);
    popBack(list);
    assert(back(list) == 11);
    destroy(list);
}

void test_insert(){
    LinkedList *list = initialise();
    pushFront(list, 11);
    pushFront(list, 22);
    pushBack(list, 56);
    // printList(list);
    assert(valueAt(list, 0) == 22);
    
    insert(list, 12, 1);
    
    // printf("List after insertion: ");
    // printList(list);
    
    assert(valueAt(list, 1) == 12);
    destroy(list);
}
void test_value_at(){
    LinkedList *list = initialise();
    pushFront(list, 1);
    pushFront(list, 3);
    // printList(list);
    assert(valueAt(list,0) == 3);
    destroy(list);
}

void test_erase(){
    LinkedList *list = initialise();
    pushFront(list, 1);
    pushFront(list, 3);
    assert(size(list) == 2);
    erase(list,0);
    assert(size(list) == 1);
    assert(front(list) == 1);
    destroy(list);
}

void test_value_n_from_end(){
    LinkedList *list = initialise();
    pushFront(list, 1);
    pushFront(list, 3);
    pushFront(list,42);

    assert(value_n_from_end(list,1) == 1);
    destroy(list);
}

void test_reverse(){
    LinkedList *list = initialise();
    pushFront(list, 1);
    pushFront(list, 3);
    reverse(list);
    assert(valueAt(list, 1) == 3);
    assert(valueAt(list,0) == 1);
    destroy(list);
}

void test_remove(){
    LinkedList *list = initialise();
    pushFront(list, 1);
    pushFront(list, 3);
    pushFront(list, 3);
    remove_value(list, 3);
    assert(valueAt(list,0) == 1);
    assert(size(list) == 1);
    destroy(list);
}