%{
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "array.h"
#include "read.h"
#include "main.h"
#include "rlp.h"

extern FILE* yyin;
extern int yylineno;
extern char* yytext;

int type=0;
int varc=0;
int condc=0;
int eqc=0;
char* vobj=NULL;
Prob prob=NULL;

int yylex();
void yyerror(const char* msg)
{fprintf(stderr,"ERROR! line %d: %s - %s\n",yylineno,yytext,msg);exit(255);}
%}

%union{
        double real;
        int integer;
        char* str;
      }

// Terminals
%token OPADD    "+"
%token OPSUB    "-"
%token OPMULT   "*"
%token OPEQ     "="
%token OPLE     "<="
%token OPGE     ">="
%token OP       "("
%token CP       ")"
%token MIN      "MIN"
%token MAX      "MAX"
%token ST       "ST"

// Pseudo-terminals
%token <real> REAL
%token <str> VAR

// Non-terminals
%type <real> Real
%type <integer> OpRel Sig

%%

Prob    : Type VAR "=" Exp "ST" LCond   {vobj=$2;}
        ;
Type    : "MAX"                         {type=-1;}
        | "MIN"                         {type=1;}
        ;
Exp     : Head Tail                     {condc++;}
        ;
Head    : VAR                           {varc+=addCoefHead(prob,$1,varc,1);}
        | Sig VAR                       {varc+=addCoefHead(prob,$2,varc,$1);}
        | REAL OptS VAR                 {varc+=addCoefHead(prob,$3,varc,$1);}
        | Sig REAL OptS VAR             {varc+=addCoefHead(prob,$4,varc,$1*$2);}
        ;
Tail    :                               {}
        | Tail Prod                     {}
        ;
Prod    : Sig VAR                       {varc+=addCoefTail(prob,$2,varc,$1);}
        | Sig Real OptS VAR             {varc+=addCoefTail(prob,$4,varc,$2*$1);}
        ;
Real    : "(" Sig REAL ")"              {$$=$2*$3;}
        | REAL                          {$$=$1;}
        ;
Sig     : "+"                           {$$=1;}
        | "-"                           {$$=-1;}
        ;
OptS    :                               {}
        | "*"                           {}
        ;
LCond   : Exp OpRel Real                {setOpRHS(prob,$2,$3);}
        | LCond Exp OpRel Real          {setOpRHS(prob,$3,$4);}
        ;
OpRel   : ">="                          {$$=-1;}
        | "<="                          {$$=1;}
        | "="                           {$$=0;eqc++;}
        ;

%%

int main(int argc,char** argv)
{
  double* matrix;
  int err,ftab;
  char* in,*out;
  FILE* fin,*fout;

  in=NULL;
  out=NULL;
  fin=NULL;
  fout=NULL;

  if((ftab=opt(argc,argv,&in,&out))<0) return 0;

  if(in)
  {
    fin=fopen(in,"r");

    if(!fin)
    {
      fprintf(stderr,"ERROR! Can not open file \'%s\'.\n",in);
      exit(254);
    }
    yyin=fin;
  }

  if(ftab)
  {
    if(out)
    {
      fout=fopen(out,"w");
      if(!fout) fprintf(stderr,"ERROR! Can not open file \'%s\'.\n",out);
    }
    else fout=stdout;
  }

  prob=newProb();

  yyparse();

  matrix=loadMatrix(prob,varc,condc-1,eqc,type);

  err=simplex(matrix,varc,condc-1+eqc,fout);

  if(err)
  {
    printf("Can not solve this problem.\n");
    return 1;
  }
 
  puts("");
  printRes(prob->invpos,matrix,vobj,varc,condc+eqc-1,type);
  puts("");

  listDelete(prob->exps);
  arrayMap(prob->invpos,free);
  arrayDelete(prob->invpos);
  hashDelete(prob->pos);
  return 0;
}
