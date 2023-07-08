#include <string.h>

#ifndef PARSING
#define PARSING

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

#ifndef ast_t
#define ast_t

typedef struct leaf {
    leafType type;
    union {
        char* value;
        struct {
            leaf* left;
            leaf* right;
        } subLeafs;
    } contense;
} leaf;

typedef enum leafType {
    CODE, FUNCTION_HEADER,
    TYPE_INT, TYPE_FLOAT, TYPE_CHAR,
    NAME,
    PARENTHESIS,
    TREE_END
} leafType;

#endif

leaf* parse(token* tokens);
code(token* tokens, leaf* parseTree);
functionHeader(token* tokens, leaf* parseTree);
type(token* tokens, leaf* parseTree);
arguments(token* tokens, leaf* parseTree);
codeBlock(token* tokens, leaf* parseTree);

#endif