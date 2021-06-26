#include <string.h>
#include <stdlib.h>

#ifndef LEXING.h
#define LEXING.h

// types
typedef enum {
    WHITE_SPACE, COMMENT, MULTI_LINE_COMMENT,
    TOKEN_COMPLETE,
    TOKEN_NUMERIC,
    TOKEN_IDENTIFIER,
} state;

#ifndef TYPE_token
#define TYPE_token
typedef struct s_token {
    typedef enum {
        ERROR,
        IDENTIFIER,
        KEYWORD, RETURN_KEYWORD,
        INTEGER, REAL,
        CHAR, BACKSLAH_CHAR, STRING,
        STRING,
        ASSIGNMENT,
        ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION,
        LEFT_PAR, RIGHT_PAR, LEFT_BRACE, RIGHT_BRACE,
        COMMA, SEMICOLON, 
    } type;
    char* value;
    struct s_token* next;
} token;
#endif
//

// functions
token lexer(const char* src, int size);
static int isKeyWordBool(char* name);
static int isSpecialCharBool(char character);
static int isOperatorBool(char* character);
//

token lexer(const char* src, int size) {

    state currentState = WHITE_SPACE;
    token baseToken;
    int tokenNum = 0;

    for (int i=0; i<size; i++) {

        switch (currentState) {
            case WHITE_SPACE:
                if (src[i]=='/' && src[i+1]=='/') {
                    currentState = COMMENT;
                    i++;
                } else if (src[i]=='/' && src[i+1]=='*') {
                    currentState = MULTI_LINE_COMMENT;
                    i++;
                } else if (isSpecialCharBool(src[i])) {
                    currentState = TOKEN_COMPLETE;
                } else if (isOperatorBool(src[i])) {
                    currentState = TOKEN_COMPLETE;
                }
                break;
            case TOKEN_IDENTIFIER:
                break;
            case TOKEN_NUMERIC:
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


#endif