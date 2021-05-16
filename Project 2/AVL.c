/*
 * File: AVL.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Source code for an AVL tree and Doubly Linked List. Besides the
 * usual structure of such a tree, each node holds a pointer to char and a 
 * pointer to a doubly linked list. The list contains information of the children
 * nodes by order of creation.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AVL.h"

int main() {
    return 0;
}

/* Returns a pointer to a newly created doubly linked list. The pointers
 * to the list's first and last nodes are both pointers to NULL */
List* ListInit() {
    List *lista = (List *) malloc(sizeof(List));
    
    lista->first = NULL;
    lista->last = NULL;

    return lista;    
}


/* Receives a doubly linked list and returns a pointer to the first node on
 * the list */
Node* ListFirst(List *lista) {
    return lista->first;
}


/* Receives a pointer to a doubly linked list and returns a pointer to the last
 * node on the list */
Node* ListLast(List *lista) {
    return lista->last;
}


char* ValueNode(Node *node) {
    return node->value;
}


/* Receives a pointer to a Node structure and returns a pointer 
 * to the next node on the list */
Node* NextNode(Node *node) {
    return node->next;
}

/* Receives a pointer to a Node structure and returns a pointer
 * to the previous node to the one received */
Node* PreviousNode(Node *node) {
    return node->previous;
}


/* Receives a pointer to a doubly linked list and a pointer to char. Inserts a
 * new node at the end of the list and returns the head of the list */
Node* InsertLast(List *list, char *v) {
    Node *new = (Node *) malloc(sizeof(Node));

    new->value = v;
    new->previous = list->last;
    new->next = NULL;
    if (list->first == NULL) { /* If list is empty, insert as first node */
        list->first = new;
    }
    else {
        list->last->next = new;
    }

    return ListFirst(list);
}

/* Receives a pointer to a doubly linked list and prints the value stored
 * on all nodes, by order of insertion on the list (from first to last) */
void PrintList(List *list) {
    Node *ptr = ListFirst(list);

    while (ptr != NULL) {
        printf("%s\n", ValueNode(ptr));
        ptr = NextNode(ptr);
    }
}

/* Receives a pointer to a doubly linked list and frees all nodes on the list */
void DestroyList(List *list) {
    Node *ptr1, *ptr2;

    ptr1 = ListFirst(list);
    while (ptr1 != NULL) {
        ptr2 = ptr1;
        ptr1 = NextNode(ptr1);
        free(ptr2);
    }
    free(list);
}


/* Returns a pointer to the root of a BST struct. The pointer is returned
 * pointing to NULL */
TreeNode* AVLinit() {
    TreeNode *head = NULL;

    return head;
}


/* Receives a pointer to a TreeNode and searchs the node and its children nodes
 * until a node with the value v is found. If no such node is found, this 
 * this function returns NULL */
TreeNode* search(TreeNode *h, char *v) {
    
    if (h == NULL)
        return NULL;

    if (!strcmp(v, h->value)) 
        return h;

    if (strcmp(v, h->value) < 0)
        return search(h->left, v);

    else
        return search(h->right, v);
}

/* Allocates memory for a new TreeNode and returns a pointer to the newly 
 * created node */
TreeNode* NewTN(char* value, TreeNode *left, TreeNode *right) {
    TreeNode *x = (TreeNode *)malloc(sizeof(TreeNode));
    List *children_list = ListInit();

    x->height = 1;
    x->value = value;
    x->left = left;
    x->right = right;
    x->childrenList = children_list;

    return x;
}


/* Receives a pointer to a TreeNode and a value v. */
TreeNode *insert(TreeNode* h, char *value) {

    if (h == NULL)
        return NewTN(value, NULL, NULL);

    if (strcmp(value, h->value) < 0) {
        h->left = insert(h->left, value);
    }
    else {
        h->right = insert(h->right, value);
    }
    h = AVLbalance(h);

    return h;
}

/* Returns an integer corresponding to the number of nodes in the tree */
int count(TreeNode *h) {
    if (h == NULL) {
        return 0;
    }
    
    else {
        return count(h->right) + count(h->left) + 1;
    }
}

/* Returns a pointer to the descendant of TreeNode h with the largest
 * value */
