/*
 * File: main.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Main file for a file system, for the second project in the
 * 2020/2021 IAED class
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search_tree.h"
#include "hash_table.h"

#define ROOT_SIZE 2
#define INSTRUCTION_SIZE 65536
#define TRUE 1
#define FALSE 0
#define NO_SPACES 1
#define SPACES -1                   
#define QUIT "quit"
#define HELP "help"
#define SET "set"
#define PRINT "print"
#define LIST "list"
#define FIND "find"
#define SEARCH "search"
#define DELETE "delete"
#define HELP_DESCRIPTION "Imprime os comandos disponíveis."
#define QUIT_DESCRIPTION "Termina o programa."
#define SET_DESCRIPTION "Adiciona ou modifica o valor a armazenar."
#define PRINT_DESCRIPTION "Imprime todos os caminhos e valores."
#define FIND_DESCRIPTION "Imprime o valor armazenado."
#define LIST_DESCRIPTION "Lista todos os componentes imediatos de um sub-caminho."
#define SEARCH_DESCRIPTION "Procura o caminho dado um valor."
#define DELETE_DESCRIPTION "Apaga um caminho e todos os subcaminhos."
#define NUMBER_OF_COMMANDS 8
#define SLASH "/"
#define SLASH_SIZE 1
#define DELIMITER '/'
#define LAST_CHAR 2
#define NOT_FOUND "not found\n"
#define NO_DATA "no data\n"

TreeNode* createRoot(TreeNode **table);
int read_input(char *instruction, int context, char *terminal_char);
int space(char c);
void execute_command(char *instruction, TreeNode **table, TreeNode *root,
                    char *terminal_char);
void help_command();
void set(char *path, int size, TreeNode **table, TreeNode *root);
void print(TreeNode *root);
void find(TreeNode **table, char *instruction);
void list(char *path, TreeNode **table);
void search(char *key, TreeNode *root);
void delete(TreeNode **table, TreeNode *root, char *input, char *terminal_char);

int main() {
    char instruction[INSTRUCTION_SIZE];
    char *last_char = (char *) malloc(sizeof(char) * LAST_CHAR);
    TreeNode *root, **table = STinit();
    
    root = createRoot(table);
    read_input(instruction, NO_SPACES, last_char);

    while (strcmp(instruction, QUIT)) {

        execute_command(instruction, table, root, last_char);
        read_input(instruction, NO_SPACES, last_char);
    }
    free(table);
    deleteT(root, root);

    return 0;
}



/* Creates the root of the file system and inserts it onto a hash table.
 * Returns a pointer to the newly created root */
TreeNode* createRoot(TreeNode **table) {
    TreeNode *root, *tree;
    char *path = (char *) malloc(sizeof(char) * ROOT_SIZE);
    strcpy(path, SLASH);

    tree = Treeinit();
    root = insert(tree, path, 0, 2, SLASH);
    STinsert(root, table);

    return root;
}

/* Reads from input and stores what is read on instruction. This function
 * ignores leading white spaces on the input. If context is passed as NO_SPACES
 * then the string terminates when a white space and all cases of consecutive
 * '/' chars are turned into a single one. If SPACES is passed, the 
 * aforementioned restrictions don't apply */
int read_input(char *instruction, int context, char *terminal_char) {
    int i = 0;
    char c, last_char;

    while (space(c = getchar())); /* Ignores leading white spaces */
    instruction[i++] = c;
    last_char = c;

    while ((c = getchar()) && ((context == NO_SPACES && !space(c)) ||
            (context == SPACES)) && c != EOF && c != '\n') {
    
        if (!space(c) && (c != '/' || (c == '/' && last_char != '/'))) {
            /* Ignores consecutive '/' chars, storing only the first found
             * on an uninterrupted sequence */

             instruction[i++] = c;
        }
        else if (context == SPACES) { /* Allows storage of consecutive '/' chars */
            instruction[i++] = c;     /* and white spaces on the string */
        }
        last_char = c;
    }
    instruction[i] = '\0';
    if (terminal_char != NULL) terminal_char[0] = c;

    return i;
}


/* Sees if a character is a white space, tab or newline character and returns
 * an integer other than 0, if that is the case */
int space(char c) {
    return c == '\t' || c == ' ' || c == '\n';
}


/* Receives a command from an instruction and checks which command it is */
void execute_command(char *instruction, TreeNode **table, TreeNode *root,
                    char *terminal_char) {
    int size;

    if (!strcmp(instruction, HELP)) {
        help_command();
    }
    else if (!strcmp(instruction, SET)) {
        size = read_input(instruction, NO_SPACES, NULL);
        set(instruction, size, table, root);
    }
    else if (!strcmp(instruction, PRINT)) {
        print(root);
    }
    else if (!strcmp(instruction, FIND)) {
        find(table, instruction);
    }
    else if (!strcmp(instruction, LIST)) {
        list(terminal_char, table);
    }
    else if (!strcmp(instruction, SEARCH)) {
        search(instruction, root);
    }
    else if (!strcmp(instruction, DELETE)) {
        delete(table, root, instruction, terminal_char);
    }
}

