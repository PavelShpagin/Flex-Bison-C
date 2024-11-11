%{
#include <stdio.h>
#include <stdlib.h>
#include "ASTNode.h"

void yyerror(const char *s);
int yylex(void);
%}

%union {
    int num;
    ASTNode* node;
}

%token <num> NUMBER
%token PLUS MINUS MULTIPLY DIVIDE
%token LPAREN RPAREN
%token UMINUS UPLUS
%type <node> expr

%left PLUS MINUS
%left MULTIPLY DIVIDE
%right UMINUS UPLUS

%%

input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | expr '\n' {
        printf("Result: %d\n", evaluate($1));

        FILE *file = fopen("ast.json", "w");
        if (file) {
            printASTJSONToFile(file, $1);
            fclose(file);
            printf("AST JSON saved to ast.json\n");
        } else {
            fprintf(stderr, "Error: Could not open file to save AST JSON.\n");
        }
    }
    ;

expr:
      NUMBER {
        $$ = createNumberNode($1);
    }
    | expr PLUS expr {
        $$ = createBinaryOpNode('+', $1, $3);
    }
    | expr MINUS expr {
        $$ = createBinaryOpNode('-', $1, $3);
    }
    | expr MULTIPLY expr {
        $$ = createBinaryOpNode('*', $1, $3);
    }
    | expr DIVIDE expr {
        $$ = createBinaryOpNode('/', $1, $3);
    }
    | MINUS expr %prec UMINUS {
        $$ = createUnaryOpNode('-', $2);
    }
    | PLUS expr %prec UPLUS {
        $$ = createUnaryOpNode('+', $2);
    }
    | LPAREN expr RPAREN {
        $$ = $2;
    }
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}
