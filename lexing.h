#include <string.h>
#include <stdlib.h>

#ifndef LEXING.h
#define LEXING.h

// types
typedef enum state {
    WHITE_SPACE, COMMENT, MULTI_LINE_COMMENT,
    TOKEN_COMPLETE,
    TOKEN_NUMERIC,
    TOKEN_IDENTIFIER,
} state;

#ifndef token_t
#define token_t

typedef enum type {
        ERROR,
        IDENTIFIER,
        KEYWORD, RETURN_KEYWORD,
        INTEGER, REAL,
        CHAR, BACKSLAH_CHAR, STRING,
        STRING,
        ASSIGNMENT,
        ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION,
        LEFT_PAR, RIGHT_PAR, LEFT_BRACE, RIGHT_BRACE,
        COMMA, SEMICOLON
} type;

typedef struct token {
    type tokenType;
    char* tokenValue;
} token;

#endif
//

// functions
token* lexer(const char* src, int size);
static int isKeyWordBool(char* name);
static int isSpecialCharBool(char character);
static int isOperatorBool(char character);
static int isAlphabeticalBool(char character);
static int isNumericalBool(char character);
//

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
                        tokens[tokenNum].tokenType = RETURN_KEYWORD;
                    } else if (isKeyWordBool(tokenValue)) {
                        tokens[tokenNum].tokenType = KEYWORD;
                    } else {
                        tokens[tokenNum].tokenType = IDENTIFIER;
                    }

                    tokens[tokenNum].tokenValue = tokenValue;

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
                if (isAlphabeticalBool(src[i])) {
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

#endif