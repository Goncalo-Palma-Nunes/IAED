/*
 * File: hash_table.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source code for a hash table
*/


/*#include "hashtable.h"*/
#include <stdlib.h>
#include "search_table.h"


int main() {
    return 0;
}


/* Hash function for the table. Receives a pointer to char and the size of
 * the table and returns an index on the table */
int hash(char *v) { 
    int h, a = 31415, b = 27183;
    
    for (h = 0; *v != ’\0’; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;

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


/* Receives an integer representation of the key to an item and deletes
 * the first item found with that key */
void STdelete(unsigned long id, TreeNode **st) { 
    int j, k, i = hash(id, M) 
    int k = hashtwo(v, M);
    TreeNode *v;

    while (st[i] != NULL) {
        if (equal(st[i], v)) break;
        
        else i = (i+k) % M;
    }
    if (st[i] == NULL) {
        return;
    }

/*    free(st[i]->value);*/
    free(pathT(st[i]));
    free(keyT(st[i]));
    free(st[i]);
    st[i] = NULL; 
    for (j = (i+k) % M; st[j] != NULL; j = (j+k) % M) {
        v = st[j]; 
        st[j] = NULL;
        STinsert(v);
    }
}

/* Receives a pointer to a TreeNode to a hash table and inserts the TreeNode
 * on the table */
void STinsert(TreeNode *node, TreeNode **st) {
    char *v = pathT(node);
    int i = hash(v, M);
    int k = hashtwo(v, M);
    while (st[i] != NULL) {
        i=(i+k)%M;
    }
   st[i] = node;
}

/* Receives a pointer to a hash table and returns the first element found
 * with the value v */
TreeNode* STsearch(char *v, TreeNode **st) {
    int i = hash(v, M);
    int k = hashtwo(v, M);
    while (st[i] != NULL) {
        if (equal(st[i], v)) { 
            return st[i];
        }
        else {
            i = (i+k) % M;
        }
    }
    return NULL;
}
