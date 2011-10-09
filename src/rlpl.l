%{
#include <string.h>
#include "rlpy.h"
%}

real    [0-9]+(\.)?[0-9]*
var     [a-z][a-zA-Z0-9]*

%option yylineno

%%

"ST"            {return ST;}
"MIN"           {return MIN;}
"MAX"           {return MAX;}
{real}          {yylval.real=atof(yytext);return REAL;}
{var}           {yylval.str=strdup(yytext);return VAR;}
"+"             {return OPADD;}
"-"             {return OPSUB;}
"*"             {return OPMULT;}
"="             {return OPEQ;}
">="            {return OPGE;}
"<="            {return OPLE;}
"("             {return OP;}
")"             {return CP;}
[ \n\t]         {}

%%

int yywrap()
{return 1;}
