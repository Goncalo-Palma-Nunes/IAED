/*
 * File: AVL.h
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Header file for an AVL tree
*/


/* Structure Declarations */

struct tree;

typedef struct Node {
    char *value;
    struct Node *next;
    struct Node *previous;

} Node;

typedef struct List {
    Node *first;
    Node *last;

} List;

typedef struct TreeNode {
    int height;
    char *value;
    List *childrenList;
    struct TreeNode *right;
    struct TreeNode *left;
    struct tree *subtree;

} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;


/* Function Prototypes */

/* Returns a pointer to the root of a BST struct. The pointer is returned
 * pointing to NULL */
TreeNode* AVLinit();

/* Receives a pointer to a TreeNode and searchs the node and its children nodes
 * until a node with the value v is found. If no such node is found, this
 * this function returns NULL */
 TreeNode* search(TreeNode *h, char *v);

 /* Allocates memory for a new TreeNode and returns a pointer to the newly
 * created node */
TreeNode* NewTN(char* value, TreeNode *left, TreeNode *right);

/* Receives a pointer to a TreeNode and a value v. */
TreeNode* insert(TreeNode* h, char *value) ;

/* Returns an integer corresponding to the number of nodes in the tree */
int count(TreeNode *h);

/* Returns a pointer to the descendant of TreeNode h with the largest
 * value */
TreeNode* max(TreeNode *h);

/* Returns a pointer to the descendant of TreeNode h with the smallest
 * value */
TreeNode* min(TreeNode *h);

/* Receives a pointer to a TreeNode and returns its height */
int height(TreeNode *node);

/* Receives a pointer to a TreeNode and returns the balance factor for
 * that node */
int balance(TreeNode *node);

/* Receives a pointer to a TreeNode and performs a left rotation on that node
 * and its immediate children nodes */
TreeNode* rotateL(TreeNode *h);

/* Receives a pointer to a TreeNode and performs a right rotation on that node
 * and its immediate children nodes */
TreeNode* rotateR(TreeNode *h);

/* Receives a pointer to a TreeNode and performs a left-right double
 * rotation */
TreeNode* rotateLR(TreeNode *h);

/* Receives a pointer to a TreeNode and performs a left-right double
 * rotation */
TreeNode* rotateRL(TreeNode *h);

/* Receives a pointer to a TreeNode and balances it */
TreeNode* AVLbalance(TreeNode *h);

/* Receives a pointer to a TreeNode and a value v. Searches the tree
 * for a node with that value and removes it. Memory associated with
 * the node and its value is freed */
TreeNode* deleteR(TreeNode *h, char *v);
