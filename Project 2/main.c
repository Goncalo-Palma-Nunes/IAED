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
#include "hash_table.h"                             /* Estou com stack overflow */

#define ROOT_SIZE 2                                 /* Parece crashar ao segundo set */
#define INSTRUCTION_SIZE 65536                      /* Ao acrescentar / tambem causa uns erros */
#define TRUE 1                                      /* Passar a parte do input do find para uma auxiliar para ficar bonito */
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
#define LIST_DESCRIPTION "Lista todos os componentes de um caminho."
#define SEARCH_DESCRIPTION "Procura o caminho dado um valor."
#define DELETE_DESCRIPTION "Apaga um caminho e todos os subcaminhos."
#define NUMBER_OF_COMMANDS 8
#define SLASH "/"
#define START_WITH_SLASH 1
#define DELIMITER '/'

TreeNode* createRoot(TreeNode **table);
int read_input(char *instruction, int context, int first_char);
int space(char c);
void execute_command(char *instruction, TreeNode **table, TreeNode *root);
void help_command();
void set(char *path, int size, TreeNode **table, TreeNode *root);
void print(TreeNode *root);
void find(TreeNode **table, char *instruction);


int main() {
    char instruction[INSTRUCTION_SIZE];
    TreeNode *root, **table = STinit();
    
    root = createRoot(table);
    read_input(instruction, NO_SPACES, FALSE);
    printf("%s\n", instruction);

    while (strcmp(instruction, QUIT)) {

        execute_command(instruction, table, root);
        read_input(instruction, NO_SPACES, FALSE);
    }

    free(table);
    delete(root);
    return 0;
}



/* Creates the root of the file system and inserts it onto a hash table.
 * Returns a pointer to the newly created root */
TreeNode* createRoot(TreeNode **table) {
    TreeNode *root, *tree;
    char *path = (char *) malloc(sizeof(char) * ROOT_SIZE);
    strcpy(path, SLASH);

    tree = Treeinit();
    root = insert(tree, path, 0, 2);
    STinsert(root, table);

    return root;
}

/* Reads from input and stores what is read on instruction. This function
 * ignores leading white spaces on the input. If context is passed as NO_SPACES
 * then the string terminates when a white space and all cases of consecutive
 * '/' chars are turned into a single one. If SPACES is passed, the 
 * aforementioned restrictions don't apply */
int read_input(char *instruction, int context, int first_char) {
    /*int i = 0;*/
    int i = (first_char == START_WITH_SLASH) ? TRUE : FALSE; /* if first char*/
    char c, last_char;                                       /* should be / */

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

    return i;
}


/* Sees if a character is a white space, tab or newline character and returns
 * an integer other than 0, if that is the case */
int space(char c) {
    return c == '\t' || c == ' ' || c == '\n';
}


/* Receives a command from an instruction and checks which command it is */
void execute_command(char *instruction, TreeNode **table, TreeNode *root) {
    int size;

    if (!strcmp(instruction, HELP)) {
        help_command();
    }
    else if (!strcmp(instruction, SET)) {
        size = read_input(instruction, NO_SPACES, FALSE);
        set(instruction, size, table, root);
    }
    else if (!strcmp(instruction, PRINT)) {
        printf("Execute Command: Entrou no branch do print\n");
        print(root);
    }
    else if (!strcmp(instruction, FIND)) {
        find(table, instruction);
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
    char *token, *str = (char *) malloc(sizeof(char) * size);
    TreeNode *current, *parent = root;
    static int instant = 0;

    token = strtok(path, SLASH);
    /*printf("O primeiro token é '%s'\n", token);*/
    /*printf("O numero de filhos de root eh '%d'\n", numberChildren(root));*/

    str[0] = '/'; str[1] = '\0';
    while (token != NULL) {
        /*printf("PAI ANTES DA CONCATENACAO '%s'\n", parent->value);*/
        strcat(str, token);
        /*printf("Mission accomplished\n");*/
        strcat(str, SLASH);
        /*printf("PAI ANTES DA PROCURA '%s'\n", parent->value);*/
        current = STsearch(str, table); /* Check for path on hash table */
        /*printf("PAI DEPOIS DO SEARCH '%s'\n", parent->value);*/
        /*printf("Depois de procurar na hash table\n");
        printf("A string atualmente eh '%s'\n", str);*/
        if (current == NULL) { /* If no such path exists yet */
            /*printf("O pai deste eh '%s'\n", parent->value);*/
            /*new = NewTN(str, instant);*/
            /*printf("Esta a tentar criar um novo\n");*/
            current = insert(parent, str, instant, size); /* Insert new path on the tree */
            /*printf("Conseguiu criar o novo node\n");*/
            STinsert(current, table);               /* and on the hash table */
            /*printf("Conseguiu inseri-o na hash table\n");*/
            instant++;
        }
        token = strtok(NULL, SLASH);
        /*strcat(str, SLASH);*/
        /*printf("Conseguiu fazer o append, agora eh '%s'\n", str);*/
        parent = current;
    }
    /*printf("We did it folks. Pack it up\n");*/
    size = read_input(path, SPACES, FALSE);
    /*printf("Vamos lá inserir-lhe a key '%s'\n", path);*/
    changeKey(current, path, size); /* Updates or creates the path's key */

    /*printf("O new tem como path '%s' e tem de valor '%s'\n", new->value, new->key);
    printf("O numero de filhos da root eh '%d'\n", numberChildren(root));*/
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
    int length;

    path[0] = DELIMITER;
    length = read_input(path, NO_SPACES, START_WITH_SLASH);
    if (length > 2) {
        path[length++] = DELIMITER;     /* Place a forward slash at the start */
        path[length] = '\0';            /* and the end of the path */
    }
    else {
        path[1] = '\0';
    }
    node = STsearch(path, table);

    if (node == NULL) {
        printf("not found\n");
    }
    else if (keyT(node) == NULL) {
        printf("no data\n");
    }
    else {
        printf("%s\n", keyT(node));
    }
}
