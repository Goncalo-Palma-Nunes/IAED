/*
 * File: main.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Main file for a file system, for the second project in the
 * 2020/2021 IAED class
*/

#include <stdio.h>
#include <string.h>

#define INSTRUCTION_SIZE 65535
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
#define LIST_DESCRIPTION "Lista todos os componentes de um caminho."
#define SEARCH_DESCRIPTION "Procura o caminho dado um valor."
#define DELETE_DESCRIPTION "Apaga um caminho e todos os subcaminhos."
#define NUMBER_OF_COMMANDS 8

void read_input(char *instruction, int context);
int space(char c);
void execute_command(char *instruction);
void help_command();

int main() {
    char instruction[INSTRUCTION_SIZE];

    read_input(instruction, SPACES);
    printf("%s\n", instruction);

    while (strcmp(instruction, QUIT)) {

        execute_command(instruction);
        read_input(instruction, SPACES);
    }

    return 0;
}


void read_input(char *instruction, int context) {
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
}

/* Returns an integer other than 0 if there is still valid input, with regards
 * to the arguments each command receives, or 0 if there is no valid input to
 * store anymore. Uses the argument "context" to read input differently for
 * the set and search commands */ 
/*int valid_input(char c, int in_word, int context) {
    return (context == NO_SPACES && (!space(c) || in_word == FALSE)) ||
        (context == SPACES && in_word);
}*/

/* Sees if a character is a white space, tab or newline character and returns
 * an integer other than 0, if that is the case */
int space(char c) {
    return c == '\t' || c == ' ' || c == '\n';
}


void execute_command(char *instruction) {
    if (!strcmp(instruction, HELP)) {
        help_command();
    }
}

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
