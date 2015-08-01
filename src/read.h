/**
 * Definitions of data types and functions required to read and store the
 * data about the problem.
 *
 * @author Rui Carlos Gonçalves
 * @file read.h
 * @version 1.5
 * @date 08/2015
 */
#ifndef _READ_
#define _READ_

#include "array.h"
#include "hashmap.h"
#include "list.h"

/**
 * Expression structure.
 */
typedef struct sExp
{
  /// Coefficients of the variables.
  Array coefs;
  /// Operator of the expression.
  int op;
  /// Right-hand side of the expression.
  double rhs;
}SExp;

/**
 * Expression definition.
 */
typedef SExp* Exp;

/**
 * Problem structure.
 */
typedef struct sProb
{
  /// Variables and their indexes.
  HashMap pos;
  /// Variables on each index.
  Array invpos;
  /// List of expressions (objective function, and conditions). 
  List exps;
}SProb;

/**
 * Problem definition.
 */
typedef SProb* Prob;

//##############################################################################

/**
 * Creates an expression.
 *
 * @param arraysize size of the coefficients array.
 *
 * @return <tt>NULL</tt> if an error occurred; the new expression otherwise.
 */
Exp newExp(int arraysize);

/**
 * Creates a problem.
 *
 * @return <tt>NULL</tt> if an error occurred; the new problem otherwise.
 */
Prob newProb();

/**
 * Hash function for variables names.
 *
 * @param varid the variable identifier.
 *
 * @return the hash code of the variable.
 */
int varhash(const char* varid);

/**
 * Adds a new condition to the problem, and adds the coefficients of a variable.
 * If the variable did not exist in the variables set, it is added.
 *
 * @param prob  the problem.
 * @param varid the variable identifier.
 * @param varc  the index of the variable if it does not exist.
 * @param coef  the coefficient of the variable.
 *
 * @return 0 if the variable already existed; 0 otherwise.
 */
int addCoefHead(Prob prob,const char* varid,int varc,double coef);

/**
 * Adds the coefficient of a variable.
 * If the variable did not exist in the variables set, it is added.
 *
 * @param prob  the problem.
 * @param varid the variable identifier.
 * @param varc  the index of the variable if it does not exist.
 * @param coef  the coefficient of the variable.
 *
 * @return 0 if the variable already existed; 0 otherwise.
 */
int addCoefTail(Prob prob,const char* varid,int varc,double coef);

/**
 * Adds the relational operator and the right-hand side to a condition.
 *
 * @param prob the problem.
 * @param op   the identifier of the relational operator.
 * @param rhs  the right-hand side of the condition.
 *
 * @return 0.
 */
int setOpRHS(Prob prob,int op,double rhs);

#endif
