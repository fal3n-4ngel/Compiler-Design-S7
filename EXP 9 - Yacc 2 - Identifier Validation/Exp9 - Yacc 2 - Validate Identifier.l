%{
    #include "yac.tab.h"
%}
%%
[a-zA-Z_]   {return CHARACTER;}
[0-9]       {return DIGIT;}
[ \t\n]     {return 0;}
.           { return INVALID; }

%%

int yywrap(void) {
    return 1;
}
