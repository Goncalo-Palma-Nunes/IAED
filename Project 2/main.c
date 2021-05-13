/*
 * File: main.c
 * Author: Gonçalo Palma Ribeiro Graça Nunes
 * Description: Main file for a file system, for the second project in the
 * 2020/2021 IAED class
*/

#include <stdio.h>

#define INSTRUCTION_SIZE 65535
#define TRUE 1
#define FALSE 0
#define NO_SPACES 1
#define SPACES -1

void read_input(char *instruction, int context);
int space(char c);

int main() {
    char instruction[INSTRUCTION_SIZE];

    read_input(instruction, SPACES);
    printf("%s\n", instruction);

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
