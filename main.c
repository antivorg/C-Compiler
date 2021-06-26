/*
 *
 * A Trivial C to x86 assembly compiler written in C
 * 
 */

#include "fileHandling.h"
#include "lexing.h"

int main(int argc, char *argv[]) {

    char* src[argc-1];

    for (int i=1; i<argc; i++) {
        src[i-1] = readFile(argv[i]);
    }

    token* tokens[argc-1];

    for (int j=0; j<argc-1; j++) {
        tokens[j] = lexer(src[j], sizeof(src));
    }

    return 1;
}