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

    token* tokens[argc-1];

    for (int j=0; j<argc-1; j++) {
        tokens[j] = lexer(src[j], sizeof(src));
    }

    for (int i=0; i<argc-1; i++) {
        for (int j=0; j<10; j++) {
            puts(tokens[i]->value);
            tokens[i]++;
        }
    }

    return 1;
}