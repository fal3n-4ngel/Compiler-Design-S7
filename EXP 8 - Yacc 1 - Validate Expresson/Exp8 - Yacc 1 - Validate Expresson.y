%{
#include <stdio.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
expression: NUMBER
          | expression '+' expression
          | expression '-' expression
          | expression '*' expression
          | expression '/' expression
          ;

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *msg) {
    printf("Error: %s\n", msg);
    return 0;
}
