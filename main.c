/*
 *
 * A trivial C to x86 assembly compiler written in C
 * 
 */

#include "headers/main.h"

int main(int argc, char *argv[]) {

    char* src[argc-1];

    for (int i=1; i<argc; i++) {
        src[i-1] = readFile(argv[i]);
    }

    #ifdef DEBUG
    for (int i=0; i<argc-1; i++) puts(src[i]);
    #endif

    token* tokens[argc-1];

    for (int j=0; j<argc-1; j++) {
        tokens[j] = lexer(src[j], strlen(src[j]));
    }

    #ifdef DEBUG
    for (int i=0; i<argc-1; i++) {
        int j=0;
        while (tokens[i][j].type != FILE_END) {
            if (tokens[i][j].type == REAL || tokens[i][j].type == INTEGER ||
                tokens[i][j].type == IDENTIFIER || tokens[i][j].type == KEYWORD ||
                tokens[i][j].type == RETURN_KEYWORD) {
                puts(tokens[i][j].value);
            } else {
                printf("%c\n", *tokens[i][j].value);
            }
            j++;
        }
    }
    #endif

    return 1;
}