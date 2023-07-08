#include "../inc/parsing.h"

leaf* parse(token* tokens) {

    leaf* parseTree;
    
    code(tokens, parseTree);

    return parseTree;
}

code(token* tokens, leaf* parseTree) {

    // <code>  ::=  <function init> <code>
    //      |  <function def> <code>
    //      |  <function def>

    // <function init>  ::=  <function header>  ";"

    // <function def>  ::=  <function header>  <code block>

    if (tokens->value == FILE_END) {
        parseTree->type = TREE_END;
    } else {
        parseTree->type = CODE;
        functionHeader(tokens, parseTree->contense.subLeafs.left);
        leaf* subLeaf1 = parseTree->contense.subLeafs.right;
        if (tokens->type == SEMICOLON) {
            subLeaf1->contense.subLeafs.left->type = SEMICOLON;
        } else if (tokens->type == LEFT_BRACE) {
            codeBlock(subLeaf1->contense.subLeafs.left->type);
        } // else raise error
        code(tokens, subLeaf1->contense.subLeafs.right);
    } // else raise error

}

functionHeader(token* tokens, leaf* parseTree) {

    // <function header>  ::=  <type>  name  "("  <arguments>  ")"

    parseTree->type = FUNCTION_HEADER;

    type(tokens, parseTree->contense.subLeafs.left);

    leaf* subLeafName = parseTree->contense.subLeafs.right->contense.subLeafs.left;
    subLeafName->type = NAME;
    subLeafName->contense.value = tokens;
    tokens++;

    leaf* subLeaf1 = parseTree->contense.subLeafs.right->contense.subLeafs.right;

    leaf* subLeafParanthesis = subLeaf1->contense.subLeafs.left;
    if (tokens->type != LEFT_PAR); // Raise error
    tokens++;
    arguments(tokens, subLeafParanthesis);
}

type(token* tokens, leaf* parseTree) {

    // <type>  ::=  int
    //      |   float
    //      |   char
    //      |   etc.


    if (strcmp(tokens->value, "int")) {
        parseTree->contense.value = TYPE_INT;
    } else if (strcmp(tokens->value, "float")) {
        parseTree->contense.value = TYPE_FLOAT;
    } else if (strcmp(tokens->value, "char")) {
        parseTree->contense.value = TYPE_CHAR;
    } // else raise error

    tokens++;
}

arguments(token* tokens, leaf* parseTree) {

    // <arguments>  ::=  <type>  name  <arguments>
    //           |   <type>  name

    if (tokens->type == RIGHT_PAR) {
        tokens++;
    } else {
        leaf* subLeafArg = parseTree->contense.subLeafs.left;
        type(tokens, subLeafArg->contense.subLeafs.left);
        subLeafArg->contense.subLeafs.right->type = NAME;
        subLeafArg->contense.subLeafs.right->contense.value = tokens;
    }

}

codeBlock(token* tokens, leaf* parseTree) {

    // <code block>  ::=  "{"  <lines>  "}"

    if (tokens->type == RIGHT_BRACE) {
        tokens++;
    } else {
        lines();
        codeBlock();
    }

}

