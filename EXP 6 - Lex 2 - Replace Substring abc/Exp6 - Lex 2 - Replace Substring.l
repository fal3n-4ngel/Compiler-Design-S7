// Adithya Krishnan 
// Lex 2 - Replace Substring abc

%{
    #include <stdio.h>
%}

%%
abc {printf("ABC");}
. {printf("%c",yytext[0]);}
%%

int main() {
    printf("Enter the input:");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

// [nix-shell:/home/hikki/Desktop/CD - Lab ]# ./lexer
// Enter the input:hi abc hi 
// hi ABC hi 
