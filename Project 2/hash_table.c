/*
 * File: hash_table.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source code for a hash table
*/


#include <stdlib.h>
#include "search_tree.h"
#include "hash_table.h"


/* Hash function for the table. Receives a pointer to char and
 * returns an index on the table */
int hash(char *v) { 
    long int h, a = 31415, b = 27183;

    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) {
        h = (a*h + *v) % M;

    }

    return h;
}

/* Second hashing function to take care of colisions */
int hashtwo(char *v) {
    long int h, a = 7547, b = 6679;


    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) {
        h = (a * h + *v) % M;
    }

    return h;
}
/* Initializes a hash table and returns a pointer to the start of the table */
TreeNode** STinit() {
    int i;
    TreeNode **heads = (TreeNode **) malloc(M*sizeof(TreeNode *));

    for (i = 0; i < M; i++) {
        heads[i] = NULL;
    }

    return heads;
}


/* Receives an integer representation of the key to an item and removes
 * the first item found with that key from the table */
void STdelete(char *id, TreeNode **st) { 
    int j, k, i = hash(id);
    TreeNode *v;
    k = hashtwo(id);

    while (st[i] != NULL) {
        if (equal(st[i], id, PATH)) break;
        
        else i = (i+k) % M;
    }
    if (st[i] == NULL) {
        return;
    }

    st[i] = NULL; 
    for (j = (i+k) % M; st[j] != NULL; j = (j+k) % M) {
        v = st[j]; 
        st[j] = NULL;
        STinsert(v, st);
    }
}

/* Receives a pointer to a TreeNode to a hash table and inserts the TreeNode
 * on the table */
void STinsert(TreeNode *node, TreeNode **st) {
    char *v = pathT(node);
    int i = hash(v);
    int k = hashtwo(v);

    while (st[i] != NULL) {
        i=(i+k)%M;
    }

    st[i] = node;
}

/* Receives a pointer to a hash table and returns the first element found
 * with the value v */
TreeNode* STsearch(char *v, TreeNode **st) {
    int i = hash(v);
    int k = hashtwo(v);

    while (st[i] != NULL) {
        if (equal(st[i], v, PATH)) { 
            return st[i];
        }
        else {
            i = (i+k) % M;
        }
    }
    return NULL;
}
