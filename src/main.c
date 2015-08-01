/**
 * Definition of functions used by main.
 *
 * @author Rui Carlos Gonçalves
 * @file main.c
 * @version 1.5
 * @date 08/2015
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "main.h"

/**
 * Given a row (<tt>R</tt>), a column (<tt>C</tt>), and the number of columns
 * (<tt>NC</tt>) of a matrix, computes an equivalent 1D position.
 */
#define POS(R,C,NC) ((R)*(NC)+(C))

/// Error messages.
static char* errors[]={"ERROR! Function \'loadMatrix\' -> \'calloc\'.\n"
                      ,"ERROR! Function \'printRes\' -> \'newArray\'.\n"
                      ,"ERROR! Function \'printRes\' -> \'malloc\'.\n"
                      ,"ERROR! Function \'printRes\' -> \'arrayInsert\'.\n"
                      ,"ERROR! Invalid parameters.\n"
                      };

//##############################################################################

double* loadMatrix(Prob prob,int varc,int condc,int eqc,int type)
{
  double* res,*tmp;
  int row,col,k;
  Exp exp;

  k=varc+condc+eqc+2;
  res=calloc((condc+1+eqc)*(varc+condc+eqc+2),sizeof(double));

  if(!res){
    fputs(errors[0],stderr);
    exit(1);
  }

  listRemoveFst(prob->exps,(void**)&exp);

  res[POS(0,k-2,k)]=0;
  res[POS(0,k-1,k)]=0;

  for(col=0;col<k-2;col++)
  {
    arrayAt(exp->coefs,col,(void**)&tmp);
    res[POS(0,col,k)]=tmp?type*(*tmp):0;
  }

  arrayMap(exp->coefs,free);
  arrayDelete(exp->coefs);
  free(exp);

  for(row=1;!listRemoveFst(prob->exps,(void**)&exp);)
  {
    if(exp->op>-1)
    {
      res[POS(row,k-2,k)]=exp->rhs;
      res[POS(row,k-1,k)]=row+varc-1;

      for(col=0;col<varc;col++)
      {
        arrayAt(exp->coefs,col,(void**)&tmp);
        res[POS(row,col,k)]=tmp?*tmp:0;
      }

      row++;

      arrayMap(exp->coefs,free);
      arrayDelete(exp->coefs);
      free(exp);
    }

    if(exp->op<1)
    {
      res[POS(row,k-2,k)]=-1*(exp->rhs);
      res[POS(row,k-1,k)]=row+varc-1;

      for(col=0;col<varc;col++)
      {
        arrayAt(exp->coefs,col,(void**)&tmp);
        res[POS(row,col,k)]=tmp?-(*tmp):0;
      }

      row++;
    }
  }

  for(row=0;row<condc;row++)
    for(col=0;col<condc;col++)
      res[POS(row+1,col+varc,k)]=row==col;

  return res;
}

//##############################################################################

void printRes(Array vars,double* tab,const char* varob,int varc,int condc,int type)
{
  int i,k,erro;
  double* tmp;
  char* str;
  Array res;
  
  k=varc+condc+2;
  res=newArray(varc);

  if(!res){
    fputs(errors[1],stderr);
    exit(2);
  }

  for(i=1;i<condc+1;i++)
    if(tab[POS(i,k-1,k)]<varc)
    {
      tmp=malloc(sizeof(double));

      if(!tmp){
	fputs(errors[2],stderr);
        exit(3);
      }

      *tmp=tab[POS(i,k-2,k)];
      erro=arrayInsert(res,tab[POS(i,k-1,k)],tmp,0);

      if(erro){
	fputs(errors[3],stderr);
        exit(4);
      }
    }

  puts("====================");
  printf("%s = %f\n",varob,-type*tab[POS(0,k-2,k)]);
  puts("--------------------");
  for(i=0;i<varc;i++)
  {
    arrayAt(vars,i,(void**)&str);
    printf("%s =",str);
    if(!arrayAt(res,i,(void**)&tmp)) printf(" %f\n",*tmp);
    else printf(" 0.0\n");
  }
  puts("====================");

  arrayMap(res,free);
  arrayDelete(res);
}

//##############################################################################

int opt(int argc,char** argv,char** in,char** out)
{
  int c,res;

  static struct option options[]={{"output" ,required_argument,NULL,'o'}
                                 ,{"input"  ,required_argument,NULL,'i'}
                                 ,{"tables" ,no_argument      ,NULL,'t'}
                                 ,{"help"   ,no_argument      ,NULL,'h'}
                                 ,{"version",no_argument      ,NULL,'v'}
                                 ,{0,0,0,0}
                                 };

  res=0;

  while((c=getopt_long(argc,argv,"o:i:thv",options,NULL))!=-1)
  {
    switch(c)
    {
      case 'o' : *out=optarg;
                 break;
      case 'i' : *in=optarg;
                 break;
      case 't' : res+=1;
                 break;
      case 'h' : puts("rlp version 1.1, Copyright (C) 2009 Rui Carlos A. Goncalves\n"
                      "rlp comes with ABSOLUTELY NO WARRANTY.  This is free software, and\n"
                      "you are welcome to redistribute it under certain conditions.  See the GNU\n"
                      "General Public Licence for details.\n\n"
                      "Solve linear programming problems using simplex method.\n\n"
                      "Options:\n"
                      "  --help                 Print this help\n"
                      "  --version              Print version number\n"
                      "  --input=<file>         Input file (default: stdin)\n"
                      "  --tables               Print all tables\n"
                      "  --output=<file>        Output file (default: stdout)"
                     );
                 res-=2;
                 break;
      case 'v' : puts("rlp version 1.1, Copyright (C) 2009 Rui Carlos A. Goncalves\n"
                      "rlp comes with ABSOLUTELY NO WARRANTY.  This is free software, and\n"
                      "you are welcome to redistribute it under certain conditions.  See the GNU\n"
                      "General Public Licence for details."
                     );
                 res-=2;
                 break;
      default  : break;
    }
  }

  if(optind<argc){
    fputs(errors[4],stderr);
    exit(5);
  }

  return res;
}
