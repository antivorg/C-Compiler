#include "headers/lexing.h"

token* lexer(char* src, int size) {

    state currentState = WHITE_SPACE;
    token* tokens = (token*) malloc(0);

    int tokenNum = 0, valueIndex = 0, isFloatBool = 0;

    for (int i=0; i<size; i++) {

        switch (currentState) {

            case TOKEN_COMPLETE:
            case WHITE_SPACE:
                if (src[i]==' ') {
                    currentState = WHITE_SPACE;
                } else if (src[i]=='\r' && src[i+1]=='\n') {
                    currentState = WHITE_SPACE;
                    i++;
                } else if (src[i]=='/' && src[i+1]=='/') {
                    currentState = COMMENT;
                    i++;
                } else if (src[i]=='/' && src[i+1]=='*') {
                    currentState = MULTI_LINE_COMMENT;
                    i++;
                } else if (isSpecialCharBool(src[i])) {
                    currentState = TOKEN_COMPLETE;
                    tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                    tokens[tokenNum].value = malloc(sizeof(char));
                    tokens[tokenNum].value[0] = src[i];
                    tokens[tokenNum].type = findTokenType(src[i]);
                    tokenNum++;
                } else if (isOperatorBool(src[i])) {
                    currentState = TOKEN_COMPLETE;
                    tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                    tokens[tokenNum].value = malloc(sizeof(char));
                    tokens[tokenNum].value[0] = src[i];
                    tokens[tokenNum].type = findTokenType(src[i]);
                    tokenNum++;
                } else if (isNumericalBool(src[i])) {
                    currentState = TOKEN_NUMERIC;
                    tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                    tokens[tokenNum].value = malloc(sizeof(char));
                    tokens[tokenNum].value[0] = src[i];
                } else if (isAlphabeticalBool(src[i])) {
                    currentState = TOKEN_IDENTIFIER;
                    tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                    tokens[tokenNum].value = malloc(sizeof(char));
                    tokens[tokenNum].value[0] = src[i];
                }
                break;

            case TOKEN_IDENTIFIER:
                if (isAlphabeticalBool(src[i]) || isNumericalBool(src[i])) {
                    tokens[tokenNum].value = realloc(tokens[tokenNum].value,
                                                    sizeof(tokens[tokenNum].value)+sizeof(char));
                    tokens[tokenNum].value[++valueIndex] = src[i];
                } else {
                    tokens[tokenNum].value[++valueIndex] = '\0';
                    if (!strcmp(tokens[tokenNum].value, "return")) {
                        tokens[tokenNum].type = RETURN_KEYWORD;
                    } else if (isKeyWordBool(tokens[tokenNum].value)) {
                        tokens[tokenNum].type = KEYWORD;
                    } else {
                        tokens[tokenNum].type = IDENTIFIER;
                    }
                    valueIndex = 0;
                    tokenNum++;
                    if (src[i]==' ') {
                        currentState = WHITE_SPACE;
                    } else if (src[i]=='\r' && src[i+1]=='\n') {
                        currentState = WHITE_SPACE;
                        i++;
                    } else if (src[i]=='/' && src[i+1]=='/') {
                        currentState = COMMENT;
                        i++;
                    } else if (src[i]=='/' && src[i+1]=='*') {
                        currentState = MULTI_LINE_COMMENT;
                        i++;
                    } else if (isSpecialCharBool(src[i])) {
                        currentState = TOKEN_COMPLETE;
                        tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                        tokens[tokenNum].value = malloc(sizeof(char));
                        tokens[tokenNum].value[0] = src[i];
                        tokens[tokenNum].type = findTokenType(src[i]);
                        tokenNum++;
                    } else if (isOperatorBool(src[i])) {
                        currentState = TOKEN_COMPLETE;
                        tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                        tokens[tokenNum].value = malloc(sizeof(char));
                        tokens[tokenNum].value[0] = src[i];
                        tokens[tokenNum].type = findTokenType(src[i]);
                        tokenNum++;
                    } else if (isNumericalBool(src[i])) {
                        currentState = TOKEN_NUMERIC;
                        tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                        tokens[tokenNum].value = malloc(sizeof(char));
                        tokens[tokenNum].value[0] = src[i];
                    } 
                }
                break;

            case TOKEN_NUMERIC:
                if (isNumericalBool(src[i])) {
                    tokens[tokenNum].value = realloc(tokens[tokenNum].value,
                                                    sizeof(tokens[tokenNum].value)+sizeof(char));
                    tokens[tokenNum].value[++valueIndex] = src[i];
                } else if (src[i]=='.') {
                    isFloatBool = 1;
                    tokens[tokenNum].value = realloc(tokens[tokenNum].value,
                                                    sizeof(tokens[tokenNum].value)+sizeof(char));
                    tokens[tokenNum].value[++valueIndex] = src[i];
                } else {
                    tokens[tokenNum].value[++valueIndex] = '\0';
                    if (isFloatBool) {
                        tokens[tokenNum].type = REAL;
                    } else {
                        tokens[tokenNum].type = INTEGER;
                    }
                    valueIndex = 0;
                    tokenNum++;
                    if (src[i]==' ') {
                        currentState = WHITE_SPACE;
                    } else if (src[i]=='\r' && src[i+1]=='\n') {
                        currentState = WHITE_SPACE;
                        i++;
                    } else if (src[i]=='/' && src[i+1]=='/') {
                        currentState = COMMENT;
                        i++;
                    } else if (src[i]=='/' && src[i+1]=='*') {
                        currentState = MULTI_LINE_COMMENT;
                        i++;
                    } else if (isSpecialCharBool(src[i])) {
                        currentState = TOKEN_COMPLETE;
                        tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                        tokens[tokenNum].value = malloc(sizeof(char));
                        tokens[tokenNum].value[0] = src[i];
                        tokens[tokenNum].type = findTokenType(src[i]);
                        tokenNum++;
                    } else if (isOperatorBool(src[i])) {
                        currentState = TOKEN_COMPLETE;
                        tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                        tokens[tokenNum].value = malloc(sizeof(char));
                        tokens[tokenNum].value[0] = src[i];
                        tokens[tokenNum].type = findTokenType(src[i]);
                        tokenNum++;
                    } else if (isAlphabeticalBool(src[i])) {
                        currentState = TOKEN_IDENTIFIER;
                        tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
                        tokens[tokenNum].value = malloc(sizeof(char));
                        tokens[tokenNum].value[0] = src[i];
                    }
                }
                break;
            case COMMENT:

                if (src[i]=='\r' && src[i]=='\n') {
                    currentState = WHITE_SPACE;
                    i++;
                }
                break;

            case MULTI_LINE_COMMENT:
                if (src[i]=='*' && src[i]=='/') {
                    currentState = WHITE_SPACE;
                    i++;
                }
                break;
            }
    }
    tokens = realloc(tokens, sizeof(tokens)+sizeof(token));
    tokens[tokenNum].type = FILE_END;

    return tokens;
}

static int isKeyWordBool(char* name) {

    const char* keywords[] = {
        "int", "double", "char", "void"
    };
    for (int i=0; i<sizeof(keywords)/sizeof(const char*); i++) {
        if (!strcmp(keywords[i], name)) {
            return 1;
        }
    }
    return 0;
}

static int isSpecialCharBool(char character) {

    const char specialChars[] = {
        ';', '(', ')', '{', '}', ',', ';'
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

    if (character <= '9' && character >= '0') {
        return 1;
    } else {
        return 0;
    }
}

static tokenType findTokenType(char character) {

    switch(character) {
        case '=':
            return ASSIGNMENT;
        case '+':
            return ADDITION;
        case '-':
            return SUBTRACTION;
        case '*':
            return MULTIPLICATION;
        case '/':
            return DIVISION;
        case '{':
            return LEFT_PAR;
        case '}':
            return RIGHT_PAR;
        case '(':
            return LEFT_BRACE;
        case ')':
            return RIGHT_BRACE;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        deafult:
            return ERROR;
    }
}