/* Prints a description of all commands */
void help_command() {
    char* descriptions[] = { HELP_DESCRIPTION, QUIT_DESCRIPTION, SET_DESCRIPTION,
                PRINT_DESCRIPTION, FIND_DESCRIPTION, LIST_DESCRIPTION,
                SEARCH_DESCRIPTION, DELETE_DESCRIPTION };
    char* commands[] = { HELP, QUIT, SET, PRINT, FIND, LIST, SEARCH, DELETE };

    int i;

    for (i = 0; i < NUMBER_OF_COMMANDS; i++) {
        printf("%s: %s\n", commands[i], descriptions[i]);
    }
}

/* Receives a path and a key value. If the path already exists, its key value
 * is update, otherwise the path is created */
void set(char *path, int size, TreeNode **table, TreeNode *root) {
    char *token, *str = (char *) malloc(sizeof(char) * (size + 3));
    TreeNode *current, *parent = root;
    static int instant = 1;

    token = strtok(path, SLASH);

    str[0] = '/'; str[1] = '\0';
    while (token != NULL) {
        strcat(str, token);

        current = STsearch(str, table);
        if (current == NULL) {
        /* Check for path on hash table, if no such path exists yet */
        /*  Insert new path on the tree and on the hash table */
            current = insert(parent, str, instant, size, token);
            STinsert(current, table);
            instant++;
        }
        token = strtok(NULL, SLASH);
        strcat(str, SLASH);
        parent = current;
    }
    size = read_input(path, SPACES, NULL);
    changeKey(current, path, size); /* Updates or creates the path's key */
}

/* Reads a string from input. If the input doesn't begin with a forward slash,
 * one is added at the start of the string, otherwise the input suffers no
 * changes. The treated output is pointed at by char *path */
void treat_input(char *path, char *input) {
    int length;

    length = read_input(input, NO_SPACES, NULL);
    if (input[0] != DELIMITER) { /* If it doesn't start with a forward slash */
        path = (char *) realloc(path, length + 2);
        path[0] = DELIMITER;
        path[1] = '\0';
        strcat(path,input);
    }
    else {
        path = input;
    }
}


/* Receives a pointer to the root directory of the file system. Traverses the
 * tree, printing all paths with a key value, by depth and order of creation */
void print(TreeNode *root) {
    traverseTree(root);

}

/* Reads a path from input and checks if the path already exists. If it does
 * and it has a key value, that value is printed, otherwise an error is raised */
void find(TreeNode **table, char *path) {
    TreeNode *node;
    char *str = (char *) malloc(sizeof(char));

    treat_input(str, path);
    node = STsearch(str, table);

    if (node == NULL) {
        printf("%s", NOT_FOUND);
    }
    else if (keyT(node) == NULL) {
        printf("%s", NO_DATA);
    }
    else {
        printf("%s\n", keyT(node));
    }
    if (str != path) {
        free(str);
    }
}

/* Reads a path from input and checks if it exists. If it does, the components
 * for all of its immediate sub-directories are printed, otherwise an error is
 * raised */
void list(char *path, TreeNode **table) {
    TreeNode *node;
    int length;
    char *str;

    if (path[0] == '\n') {  /* If no arguments were provided */
        str = (char *) malloc(sizeof(char) * (SLASH_SIZE + 1));
        strcpy(str, SLASH);
    }
    else {
        length = read_input(path, NO_SPACES, NULL);
        if (path[0] != DELIMITER) {
            str = (char *) malloc(sizeof(char) * (length + 2));
            str[0] = DELIMITER;
            str[1] = '\0';
            strcat(str,path);
        }
        else {
            str = path;
        }
    }
    node = STsearch(str, table);
    if (node == NULL) {
        printf("%s", NOT_FOUND);
        return;
    }
    printChildren(node);
    if (str != path) free(str);
}

/* Reads a key value from input and searches for the first path with that
 * key. If none is found, an error is raised */
void search(char *key, TreeNode *root) {
    TreeNode *node;

    read_input(key, SPACES, NULL);
    node = searchT(root, key, KEY);

    if (node != NULL) {
        printf("%s\n", pathT(node));
    }
    else {
        printf("%s", NOT_FOUND);
    }
}

/* Reads a path from input. If the path already exists, the path and all of its
 * sub-directories are deleted (the memory allocated for each path and its
 * components is freed), otherwise an error is raised */
void delete(TreeNode **table, TreeNode *root, char *input, char *terminal_char) {
    TreeNode *node;
    char *path = (char *) malloc(sizeof(char));

    if (terminal_char[0] == '\n') { /* If no arguments were provided */
        deleteT(root, root);
        return;
    }
    else {
        treat_input(path, input);
    }
    node = STsearch(path, table);
    STdelete(path, table);
    if (node == NULL) {
        printf("%s", NOT_FOUND);
    }
    else {
        deleteT(node, root);
    }
}
