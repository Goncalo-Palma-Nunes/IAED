/*
 * File: hash_table.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source code for a hash table
*/


#include <stdlib.h>
#include "search_tree.h"
#include "hash_table.h"


/* Hash function for the table. Receives a pointer to char and the size of
 * the table and returns an index on the table */
int hash(char *v) { 
    int h, a = 6229, b = 7211;
    /*printf("AQUIIIII '%s' AQUIIII\n", v);*/
    /*printf("Inicio de hashing function\n");*/
    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) {
        h = (a*h + *v) % M;
        /*printf("A iterar\n");*/
    }
    /*printf("Fim da hashing function\n");*/

    return h;
}

int hashtwo(char *v) {
    int h, a = 7547, b = 6679;

    /*printf("Inicio de hash two\n");*/
    for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) {
        h = (a * h + *v) % M;
    }
    /*printf("Fim da hash two\n");*/
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

    /*free(pathT(st[i]));
    free(keyT(st[i]));
    free(st[i]);*/
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
    /*printf("STinsert: O valor da hash eh '%d'\n", i);
    printf("STinsert: Vamos entrar no loop\n");*/
    while (st[i] != NULL) {
        i=(i+k)%M;
    }
    /*printf("STinsert: Saimos com sucesso do loop\n");*/
    st[i] = node;
    /*printf("STinsert: Acabou a funcao\n");*/
}

/* Receives a pointer to a hash table and returns the first element found
 * with the value v */
TreeNode* STsearch(char *v, TreeNode **st) {
    int i = hash(v);
    int k = hashtwo(v);
    /*printf("STsearch: O valor da hash eh '%d'\n", i);
    printf("STsearch: Vamos entrar no loop e procurar um node com o valor '%s'\n", v);*/
    while (st[i] != NULL) {
        /*printf("Good one, boss! O indice eh '%d'\n", i);*/
        /*printf("STsearch: Estamos a iterar. O node atual tem o valor '%s'\n", st[i]->value);*/
        if (equal(st[i], v, PATH)) { 
            /*printf("STsearch: Foi encontrado o elemento. Termina a funcao\n");*/
            return st[i];
        }
        else {
            /*printf("STsearch: Vai se incrementar\n");*/
            i = (i+k) % M;
        }
    }
    /*printf("STsearch: A funcao terminou e nao encontrou nada\n");*/
    return NULL;
}
