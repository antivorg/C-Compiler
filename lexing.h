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

typedef enum tokenType {
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
} tokenType;

typedef struct token {
    tokenType type;
    char* value;
} token;

#endif
//

// functions
token* lexer(const char* src, int size);
int isKeyWordBool(char* name);
int isSpecialCharBool(char character);
int isOperatorBool(char character);
int isAlphabeticalBool(char character);
int isNumericalBool(char character);
//


#endif