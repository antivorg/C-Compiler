/*
 *
 * A trivial C cross compiler written in C
 * 
 */

#include "../inc/main.h"

int main(int argc, char *argv[]) {

    // No pre-processor for now

    char* src[argc-1];

    // Read file
    for (int i=1; i<argc; i++) {
        src[i-1] = readFile(argv[i]);
    }

    #ifdef DEBUG
    //puts("File contents\n");
    //for (int i=0; i<argc-1; i++) puts(src[i]);
    #endif

    // Lexing
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

    // Parsing
    for (int k=0; k<argc-1; k++) {
        //parse(tokens[k]);
	free(tokens[k]);
    }

    return 1;
}
