/*
 * File: LinkedList.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source file for doubly linked list
*/

#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    char *value;
    struct Node *next;
    struct Node *previous;

} Node;

typedef struct List {
    Node *first;
    Node *last;

} List;


int main() {
    return 0;
}


/* Returns a pointer to a newly created doubly linked list. The pointers
 * to the list's first and last nodes are both pointers to NULL */
List* ListInit() {
    List *lista = (List *) malloc(sizeof(List));
    
    lista->first = NULL;
    lista->last = NULL;


    return lista;    
}


/* Receives a doubly linked list and returns a pointer to the first node on
 * the list */
Node* ListFirst(List *lista) {
    return lista->first;
}


/* Receives a pointer to a doubly linked list and returns a pointer to the last
 * node on the list */
Node* ListLast(List *lista) {
    return lista->last;
}


char* ValueNode(Node *node) {
    return node->value;
}


/* Receives a pointer to a Node structure and returns a pointer 
 * to the next node on the list */
Node* NextNode(Node *node) {
    return node->next;
}

/* Receives a pointer to a Node structure and returns a pointer
 * to the previous node to the one received */
Node* PreviousNode(Node *node) {
    return node->previous;
}


/* Receives a pointer to a doubly linked list and a pointer to char. Inserts a
 * new node at the end of the list and returns the head of the list */
Node* InsertLast(List *list, char *v) {
    Node *new = (Node *) malloc(sizeof(Node));

    new->value = v;
    new->previous = list->last;
    new->next = NULL;
    if (list->first == NULL) { /* If list is empty, insert as first node */
        list->first = new;
    }
    else {
        list->last->next = new;
    }

    return ListFirst(list);
}

/* Receives a pointer to a doubly linked list and prints the value stored
 * on all nodes, by order of insertion on the list (from first to last) */
void PrintList(List *list) {
    Node *ptr = ListFirst(list);

    while (ptr != NULL) {
        printf("%s\n", ValueNode(ptr));
        ptr = NextNode(ptr);
    }
}

/* Receives a pointer to a doubly linked list and frees all nodes on the list */
void DestroyList(List *list) {
    Node *ptr1, *ptr2;

    ptr1 = ListFirst(list);
    while (ptr1 != NULL) {
        ptr2 = ptr1;
        ptr1 = NextNode(ptr1);
        free(ptr2);
    }
    free(list);
}
