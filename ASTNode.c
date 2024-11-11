#include <stdio.h>
#include <stdlib.h>
#include "ASTNode.h"

ASTNode *createNumberNode(int value)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = 'N';
    node->data.value = value;
    return node;
}

ASTNode *createBinaryOpNode(char op, ASTNode *left, ASTNode *right)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = 'B';
    node->data.binary.op = op;
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}

ASTNode *createUnaryOpNode(char op, ASTNode *operand)
{
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = 'U';
    node->data.unary.op = op;
    node->data.unary.operand = operand;
    return node;
}

int evaluate(ASTNode *node)
{
    if (node->type == 'N')
    {
        return node->data.value;
    }
    else if (node->type == 'B')
    {
        int left = evaluate(node->data.binary.left);
        int right = evaluate(node->data.binary.right);
        switch (node->data.binary.op)
        {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right != 0)
                return left / right;
            else
            {
                fprintf(stderr, "Error: Division by zero.\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Error: Unknown binary operator '%c'.\n", node->data.binary.op);
            exit(EXIT_FAILURE);
        }
    }
    else if (node->type == 'U')
    {
        int operand = evaluate(node->data.unary.operand);
        switch (node->data.unary.op)
        {
        case '+':
            return operand;
        case '-':
            return -operand;
        default:
            fprintf(stderr, "Error: Unknown unary operator '%c'.\n", node->data.unary.op);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "Error: Unknown node type '%c'.\n", node->type);
        exit(EXIT_FAILURE);
    }
}

void printASTJSONToFile(FILE *file, ASTNode *node)
{
    if (node->type == 'N')
    {
        fprintf(file, "{\"type\":\"Number\",\"value\":%d}", node->data.value);
    }
    else if (node->type == 'B')
    {
        fprintf(file, "{\"type\":\"BinaryOp\",\"op\":\"%c\",\"left\":", node->data.binary.op);
        printASTJSONToFile(file, node->data.binary.left);
        fprintf(file, ",\"right\":");
        printASTJSONToFile(file, node->data.binary.right);
        fprintf(file, "}");
    }
    else if (node->type == 'U')
    {
        fprintf(file, "{\"type\":\"UnaryOp\",\"op\":\"%c\",\"operand\":", node->data.unary.op);
        printASTJSONToFile(file, node->data.unary.operand);
        fprintf(file, "}");
    }
    else
    {
        fprintf(stderr, "Error: Unknown node type '%c'.\n", node->type);
        exit(EXIT_FAILURE);
    }
}