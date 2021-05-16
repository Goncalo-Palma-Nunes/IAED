/*
 * File: search_tree.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source code for a search tree. Each tree tree node contains two
 * doubly linked lists of its children nodes. One list preserves the order of
 * creation of the nodes while the other is sorted by alphabetic order
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search_tree.h"

int main() {
    return 0;
}

/* Returns a pointer to the root of a new search tree */
TreeNode* Treeinit() {
    TreeNode *head = NULL;

    return head;
}

/* Receives a pointer to a TreeNode and returns its key value */
char* keyT(TreeNode *h) {
    return h->value;
}

/* Receives a pointer to a TreeNode and returns an integer corresponding
 * to the instant of creation of the node */
int instantT(TreeNode *h) {
    return h->creation;
}

/* Receives a pointer to a TreeNode and returns the number of children
 * that the node has */
int numberChildren(TreeNode *h) {
    return h->childrenNumber;
}

TreeNode** nodeChildren(TreeNode *h) {
    return h->children;
}

/* Receives a pointer to a TreeNode and returns its first child node.
 * If the node has no children, returns a pointer to NULL */
TreeNode* firstChild(TreeNode *h) {
    
    if (numberChildren(h)) {
        return h->children[0]
    }
    return NULL;
}

/* Receives a pointer to a TreeNode and returns the capacity of children nodes
 * it can currently hold */
TreeNode* capacity(TreeNode *h) {
    return h->capacity;
}

/* Receives a pointer to a TreeNode and returns an integer EMPTY, as defined in
 * search_tree.h, if the tree is empty, otherwise returns NOT_EMPTY */
int  emptyT(TreeNode *h) {
    if (h == NULL) {
        return EMPTY;
    }
    return NOT_EMPTY;
}

/* Allocates memory for a new TreeNode and returns a pointer to the newly
 * created node */
TreeNode* NewTN(char* value, int instant) {
    TreeNode *x = (TreeNode *)malloc(sizeof(TreeNode));

    x->children = (char **) malloc(sizeof(char *) * CAPACITY);
    x->capacity = CAPACITY;
    x->childrenNumber = 0;
    x->creation = instant;
    strcpy(x->value, value);

    return x;
}

/* Returns an integer other than zero, if value v is stored on TreeNode h */
int equal(TreeNode *h, char *value) {
    return strcmp(keyT(h), value);
}

/* Searches the tree recursively for the first node with the key value.
 * If none is found, returns NULL */
TreeNode* searchT(TreeNode *h, char *value) {
    TreeNode **children;
    int i, limit;

    if (h == NULL) {
        return NULL;
    }
    else if (equal(h,v)) {
        return h;
    }
    children = nodeChildren(h);
    limit = numberChildren(h);
    
    for (i = 0; i < limit; ++i) {
        h = searchT(children[i], value);
        
        if (h != NULL) {
            return h;
        }
    }

    return NULL;
}

/* Creates a new child node to h, inserting it as the last of its children
 * nodes */
TreeNode* insert(TreeNode *h, char *value, int instant) {
    TreeNode **children, *new = NewTN(value, instant);
    int cap, occupation;

    if (h == NULL) {
        h = new;
    }
    children = nodeChildren(h);
    occupation = numberChildren(h);
    cap = capacity(h);
    if (cap == occupation) {
        children = (char **) realloc(children, cap + cap);
    }
    children[x->childrenNumber++] = new;
}

/* Frees the memory associated with a TreeNode */
void deleteNode(TreeNode *h) {
    free(h->value);
    free(h->children);
    free(h);
}

/* Deletes recursively a TreeNode h and all its descendant nodes */
TreeNode* delete(TreeNode *h) {
    TreeNode **children = nodeChildren(h);
    int cap, occ, i;

    occ = numberChildren(h);
    cap = capacity(h);
    if (occ == 0) {
        deleteNode(h);
    }
    for (i = 0; i < occ; i++) {
        delete(children[i]);
    }
    deleteNode(h);
}
