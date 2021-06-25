/*
 *
 * A Trivial C to x86 assembly compiler written in C
 * 
 */

#include "fileHandling.h"
#include "lexing.h"

int main(int argc, char *argv[]) {

    char* sourceCode[argc-1];

    for (int i=1; i<argc; i++) {
        sourceCode[i-1] = readFile(argv[i]);
    }

    return 1;
}