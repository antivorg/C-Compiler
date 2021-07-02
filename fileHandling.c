#include "fileHandling.h"


char* readFile(char filename[]) {

    FILE *filePointer;
    filePointer = fopen(filename, "rb");

    fseek(filePointer, 0, SEEK_END);
    int bufferSize = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);

    char *buffer = malloc(bufferSize + 1);
    fread(buffer, 1, bufferSize, filePointer);
    buffer[bufferSize] = '\0';

    fclose(filePointer);

    return buffer;

}