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
    /*printf("Será aqui?\n");
    if (h == NULL) printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");*/
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
    /*if (h == NULL) printf("PROOOOOOBLEEEEEEEEEEEEEEEEMA\n");
    printf("Instantt: Prestes a sair\n");*/
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
    /*x->value = value;*/
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
    /*printf("Roger Roger\n");*/
    if (context == PATH) {
        res = !strcmp(pathT(h), value);
    }
    else if (context == KEY && keyT(h) != NULL) {
        /*printf("equal: Estamos no equal. O path eh '%s' e o valor eh '%s'\n", pathT(h), keyT(h));*/
        res = !strcmp(keyT(h), value);
    }
    /*printf("Welcome to Dubai gentlemen\n");*/
    return res;
    /*return !strcmp(pathT(h), value);*/
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
    /*printf("\ninsert: Prestes a inserir o novo elemento na lista de filhos\n");
    printf("insert: O pai é '%s' e o filho é '%s'. Está a ser inserido em '%d'\n", h->value, new->value, h->childrenNumber);*/
    /*children[h->childrenNumber++] = new;*/
    h->children[h->childrenNumber++] = new;
    /*printf("insert: Após inserção o number_children é '%d' e no indice anterior tem-se '%s'\n\n", h->childrenNumber, children[h->childrenNumber - 1]->value);*/
    h->capacity = cap;

    return new;
}

/* Frees the memory associated with a TreeNode */
void deleteNode(TreeNode *h) {
    /*printf("\ndeleteNode: Vamos começar a apagar o node '%s'\n", pathT(h));*/
    free(h->value);
    free(h->component);
    free(h->key);
    free(h->children);
    /*printf("deleteNode: o seu pai tinha '%d'\n", h->parent->childrenNumber);*/
    h->parent->childrenNumber--;
    /*printf("deleteNode: agora tem '%d'\n", h->parent->childrenNumber);*/
    free(h);
    /*printf("deleteNode: Foi apagado com sucesso\n\n");*/
}

/* Deletes recursively a TreeNode h and all its descendant nodes */
TreeNode* deleteT(TreeNode *h, TreeNode *root) {
    TreeNode *parent, **children = nodeChildren(h);
    int occ, i;

    /*printf("deleteT: O node atual eh '%s'\n", pathT(h));*/
    occ = numberChildren(h);
    /*printf("deleteT: Ele tem '%d' filhos\n", occ);*/
    if (occ == 0) {
        /*printf("deleteT: Logo, vai ser apagado\n");*/
        /*deleteNode(h);*/
        parent = parentT(h);
        removeChild(parent, h);
        return NULL;
    }
    for (i = (occ - 1); i >= 0; i--) {
        /*printf("deleteT: estamos no filho nº '%d' com path '%s'\n", (i + 1), pathT(children[i]));*/ 
        deleteT(children[i], root);
        h->childrenNumber--;
        /*printf("deleteT: De momento ainda estamos no filho nº '%d'\n", (i + 1));*/
    }
    /*printf("deleteT: os filhos foram removidos com sucesso\n");*/
    if (h == root) { /* If we're deleting the root directory */
        /*deleteNode(h);*/
        return NULL;
    }
    parent = parentT(h);
    /*printf("deleteT: vamos apagar o '%s'\n", pathT(h));
    printf("deleteT: o pai do node que estamos a apagar eh '%s'\n", pathT(parent));
    printf("deleteT: Vamos remover o node da lista de filhos do seu pai");*/
    removeChild(parent, h);
    /*printf("deleteT: Conseguimos\n");*/
    /*deleteNode(h);*/

    return parent;;
}

void removeChild(TreeNode *parent,TreeNode *node) {
    TreeNode **children = nodeChildren(parent);
    int occ, i;

    occ = numberChildren(parent);
    for (i = 0; i < occ; i++) {
        if (children[i] == node) {
            /*printf("removeChild: Queremos apagar o '%s'\n", pathT(node));
            printf("removeChild: Vamos primeiro trocá-lo com '%s'\n", pathT(children[occ - 1]));*/
            children[i] = children[--occ]; /* Swap place with the "last child" */
            deleteNode(node);
            /*parent->childrenNumber = occ;*/
            return;
        }
    }

}

void quicksort(TreeNode **children, int left, int right, int context) {
    int i;
    
    if (right <= left) {
        return;
    }
    
    i = partition(children, left, right, context);
    quicksort(children, left, i-1, context);
    quicksort(children, i+1, right, context);
}

int partition(TreeNode **children, int left, int right, int context) {
    int i = left-1;
    int j = right;
    TreeNode *temp, *v = children[right];
    
    while (i < j) {
        /*printf("AQUI MESMO SENHOR AGENTE!\n");*/
        while (less(children[++i], v, context));
        /*printf("SERA DEPOIS DO PRIMEIRO WHILE?\n");*/
        while (less(v, children[--j], context)) {
           if (j == left)
                break;
        }
        if (i < j) {
            /*printf("HEEERE I AM\n");*/
            temp = children[i];
            children[i] = children[j];
            children[j] = temp;
        }
    }
    /*printf("TTTTTTTTTTTTTTTTTTTTTESTE\n");*/
    temp = children[i];
    children[i] = children[right];
    children[right] = temp;
    
    return i;
}

int less(TreeNode *a, TreeNode *b, int context) {
    /*if (a == NULL || b == NULL) {
        printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    }*/
    return (a != NULL && ((context == CREATION && instantT(a) < instantT(b)) ||
        (context == PATH && strcmp(componentT(a), componentT(b)) < 0)));
    /*return (a != NULL && ((context == CREATION && instantT(a) < instantT(b)) ||
            (context == PATH && strcmp(pathT(a), pathT(b)) < 0)));*/
}


TreeNode* traverseTree(TreeNode *h) {
    TreeNode **children;
    int i, limit;
    char *key;
    
    /*printf("traverseTree: A começar um node\n");*/
    if (h == NULL) {
        return NULL;
    }
    else if ((key = keyT(h)) != NULL) {
        printf("%s %s\n", pathT(h), keyT(h));
    }
    /*printf("traverseTree: Estamos em '%s'\n", h->value);*/
    children = nodeChildren(h);
    limit = numberChildren(h);
    /*printf("traverseTree: O seu número de filhos é '%d'\n\n", limit);*/
    quicksort(children, 0, limit - 1, CREATION);

    /*printf("traverseTree: A entrar no loop\n");*/
    for (i = 0; i < limit; ++i) {
        /*printf("traverseTree: Estamos no filho '%d'\n", i);
        printf("traverseTree: O filho atual tem como path '%s'\n", children[i]->value);*/
        h = traverseTree(children[i]);
    }

    /*printf("traverseTree: Nao encontrei nada mais neste nó\n\n");*/
    return NULL;
}

void printChildren(TreeNode *node) {
    int i, limit;
    TreeNode **children;

    /*printf("Tentativa\n");*/
    limit = numberChildren(node);
    /*printf("Erro\n");*/
    children = nodeChildren(node);
    quicksort(children, 0, limit - 1, PATH);
    for (i = 0; i < limit; ++i) {
        printf("%s\n", componentT(children[i]));
    }
}
