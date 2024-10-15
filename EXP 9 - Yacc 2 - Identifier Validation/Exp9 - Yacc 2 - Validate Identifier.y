%{
    #include <stdio.h>
    #include <stdlib.h>
    void yyerror(const char *s);
    int yylex(void);
    int valid = 1;
%}

%token DIGIT CHARACTER INVALID

%%

start: identifier
     ;

identifier: CHARACTER rest
          ;

rest: CHARACTER rest
    | DIGIT rest
    | /* empty */
    ;

%%

void yyerror(const char *s) {
    printf("Error: %s\n", s);
    valid = 0;
}

int main(void) {
    printf("Enter identifier: ");
    yyparse();
    if (valid) {
        printf("\nValid Identifier\n");
    } else {
        printf("\nInvalid Identifier\n");
    }
    return 0;
}