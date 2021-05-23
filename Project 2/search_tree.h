/*
 * File: search_tree.c
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

void removeChild(TreeNode *parent, TreeNode *node);

void quicksort(TreeNode **children, int left, int right, int context);

int partition(TreeNode **children, int left, int right, int context);

int less(TreeNode *a, TreeNode *b, int context);

TreeNode* traverseTree(TreeNode *h);

void printChildren(TreeNode *node);
