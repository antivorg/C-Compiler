#include "lexing.h"

token* lexer(const char* src, int size) {

    state currentState = WHITE_SPACE;
    token* tokens = (token*) malloc(sizeof(token*));

    char* tokenValue = (char*) malloc(sizeof(char));
    tokenValue[0] = '\0';

    char buff[2] = "\0";
    int tokenNum = 0;

    for (int i=0; i<size; i++) {

        switch (currentState) {
            case WHITE_SPACE:
                if (src[i]=='/' && src[i+1]=='/') {//is comment
                    currentState = COMMENT;
                    i++;
                } else if (src[i]=='/' && src[i+1]=='*') {//is comment
                    currentState = MULTI_LINE_COMMENT;
                    i++;
                } else if (isSpecialCharBool(src[i])) {//is a new spec char token
                    currentState = TOKEN_COMPLETE;
                } else if (isOperatorBool(src[i])) {//is a new operator token
                    currentState = TOKEN_COMPLETE;
                } else if (isNumericalBool(src[i])) {//is a neumeric
                    currentState = TOKEN_NUMERIC;
                } else if (isAlphabeticalBool(src[i])) {//is an identifier
                    currentState = TOKEN_IDENTIFIER;
                }
                break;

            case TOKEN_IDENTIFIER:
                if (isAlphabeticalBool(src[i]) || isNumericalBool(src[i])) {
                    tokenValue = (char*) realloc(tokenValue, sizeof(tokenValue)+sizeof(char));
                    buff[0] = src[i];
                    tokenValue = strcat(tokenValue, buff);
                } else {
                    tokens = (token*) realloc(tokens, sizeof(tokens)+sizeof(token));
                    if (strcmp(tokenValue, "return")) {
                        tokens[tokenNum].type = RETURN_KEYWORD;
                    } else if (isKeyWordBool(tokenValue)) {
                        tokens[tokenNum].type = KEYWORD;
                    } else {
                        tokens[tokenNum].type = IDENTIFIER;
                    }

                    tokens[tokenNum].value = tokenValue;

                    tokenValue = (char*) realloc(tokenValue, sizeof(char));
                    tokenValue[0] = '\0';

                    if (src[i]=='/' && src[i+1]=='/') {//is comment
                        currentState = COMMENT;
                        i++;
                    } else if (src[i]=='/' && src[i+1]=='*') {//is comment
                        currentState = MULTI_LINE_COMMENT;
                        i++;
                    } else if (isSpecialCharBool(src[i])) {//is a new spec char token
                        currentState = TOKEN_COMPLETE;
                    } else if (isOperatorBool(src[i])) {
                        currentState = TOKEN_COMPLETE;
                    }
                }
                break;

            case TOKEN_NUMERIC:
                if (isNumericalBool(src[i])) {
                    // add value
                } else if (src[i]=='.') {
                    // it's a boy! (float)
                } //otherwise check for terminations
            case COMMENT:
                if (src[i]=='\n' && src[i]=='\r') {
                    currentState = WHITE_SPACE;
                    i++;
                    break;
                }
            case MULTI_LINE_COMMENT:
                if (src[i]=='*' && src[i]=='/') {
                    currentState = WHITE_SPACE;
                    i++;
                }
        }

    }

}

static int isKeyWordBool(char* name) {

    const char* keywords[] = {
        "int", "double", "char", "void"
    };
    for (int i=0; i<sizeof(keywords); i++) {
        if (!strcmp(keywords[i], name)) {
            return 1;
        }
    }
    return 0;
}

static int isSpecialCharBool(char character) {

    const char specialChars[] = {
        ';'
    };
    for (int i=0; i<sizeof(specialChars); i++) {
        if (specialChars[i] == character) {
            return 1;
        }
    }
    return 0;
}

static int isOperatorBool(char character) {

    const char operators[] = {
        '+', '-', '*', '/'
    };
    for (int i=0; i<sizeof(operators); i++) {
        if (operators[i] == character) {
            return 1;
        }
    }
    return 0;
}

static int isAlphabeticalBool(char character) {

    if (character >= 'a' && character <= 'z') {
        return 1;
    } else if (character >= 'A' && character <= 'Z') {
        return 1;
    } else {
        return 0;
    }
}

static int isNumericalBool(char character) {

    if (character >= '9') {
        return 1;
    } else {
        return 0;
    }
}
