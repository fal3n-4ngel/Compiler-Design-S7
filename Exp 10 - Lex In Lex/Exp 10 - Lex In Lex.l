%{
#include <stdio.h>
#include <string.h>
FILE *output_file;
#define IDENTIFIER
#define NUMBER 2
#define KEYWORD 3
#define OPERATOR 4
#define WHITESPACE 5
#define STRING 6
#define SYMBOL 7
%}

KEYWORD "if"|"else"|"while"|"for"|"int"|"else if"|"printf"
OPERATOR "*"|"-"|"+"|"="
SYMBOL "{"|"}"|"("|")"|";"

%%
{KEYWORD} {fprintf(output_file, "Keyword: %s\n", yytext);}
{SYMBOL} {fprintf(output_file, "Symbol: %s\n", yytext);}
[0-9]+ {fprintf(output_file, "Number: %s\n", yytext);}
[a-zA-Z_][a-zA-Z0-9_]* {fprintf(output_file, "Identifier: %s\n", yytext);}
{OPERATOR} {fprintf(output_file, "Operator: %s\n", yytext);}
"\""[^"]*"\"" {fprintf(output_file, "String: %s\n", yytext);}
[ \t\n]+ {/* Ignore whitespace */}
. {fprintf(output_file, "Unknown Character: %s\n", yytext);}
%%

int main(int argc, char **argv) {
    FILE *input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");

    if (!input_file || !output_file) {
        printf("Error opening file.\n");
        return 1;
    }

    yyin = input_file;
    yylex();
    
    fclose(input_file);
    fclose(output_file);

    return 0;
}

int yywrap(){
    return 1;
}