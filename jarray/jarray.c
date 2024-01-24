#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// vector implementation
#include "jarray.h"

JArray *jarray_new(int capacity){
    JArray *array = malloc(sizeof(JArray));
    array -> capacity = check_capacity(capacity); // Add this line to update capacity
    int true_capacity = array->capacity;
    check_address(array);
    array -> size = 0;
    array -> data = (int *) malloc(sizeof(int) * true_capacity);
    check_address(array -> data);

    return array;
}


int check_capacity(int capacity){
    const int kMinInitialCapacity = 1;
    int true_capacity = kMinCapacity;

    if (capacity < kMinInitialCapacity){
        exit(EXIT_FAILURE);
    }

    while (capacity > true_capacity/kGrowthFactor) {
        true_capacity *= kGrowthFactor;
    }
    return true_capacity;   
}

void  jarray_upsize(JArray *arrptr){
    int old_capacity = arrptr -> capacity;
    int new_capacity = arrptr->capacity / kGrowthFactor;

    int *new_data = (int *)realloc(arrptr->data, sizeof(int) * new_capacity);
    check_address(new_data);

    arrptr->data = new_data;
    arrptr->capacity = new_capacity;
    
}

void jarray_downsize(JArray *arrptr){
    int old_capacity = arrptr->capacity;
    int new_capacity = old_capacity/kGrowthFactor;

    if (new_capacity < kMinCapacity){
        new_capacity = kMinCapacity;
    }
    if (new_capacity != old_capacity){
        int *new_data = (int *)realloc(arrptr->data, sizeof(int) * new_capacity);
        check_address(new_data);
        arrptr->data = new_data;
        arrptr->capacity = new_capacity;
    }
}

int jarray_size(JArray *arrptr){
    return arrptr->size;
}

void jarray_destroy(JArray *arrptr){
    free(arrptr->data);
    free(arrptr);
}

void jarray_resize_for_size(JArray *arrptr, int candidate_size){
    if (arrptr->size < candidate_size){
        if (arrptr->size == arrptr->capacity){
            jarray_upsize(arrptr);
        }
    }
    else if (arrptr->size > candidate_size){
        if (arrptr->size < arrptr->capacity/kShrinkFactor){
            jarray_downsize(arrptr);
        }
    }
}

void jarray_push(JArray *arrptr, int item){

    jarray_resize_for_size(arrptr, arrptr->size + 1); // increasing array capacity
    *(arrptr->data + arrptr->size) = item; 
    ++(arrptr->size); //increasing array size
}

void jarray_print(JArray *arrptr){
    printf("Size: %d\n", arrptr->size);
    printf("Capacity: %d\n", arrptr->capacity);
    printf("Items:\n");

    for (int i = 0; i < arrptr->size; i++){
        printf("%d: %d\n", i, *(arrptr->data + i));
    }
  printf("---------\n");
}

bool jarray_is_empty(JArray *arrptr){
    return arrptr -> size == 0;
}

int jarray_pop(JArray *arrptr) {
  if (arrptr->size == 0) {
    exit(EXIT_FAILURE);
  }

  jarray_resize_for_size(arrptr, arrptr->size - 1);

  int popped_value = *(arrptr->data + arrptr->size - 1);
  arrptr->size--;

  return popped_value;
}

int jarray_find(JArray *arrptr, int value){
    int found_index = -1;
    for (int i = 0; i < arrptr->size; i++){
        if (*(arrptr->data+i) == value){
            found_index = i;
            break;
        }
    }
    return found_index;
}

void jarray_delete(JArray *arrptr, int index){
    if (index == 0 || index >= arrptr->size){
        exit(EXIT_FAILURE);
    }
    jarray_resize_for_size(arrptr, arrptr->size-1);

    memmove(arrptr->data + index, arrptr->data + index + 1, (arrptr->size - index) * sizeof(int));
    // first argument is the destination pointer so, second is a pointer to what its copying the rest of the data appending it to the destination and missing the value at the index
    // the third argument is the number of integers that are being copied.
    --(arrptr->size);
}

void jarray_remove(JArray *arrptr, int value){
    int find_index = -1;
    for (int i = 0; i < arrptr->size; i++){
        int check_value = *(arrptr->data + i);
        if (check_value == value){
            jarray_delete(arrptr, i);
            i--; // to recheck index the data was just copied into
        }
    } 
}

