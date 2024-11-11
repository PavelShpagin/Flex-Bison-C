#ifndef ASTNODE_H
#define ASTNODE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ASTNode
{
    char type;
    union
    {
        int value;
        struct
        {
            char op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;
        struct
        {
            char op;
            struct ASTNode *operand;
        } unary;
    } data;
} ASTNode;

ASTNode *createNumberNode(int value);
ASTNode *createBinaryOpNode(char op, ASTNode *left, ASTNode *right);
ASTNode *createUnaryOpNode(char op, ASTNode *operand);
int evaluate(ASTNode *node);
void printASTJSONToFile(FILE *file, ASTNode *node);

#endif
