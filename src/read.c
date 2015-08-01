/**
 * Definitions of data types and functions required to read and store the
 * data about the problem.
 *
 * @author Rui Carlos Gonçalves
 * @file read.c
 * @version 1.5
 * @date 08/2015
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "read.h"

/**
 * Given a row (<tt>R</tt>), a column (<tt>C</tt>), and the number of columns
 * (<tt>NC</tt>) of a matrix, computes an equivalent 1D position.
 */
#define POS(R,C,NC) ((R)*(NC)+(C))

/// Error messages.
static char* errors[]={"ERROR! Function \'setCoefHead\' -> \'malloc\'.\n"
                      ,"ERROR! Function \'setCoefHead\' -> \'listInsertLst\'.\n"
                      ,"ERROR! Function \'setCoefHead\' -> \'arrayInsert\'.\n"
                      ,"ERROR! Function \'setCoefHead\' -> \'newExp\'.\n"
                      ,"ERROR! Function \'setCoefHead\' -> \'hashInsert\'.\n"
                      ,"ERROR! Function \'setCoefTail\' -> \'malloc\'.\n"
                      ,"ERROR! Function \'setCoefTail\' -> \'hashInsert\' or"
                      "\'arrayInsert\'.\n"
                      ,"ERROR! Function \'setCoefTail\' -> \'arrayInsert\'.\n"
                      };

//##############################################################################

Exp newExp(int size)
{
  Exp res;

  res=malloc(sizeof(SExp));

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

  res=malloc(sizeof(SProb));

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
    vpos=malloc(sizeof(int));

    if(!vpos){
      fputs(errors[0],stderr);
      exit(1);
    }

    *vpos=varc;
    erro=hashInsert(prob->pos,(void**)varid,vpos,0);
    erro+=arrayInsert(prob->invpos,varc,(void**)varid,0);

    if(erro){
      fputs(errors[4],stderr);
      exit(5);
    }

    res=1;
  }

  exp=newExp((varc+1>10)?(varc+1):10);

  if(!exp){
    fputs(errors[3],stderr);
    exit(4);
  }

  erro=listInsertLst(prob->exps,exp);

  if(erro){
    fputs(errors[1],stderr);
    exit(2);
  }

  tmp=malloc(sizeof(double));

  if(!tmp){
    fputs(errors[0],stderr);
    exit(1);
  }
    
  *tmp=coef;
  erro=arrayInsert(exp->coefs,*vpos,tmp,0);

  if(erro){
    fputs(errors[2],stderr);
    exit(3);
  }

  return res;
}

//##############################################################################

int addCoefTail(Prob prob,const char* varid,int varc,double coef)
{
  int* vpos,pos,res,error;
  double* tmp;
  Exp exp;

  vpos=&pos;
  res=0;

  if(hashGet(prob->pos,(void*)varid,(void**)&vpos))
  {
    vpos=malloc(sizeof(int));

    if(!vpos){
      fputs(errors[5],stderr);
      exit(6);
    }

    *vpos=varc;
    error=hashInsert(prob->pos,(void**)varid,vpos,0);
    error+=arrayInsert(prob->invpos,varc,(void**)varid,0);

    if(error)
    {
      fputs(errors[6],stderr);
      exit(7);
    }

    res=1;
  }

  listLst(prob->exps,(void**)&exp);
  tmp=malloc(sizeof(double));

  if(!tmp){
    fputs(errors[5],stderr);
    exit(6);
  }

  *tmp=coef;
  error=arrayInsert(exp->coefs,*vpos,tmp,0);

  if(error)
  {
    fputs(errors[7],stderr);
    fprintf(stderr,"\n%d\n\n",error);
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