int jarray_at(JArray *arrptr, int index){
    if (index < 0 || index > arrptr->size-1){
        exit(EXIT_FAILURE);
    }
    return *(arrptr->data + index);
}
void jarray_insert(JArray *arrptr, int index, int value){
    if (index < 0 || index > arrptr->size){
        exit(EXIT_FAILURE);
    }

    jarray_resize_for_size(arrptr, arrptr->size + 1);

    memmove(arrptr->data + index + 1, arrptr->data + index, (arrptr->size - index - 1) * sizeof(int));

    *(arrptr->data + index) = value;

    arrptr->size++;
}

void jarray_prepend(JArray *arrptr, int value){
    printf("prependbeofre");
    jarray_insert(arrptr, 0, value);    
    printf("prependafter");
}
int jarray_capacity(JArray *arrptr) { return arrptr->capacity; }


void check_address(void *p){
if(p == NULL){
    exit(EXIT_FAILURE);
    }
}

//=========== tests ===================================

void run_all_tests(){

}

void test_size_init(){
    JArray *arrptr = jarray_new(5);
    int initial_size = jarray_size(arrptr);
    assert(initial_size == 0);
    jarray_destroy(arrptr);
}

void test_append(){
    JArray *arrptr = jarray_new(5);
    jarray_push(arrptr, 2);
    jarray_push(arrptr, 3);
    int new_size = jarray_size(arrptr);
    assert(new_size == 2);
    jarray_destroy(arrptr);
}

void test_empty(){
    JArray *arrptr = jarray_new(5);
    bool empty = jarray_is_empty(arrptr);
    assert(empty == 1);
    jarray_push(arrptr, 3);
    jarray_is_empty(arrptr);
    assert(empty == 0);
    jarray_destroy(arrptr);
}

void test_resize(){
    JArray *arrptr = jarray_new(5);
    int old_capacity = jarray_capacity(arrptr);
    assert(old_capacity == 16);
    for (int i = 0; i < 18; i++){
        jarray_push(arrptr, i+1);
    }
    assert(jarray_capacity(arrptr) == 32);
    for (int i = 0; i < 15; i++){
        jarray_pop(arrptr);
    }
    assert(jarray_capacity(arrptr) == 16);
    jarray_destroy(arrptr);
}

void test_at(){
    JArray *arrptr = jarray_new(5);
    jarray_push(arrptr,2);
    jarray_push(arrptr,4);
    int index = jarray_at(arrptr,0);
    assert(index == 2);
    jarray_destroy(arrptr);
}

void test_insert(){
    JArray *arrptr = jarray_new(5);
    for (int i = 0; i<5; i++){
        jarray_insert(arrptr, i, i+1);
    }
    int num = jarray_at(arrptr, 0);
    assert(num == 1);
    jarray_destroy(arrptr);

}

void test_prepend(){
    JArray *arrptr = jarray_new(5);
    for (int i = 0; i < 5; i++){
        jarray_push(arrptr, i+1);
    }
    assert(jarray_at(arrptr, 0) == 1);
    assert(jarray_at(arrptr, 1) == 2);
    jarray_destroy(arrptr);
    printf("good");
}

void test_pop(){
    JArray *arrptr = jarray_new(5);
    for (int i = 0; i < 5; i++){
        jarray_push(arrptr, i + 1);
    }
    assert(jarray_size(arrptr) == 5);
    for (int i = 0; i < 5; i++){
        jarray_pop(arrptr);
    }
    assert(jarray_is_empty(arrptr) == 1);
    jarray_destroy(arrptr);
}

void test_remove(){
  JArray *arrptr = jarray_new(5);
  jarray_push(arrptr, 12);
  jarray_push(arrptr, 3);
  jarray_push(arrptr, 41);
  jarray_push(arrptr, 12);
  jarray_push(arrptr, 12);
  jarray_remove(arrptr, 12);
  assert(jarray_size(arrptr) == 3);
  jarray_destroy(arrptr);
}

void test_find_exists(){
    JArray *arrptr = jarray_new(5);
    for (int i = 0; i < 5; i++){
        jarray_push(arrptr, i+1);
    }
    int index = jarray_find(arrptr, 2);
    assert(index == 1);
    jarray_destroy(arrptr);
}

void test_find_not_exists(){
    JArray *arrptr = jarray_new(3);
    jarray_push(arrptr, 1);
    jarray_push(arrptr, 2);
    jarray_push(arrptr, 3);
    assert(jarray_at(arrptr, -2) == -1);
    jarray_destroy(arrptr);
}