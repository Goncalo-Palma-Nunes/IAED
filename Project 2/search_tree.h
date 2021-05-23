/*
 * File: search_tree.h
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Header file for a n-ary search tree
*/

/* Constant Values */

#define EMPTY 0
#define NON_EMPTY 1
#define CAPACITY 25
#define CREATION 1
#define PATH 2
#define KEY 3

/* Structure Declaration */

typedef struct tree {
    int creation;
    char *value;
    char *key;
    char *component;
    int childrenNumber;
    int capacity;
    struct tree *parent;
    struct tree **children;

} TreeNode;

/* Function Prototypes */


/* Returns a pointer to the root of a new search tree */
TreeNode* Treeinit();

/* Receives a pointer to a TreeNode and returns its key value */
char* pathT(TreeNode *h);

/* Receives a pointer to a TreeNode and returns its path */
char* keyT(TreeNode *h);

/* Receives a pointer to a TreeNode and returns the final
 * component of the path */
char* componentT(TreeNode *h);

/* Receives a pointer to a TreeNode and returns an integer corresponding
 * to the instant of creation of the node */
int instantT(TreeNode *h);

/* Receives a pointer to a TreeNode and returns the number of children
 * that the node has */
int numberChildren(TreeNode *h);

/* Receives a pointer to a TreeNode and returns its children */
TreeNode** nodeChildren(TreeNode *h);

/* Receives a pointer to a TreeNode and returns its first child node.
 * If the node has no children, returns a pointer to NULL */
TreeNode* firstChild(TreeNode *h);

/* Receives a pointer to a TreeNode and returns the capacity of children nodes
 * it can currently hold */
int capacity(TreeNode *h);


/* Receives a pointer to a TreeNode and a key and updates the node's current
 * key */
TreeNode* changeKey(TreeNode *h, char *key, int size);

/* Receives a pointer to a TreeNode and returns an integer EMPTY, as defined in
 * search_tree.h, if the tree is empty, otherwise returns NOT_EMPTY */
int  emptyT(TreeNode *h);

/* Allocates memory for a new TreeNode and returns a pointer to the newly
 * created node */
TreeNode* NewTN(char* value, int instant, int size, char *component,
                TreeNode *h);

/* Returns an integer other than zero, if value v is stored on TreeNode h */
int equal(TreeNode *h, char *value, int context);

/* Searches the tree recursively for the first node with a certain key value.
 * If none is found, returns NULL */
TreeNode* searchT(TreeNode *h, char *value, int context);

/* Creates a new child node to h, inserting it as the last of its children
 * nodes */
TreeNode* insert(TreeNode *h, char *value, int instant, int size, 
                char *component);

/* Frees the memory associated with a TreeNode */
void deleteNode(TreeNode *h);

/* Deletes a TreeNode recursively h and all its descendant nodes */
TreeNode* deleteT(TreeNode *h, TreeNode *root);

/* Receives a pointer to a node and another to its parent-node. Removes it
 * from its parent's array of children nodes, freeing the memory allocated for
 * the removed node */
void removeChild(TreeNode *parent, TreeNode *node);

/* Implementation of a quicksort algorithm to sort arrays of TreeNode*s.
 * Depending on the context provided, as argument, sort is done either
 * alphabetically by path or by order of creation */
void quicksort(TreeNode **children, int left, int right, int context);

/* Implementation of quicksort's partition algorithm */
int partition(TreeNode **children, int left, int right, int context);

/* Returns and integer other than zero if a was created before b or if
 * the path associated with a comes first, alphabetically, than the path
 * associated with b */
int less(TreeNode *a, TreeNode *b, int context);

/* Traverses the tree and prints all the path and key of all nodes
 * with a key value */
TreeNode* traverseTree(TreeNode *h);

/* Prints the last component of all immediate children of a TreeNode/path */
void printChildren(TreeNode *node);
