/*
 * File: hash_table.h
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Header file for a hash table structure. In this implementation,
 * the table is a table of TreeNode structs
*/

/* Constants */

#define M 50000  /* Size of the table */


#include <stdio.h>          /*APAGAR ISTO DEPOIS*/


/* Function Prototypes */

/* Hash function for the table. Receives a pointer to char and the size of
 * the table and returns an index on the table */
int hash(char *v);

/* Initializes a hash table and returns a pointer to the start of the table */
TreeNode** STinit();

/* Receives an integer representation of the key to an item and deletes
 * the first item found with that key */
void STdelete(char *id, TreeNode **st);

/* Receives a pointer to a TreeNode to a hash table and inserts the TreeNode
 * on the table */
void STinsert(TreeNode *node, TreeNode **st);

/* Receives a pointer to a hash table and returns the first element found
 * with the value v */
TreeNode* STsearch(char *v, TreeNode **st);
