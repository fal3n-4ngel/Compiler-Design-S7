%{
    #include <stdio.h>
    int words = 0;
    int letters = 0;
    int lines = 0;
%}

%%
\n      { lines++; }
[a-zA-Z]+ { letters += yyleng; words++; }
[[:space:]]+  { /* Ignore whitespace between words */ }
.       { /* Ignore other characters */ }
%%

int main() {
    printf("Enter the input (Ctrl+D to end on Unix, Ctrl+Z on Windows):\n");
    yylex();
    printf("Words: %d\n", words);
    printf("Letters: %d\n", letters);
    printf("Lines: %d\n", lines);
    return 0;
}

int yywrap() {
    return 1;
}
