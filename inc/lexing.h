#include <string.h>
#include <stdlib.h>

#ifndef LEXING
#define LEXING

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
        ASSIGNMENT,
        ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION,
        LEFT_PAR, RIGHT_PAR, LEFT_BRACE, RIGHT_BRACE,
        COMMA, SEMICOLON, FILE_END
} tokenType;

typedef struct token {
    tokenType type;
    char* value;
} token;

#endif

token* lexer(char* src, int size);
static int isKeyWordBool(char* name);
static int isSpecialCharBool(char character);
static int isOperatorBool(char character);
static int isAlphabeticalBool(char character);
static int isNumericalBool(char character);
static tokenType findTokenType(char character);

#endif
