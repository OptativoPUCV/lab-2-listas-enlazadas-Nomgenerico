#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List * lista = (List *) malloc(sizeof(List)) ;
    lista->head = NULL ;
    lista->tail = NULL ;
    lista->current = NULL ;
    return lista ;
}

void * firstList(List * list) {
    list->current = list->head ;
    if (list->current) return list->current->data ;
    return NULL ;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL ;
    list->current = list->current->next ;
    if (list->current) return list->current->data ;
    return NULL;
}

void * lastList(List * list) {
    list->current = list->tail ;
    if (list->current) return list->tail->data ;
    return NULL;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL ;
    list->current = list->current->prev ;
    if (list->current) return list->current->data ;
    return NULL;
}

void pushFront(List * list, void * data) {
    Node *nuevoNodo = createNode(data) ;
    if (list->head == NULL){
        list->head = nuevoNodo ;
        list->tail = nuevoNodo ;
    }
    else {
        list->head->prev = nuevoNodo ;
        nuevoNodo->next = list->head ;
        list->head = nuevoNodo ;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nuevoNodo = createNode(data) ;
    nuevoNodo->prev = list->current ;
    if (list->current->next != NULL) nuevoNodo->next = list->current->next ;
    else {
        list->tail->next = nuevoNodo ;
        nuevoNodo->prev = list->tail ;
        list->tail = nuevoNodo ;
    }
    list->current->next = nuevoNodo ;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current->prev != NULL) list->current->prev->next = list->current->next ;
    else {
        list->head = list->head->next ;
        list->current = list->head ;
        list->head->prev = NULL ;
    }
    if (list->current->next != NULL) list->current->next->prev = list->current->prev ;
    else {
        list->tail = list->tail->prev ;
        list->current = list->tail ;
        list->tail->next = NULL ; 
    }
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}