TreeNode* max(TreeNode *h) {
    if (h == NULL || h->right == NULL) {
        return h;
    }
    else {
        return max(h->right);
    }
}

/* Returns a pointer to the descendant of TreeNode h with the smallest
 * value */
TreeNode* min(TreeNode *h) {
    if (h == NULL || h->left == NULL) {
        return h;
    }
    else {
        return min(h->left);
    }
}

/* Receives a pointer to a TreeNode and returns its height */
int height(TreeNode *node)
{
	if(node == NULL)
		return 0;

 	return node->height;
}

/* Receives a pointer to a TreeNode and returns the balance factor for 
 * that node */
int balance(TreeNode *node)
{
	if(node == NULL)
		return 0;

 	return height(node->left) - height(node->right);
}

/* Receives a pointer to a TreeNode and performs a left rotation on that node
 * and its immediate children nodes */
TreeNode* rotateL(TreeNode *h) {
    
    int hleft, hright, xleft, xright;
    TreeNode *x = h->left;
    h->left = x->right;
    x->right = h;
    
    hleft = height(h->left); 
    hright = height(h->right);
    h->height = hleft > hright ? hleft + 1 : hright + 1;
    
    xleft = height(x->left);
    xright = height(x->right);
    x->height = xleft > xright ? xleft + 1 : xright + 1;

    return x; 
}

/* Receives a pointer to a TreeNode and performs a right rotation on that node
 * and its immediate children nodes */
TreeNode* rotateR(TreeNode *h) {
    
    int hleft, hright, xleft, xright;
    TreeNode *x = h->left;
    h->left = x->right;
    x->right = h;
    
    hleft = height(h->left); 
    hright = height(h->right);
    h->height = hleft > hright ? hleft + 1 : hright + 1;
    
    xleft = height(x->left);
    xright = height(x->right);
    x->height = xleft > xright ? xleft + 1 : xright + 1;

    return x; 
}

/* Receives a pointer to a TreeNode and performs a left-right double
 * rotation */
TreeNode* rotateLR(TreeNode *h) {
    
    if (h == NULL) {
    return h;
    }
    h->left = rotateL(h->left);
    
    return rotateR(h);
}

/* Receives a pointer to a TreeNode and performs a left-right double
 * rotation */
TreeNode* rotateRL(TreeNode *h) {

    if (h == NULL) {
        return h;
    }
    h->right = rotateR(h->right);
    
    return rotateL(h);
}

/* Receives a pointer to a TreeNode and balances it */
TreeNode* AVLbalance(TreeNode *h) { 
    int balanceFactor, hleft, hright;
    if (h == NULL) {
        return h;
    }

    balanceFactor = balance(h);     
    if (balanceFactor > 1) {
        if (balance(h->left) >= 0) {
            h = rotateR(h);
        }
        else {
            h = rotateLR(h); 
        }
    } 
    else if (balanceFactor < -1) {
        if (balance(h->right) <= 0) {
            h = rotateL(h);
        }
        else {
            h = rotateRL(h);
        }
    }
    else {
        hleft = height(h->left); 
        hright = height(h->right);
        h->height = hleft > hright ? hleft + 1 : hright + 1;
    }
    
    return h; 
}

/* Receives a pointer to a TreeNode and a value v. Searches the tree
 * for a node with that value and removes it. Memory associated with
 * the node and its value is freed */
TreeNode* deleteR(TreeNode *h, char *v) {
    
    if (h == NULL) return h;
    else if (strcmp(v, h->value) < 0) h->left = deleteR(h->left,v);
    else if (strcmp(h->value, v) < 0) h->right = deleteR(h->right,v) ;
    else {
       if (h->left != NULL && h->right != NULL){
        TreeNode *aux = max(h->left);
        {char *x; x = h->value; h->value = aux->value; aux->value = x;}
        h->left = deleteR(h->left, aux->value);
    }
    else {
        TreeNode *aux = h;
        if (h->left == NULL && h->right == NULL) h = NULL;
        else if (h->left == NULL) h = h->right;
        else h = h->left;
        free(aux->value);
        free(aux);
        }
    }
    h = AVLbalance(h);
    return h;
}
