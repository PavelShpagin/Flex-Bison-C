@echo off
setlocal
del /f /q parser.tab.c parser.tab.h lexer.yy.c parser.tab.o lexer.yy.o ASTNode.o calculator.exe ast.json 2>nul
win_bison -d -o parser.tab.c parser.y
win_flex -o lexer.yy.c lexer.l
gcc -c ASTNode.c -o ASTNode.o
gcc -c parser.tab.c -o parser.tab.o
gcc -c lexer.yy.c -o lexer.yy.o
gcc parser.tab.o lexer.yy.o ASTNode.o -o calculator.exe
