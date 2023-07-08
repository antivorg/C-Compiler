
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../inc/lexing.h"

void print_token_type(token token0);

char* keywords[] = {
	"auto", "break", "case", "char", "const", "continue", "default", "do",
	"double", "else", "enum", "extern", "float", "for", "goto", "if",
	"inline", "int", "long", "register", "restrict", "return", "short",
	"signed", "sizeof", "static", "struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
	"_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
	"_Static_assert", "_Thread_local"
};

char* punctuators[] = {
	"[", "]", "(", ")", "{", "}", ".", "->", "++", "--", "&", "*", "+", "-",
       	"~", "!", "/", "%", "<<", ">>", "<", ">", "<=", ">=", "==", "!=", "^",
       	"|", "&&", "||", "?", ":", ";", "...", "=", "*=", "/=", "%=", "+=",
       	"-=", "<<=", ">>=", "&=", "^=", "|=", ",", "#", "##", "<:", ":>", "<%",
       	"%>", "%:", "%:%:"
};


int main(int argc, char *argv[]) {

	if (argc == 1) {
		return EXIT_FAILURE;
	}

	token* tokens;

	// Test keywords
	for (int i=0; i<sizeof(keywords)/sizeof(char*)-1; i++) {
		puts(keywords[i]);
		char code[strlen(keywords[i])+1];
		code[0] = strdup(keywords[i]);
		code[strlen(keywords[i])-1] = ' ';
		code[strlen(keywords[i])] = '\0';
		puts(keywords[i]);
		tokens = lexer(keywords[i], strlen(keywords[i])+1);
		if (tokens[0].type != KEYWORD) {
			printf("Erroneous token type: ");
			print_token_type(tokens[0]);
			printf("\n");
		}
	}

	//srand(time(NULL));

	return EXIT_SUCCESS;
}


void print_token_type(token token0) {

	switch(token0.type) {
		case ERROR:
			puts("ERROR");
			break;
        	case IDENTIFIER:
			puts("IDENTIFIER");
			break;
        	case KEYWORD:
			puts("KEYWORD");
			break;
		case RETURN_KEYWORD:
			puts("RETURN_KEYWORD");
			break;
		case INTEGER:
			puts("INTEGER");
			break;
		case REAL:
			puts("REAL");
			break;
        	case CHAR:
			puts("CHAR");
			break;
		case BACKSLAH_CHAR:
			puts("BACKSLAH_CHAR");
			break;
		case STRING:
			puts("STRING");
			break;
		case ASSIGNMENT:
			puts("ASSIGNMENT");
			break;
		case ADDITION:
			puts("ADDITION");
			break;
		case SUBTRACTION:
			puts("SUBTRACTION");
			break;
		case MULTIPLICATION:
			puts("MULTIPLICATION");
			break;
		case DIVISION:
			puts("DIVISION");
			break;
        	case LEFT_PAR:
			puts("LEFT_PAR");
			break;
		case RIGHT_PAR:
			puts("RIGHT_PAR");
			break;
		case LEFT_BRACE:
			puts("LEFT_BRACE");
			break;
		case RIGHT_BRACE:
			puts("RIGHT_BRACE");
			break;
		case COMMA:
			puts("COMMA");
			break;
		case SEMICOLON:
			puts("SEMICOLON");
			break;
		case FILE_END:
			puts("FILE_END");
			break;
	}
}
