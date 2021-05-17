/*
 * File: hash_table.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source code for a hash table
*/


/*#include "hashtable.h"*/
#include <stdlib.h>


int main() {
    return 0;
}

int hash(char *v, int M) { 
    int h, a = 31415, b = 27183;
    
    for (h = 0; *v != ’\0’; v++, a = a*b % (M-1))
        h = (a*h + *v) % M;

    return h;
}

void STinit(int m) {
    int i;
    M = m;
    heads = (TreeNode **) malloc(M*sizeof(TreeNode *));

    for (i = 0; i < M; i++) {
        heads[i] = NULL;
    }
}


void STdelete(unsigned long id) { 
    int j, i = hash(id, M); pPerson v;

    while (st[i] != NULL) {
        if (st[i]->idNumber == id) break;
        
        else i = (i+1) % M;
    }
    if (st[i] == NULL) {
        return;
    }

/*    free(st[i]->value);*/
    free(pathT(st[i]));
    free(keyT(st[i]));
    free(st[i]);
    st[i] = NULL; 
    for (j = (i+1) % M; st[j] != NULL; j = (j+1) % M) {
        v = st[j]; 
        st[j] = NULL;
        STinsert(v);
    }
}

void STinsert(TreeNode *node) {
    char *v = pathT(node);
    int i = hash(v, M);
    int k = hashtwo(v, M);
    while (st[i] != NULL) {
        i=(i+k)%M;
    }
   st[i] = node;
}

TreeNode* STsearch(char *v) {
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
