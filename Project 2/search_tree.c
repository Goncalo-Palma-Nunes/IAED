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

/* Returns a pointer to the root of a new search tree */
TreeNode* Treeinit() {
    TreeNode *head = NULL;

    return head;
}

/* Receives a pointer to a TreeNode and returns its path */
char* pathT(TreeNode *h) {
    return h->value;
}

/* Receives a pointer to a TreeNode and returns its key */
char* keyT(TreeNode *h) {
    return h->key;
}

/* Receives a pointer to a TreeNode and returns the final
 * component of the path */
char* componentT(TreeNode *h) {
    return h->component;
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

TreeNode* parentT(TreeNode *h) {
    return h->parent;
}

/* Receives a pointer to a TreeNode and returns its first child node.
 * If the node has no children, returns a pointer to NULL */
TreeNode* firstChild(TreeNode *h) {
    
    if (numberChildren(h)) {
        return h->children[0];
    }
    return NULL;
}

/* Receives a pointer to a TreeNode and returns the capacity of children nodes
 * it can currently hold */
int capacity(TreeNode *h) {
    return h->capacity;
}

/* Receives a pointer to a TreeNode and a key and updates the node's current
 * key */
TreeNode* changeKey(TreeNode *h, char *key, int size) {
    if (keyT(h) == NULL ) {
        h->key = (char *) malloc(sizeof(char) * (size + 2));
    }
    else {
        h->key = (char *) realloc(h->key, (size + 2));
    }
    strcpy(h->key, key);
    return h;
}

/* Receives a pointer to a TreeNode and returns an integer EMPTY, as defined in
 * search_tree.h, if the tree is empty, otherwise returns NOT_EMPTY */
int  emptyT(TreeNode *h) {
    if (h == NULL) {
        return EMPTY;
    }
    return NON_EMPTY;
}

/* Allocates memory for a new TreeNode and returns a pointer to the newly
 * created node */
TreeNode* NewTN(char *value, int instant, int size, char *component, 
                TreeNode *h) {
    TreeNode *x = (TreeNode *) malloc(sizeof(TreeNode));

    x->children = (TreeNode **) malloc(sizeof(TreeNode *) * CAPACITY);
    x->capacity = CAPACITY;
    x->key = NULL;
    x->childrenNumber = 0;
    x->creation = instant;
    x->parent = h;

    x->component = (char *) malloc(sizeof(char) * (strlen(component) + 1));
    strcpy(x->component, component);

    x->value = (char *) malloc(sizeof(char) * (size + 3));
    strcpy(x->value, value);

    return x;
}

/* Returns an integer other than zero, if value v is stored on TreeNode h */
int equal(TreeNode *h, char *value, int context) {
    int res = 0;

    if (h == NULL) {
        return res;
    }

    if (context == PATH) {
        res = !strcmp(pathT(h), value);
    }
    else if (context == KEY && keyT(h) != NULL) {
        res = !strcmp(keyT(h), value);
    }

    return res;
}

/* Searches the tree recursively for the first node with the key value.
 * If none is found, returns NULL */
TreeNode* searchT(TreeNode *h, char *value, int context) {
    TreeNode **children;
    int i, limit;

    if (h == NULL) {
        return NULL;
    }
    else if (equal(h,value, context)) {
        return h;
    }
    children = nodeChildren(h);
    limit = numberChildren(h);
    
    for (i = 0; i < limit; ++i) {
        h = searchT(children[i], value, context);
        
        if (h != NULL) {
            return h;
        }
    }

    return NULL;
}

/* Creates a new child node to h, inserting it as the last of its children
 * nodes */
TreeNode* insert(TreeNode *h, char *value, int instant, int size, 
                char *component) {
    TreeNode **children, *new = NewTN(value, instant, size, component, h);
    int cap, occupation;

    if (h == NULL) {
        h = new;
        return new;
    }
    children = nodeChildren(h);
    occupation = numberChildren(h);
    cap = capacity(h);
    if (cap == occupation) {
        cap = cap + cap;
        children = (TreeNode **) realloc(children, cap);
    }

    h->children[h->childrenNumber++] = new;
    h->capacity = cap;

    return new;
}

/* Frees the memory associated with a TreeNode */
void deleteNode(TreeNode *h) {
    
    free(h->value);
    free(h->component);

    if (h->key != NULL) {
        free(h->key);
    }

    free(h->children);
    if (instantT(h) != 0) { /* If h isn't the root directory */
        h->parent->childrenNumber--;
    }
    free(h);
}

/* Deletes recursively a TreeNode h and all its descendant nodes */
TreeNode* deleteT(TreeNode *h, TreeNode *root) {
    TreeNode *parent, **children = nodeChildren(h);
    int occ, i;

    occ = numberChildren(h);
    if (occ == 0) {
        if (instantT(h) == 0) { /* If the root has no sub-directories */
            deleteNode(h);
        }
        else {
            parent = parentT(h);
            removeChild(parent, h);
        }
        return NULL;
    }
    for (i = (occ - 1); i >= 0; i--) {
        deleteT(children[i], root);    /* Delete all "descendant" directories */
        h->childrenNumber--;
    }
    if (h == root) { /* If we're deleting the root directory */
        deleteNode(h);
        return NULL;
    }
    parent = parentT(h);
    removeChild(parent, h);

    return parent;;
}

/* Receives a pointer to a node and another to its parent-node. Removes it
 * from its parent's array of children nodes, freeing the memory allocated for
 * the removed node */
void removeChild(TreeNode *parent,TreeNode *node) {
    TreeNode **children = nodeChildren(parent);
    int occ, i;

    occ = numberChildren(parent);
    for (i = 0; i < occ; i++) {
        if (children[i] == node) {
            children[i] = children[--occ]; /* Swap place with the "last child" */
            deleteNode(node);
            return;
        }
    }

}

/* Implementation of a quicksort algorithm to sort arrays of TreeNode*s.
 * Depending on the context provided, as argument, sort is done either
 * alphabetically by path or by order of creation */
void quicksort(TreeNode **children, int left, int right, int context) {
    int i;
    
    if (right <= left) {
        return;
    }
    
    i = partition(children, left, right, context);
    quicksort(children, left, i-1, context);
    quicksort(children, i+1, right, context);
}

/* Implementation of quicksort's partition algorithm */
int partition(TreeNode **children, int left, int right, int context) {
    int i = left-1;
    int j = right;
    TreeNode *temp, *v = children[right];
    
    while (i < j) {
        while (less(children[++i], v, context));
        while (less(v, children[--j], context)) {
           if (j == left)
                break;
        }
        if (i < j) {
            temp = children[i];
            children[i] = children[j];
            children[j] = temp;
        }
    }
    temp = children[i];
    children[i] = children[right];
    children[right] = temp;
    
    return i;
}

/* Returns and integer other than zero if a was created before b or if 
 * the path associated with a comes first, alphabetically, than the path
 * associated with b */
int less(TreeNode *a, TreeNode *b, int context) {
    return (a != NULL && ((context == CREATION && instantT(a) < instantT(b)) ||
        (context == PATH && strcmp(componentT(a), componentT(b)) < 0)));
}


/* Traverses the tree and prints all the path and key of all nodes
 * with a key value */
TreeNode* traverseTree(TreeNode *h) {
    TreeNode **children;
    int i, limit;
    char *key;
    
    if (h == NULL) {
        return NULL;
    }
    else if ((key = keyT(h)) != NULL) {
        printf("%s %s\n", pathT(h), keyT(h));
    }

    children = nodeChildren(h);
    limit = numberChildren(h);
    quicksort(children, 0, limit - 1, CREATION);

    for (i = 0; i < limit; ++i) {
        h = traverseTree(children[i]);
    }

    return NULL;
}

/* Prints the last component of all immediate children of a TreeNode/path */
void printChildren(TreeNode *node) {
    int i, limit;
    TreeNode **children;

    limit = numberChildren(node);
    children = nodeChildren(node);
    quicksort(children, 0, limit - 1, PATH);
    for (i = 0; i < limit; ++i) {
        printf("%s\n", componentT(children[i]));
    }
}
