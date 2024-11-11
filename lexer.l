%{
#include "ASTNode.h"
#include "parser.tab.h"
#include <stdlib.h>
%}

%option noyywrap

%%

[0-9]+      { yylval.num = atoi(yytext); return NUMBER; }
[ \t]+      { /* ignore whitespace */ }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }
"("         { return LPAREN; }
")"         { return RPAREN; }
\n          { return '\n'; }
.           { printf("Unknown character: %s\n", yytext); }

%%
