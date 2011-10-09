/**
 * Definição de tipos de dados e funções necessários para ler e armazenar os
 *   dados de um problema.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file read.c
 * @version 1.3
 * @date 02/2009
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "read.h"

/**
 * Dado a linha, a coluna e o número de colunas de um array de duas dimensões
 *   obtém o índice dessa posição assumindo que o array é de uma dimensão.
 */
#define POS(L,C,NC) ((L)*(NC)+(C))

///Mensagens de erro.
static char* erros[]={"ERROR! Function \'setCoefHead\' -> \'malloc\'.\n"
                     ,"ERROR! Function \'setCoefHead\' -> \'listInsertLst\'.\n"
                     ,"ERROR! Function \'setCoefHead\' -> \'arrayInsert\'.\n"
                     ,"ERROR! Function \'setCoefHead\' -> \'newExp\'.\n"
                     ,"ERROR! Function \'setCoefHead\' -> \'hashInsert\'.\n"
                     ,"ERROR! Function \'setCoefTail\' -> \'malloc\'.\n"
                     ,"ERROR! Function \'setCoefTail\' -> \'hashInsert\' ou"
                     "\'arrayInsert\'.\n"
                     ,"ERROR! Function \'setCoefTail\' -> \'arrayInsert\'.\n"
                     };

//##############################################################################

Exp newExp(int size)
{
  Exp res;

  res=(Exp)malloc(sizeof(SExp));

  if(res)
  {
    res->coefs=newArray(size);
    res->op=0;
    res->rhs=0;
  }

  return res;
}

//##############################################################################

Prob newProb()
{
  Prob res;

  res=(Prob)malloc(sizeof(SProb));

  if(res)
  {
    res->pos=newHash(32,0.6,(int(*)(void*))varhash,(int(*)(void*,void*))strcmp);
    res->invpos=newArray(10);
    res->exps=newList();
  }

  return res;
}

//##############################################################################

int varhash(const char* varid)
{
  int i,res;

  for(i=0,res=0;varid[i];i++)
    res+=varid[i];

  return res;
}

//##############################################################################

int addCoefHead(Prob prob,const char* varid,int varc,double coef)
{
  int* vpos,pos,erro,res;
  double* tmp;
  Exp exp;

  vpos=&pos;
  res=0;

  if(hashGet(prob->pos,(void*)varid,(void**)&vpos))
  {
    vpos=(int*)malloc(sizeof(int));

    if(!vpos){
      fprintf(stderr,erros[0]);
      exit(1);
    }

    *vpos=varc;
    erro=hashInsert(prob->pos,(void**)varid,vpos,0);
    erro+=arrayInsert(prob->invpos,varc,(void**)varid,0);

    if(erro){
      fprintf(stderr,erros[4]);
      exit(5);
    }

    res=1;
  }

  exp=newExp((varc+1>10)?(varc+1):10);

  if(!exp){
    fprintf(stderr,erros[3]);
    exit(4);
  }

  erro=listInsertLst(prob->exps,exp);

  if(erro){
    fprintf(stderr,erros[1]);
    exit(2);
  }

  tmp=(double*)malloc(sizeof(double));

  if(!tmp){
    fprintf(stderr,erros[0]);
    exit(1);
  }
    
  *tmp=coef;
  erro=arrayInsert(exp->coefs,*vpos,tmp,0);

  if(erro){
    fprintf(stderr,erros[2]);
    exit(3);
  }

  return res;
}

//##############################################################################

int addCoefTail(Prob prob,const char* varid,int varc,double coef)
{
  int* vpos,pos,res,erro;
  double* tmp;
  Exp exp;

  vpos=&pos;
  res=0;

  if(hashGet(prob->pos,(void*)varid,(void**)&vpos))
  {
    vpos=(int*)malloc(sizeof(int));

    if(!vpos){
      fprintf(stderr,erros[5]);
      exit(6);
    }

    *vpos=varc;
    erro=hashInsert(prob->pos,(void**)varid,vpos,0);
    erro+=arrayInsert(prob->invpos,varc,(void**)varid,0);

    if(erro)
    {
      fprintf(stderr,erros[6]);
      exit(7);
    }

    res=1;
  }

  listLst(prob->exps,(void**)&exp);
  tmp=(double*)malloc(sizeof(double));

  if(!tmp){
    fprintf(stderr,erros[5]);
    exit(6);
  }

  *tmp=coef;
  erro=arrayInsert(exp->coefs,*vpos,tmp,0);

  if(erro)
  {
    fprintf(stderr,erros[7]);
    fprintf(stderr,"\n%d\n\n",erro);
    exit(8);
  }
 
  return res;
}

//##############################################################################

int setOpRHS(Prob prob,int op,double rhs)
{
  Exp exp;

  listLst(prob->exps,(void**)&exp);

  exp->op=op;
  exp->rhs=rhs;

  return 0;
}
