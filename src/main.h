/**
 * Definition of functions used by main.
 *
 * @author Rui Carlos Gonçalves
 * @file main.h
 * @version 1.5
 * @date 08/2015
 */
#ifndef _MAIN_
#define _MAIN_

#include "array.h"
#include "read.h"

/**
 * From the info collected by the parser, creates a matrix representing the
 * problem to solve, according to the format required by function
 * <tt>simplex</tt>.
 *
 * @param prob  info about the problem.
 * @param varc  number of variables.
 * @param condc number of conditions.
 * @param eqc   number of conditions with an equality operator.
 * @param type  determines whether we have a maximization or minimization
 * problem (max.: -1, min.: 1).
 *
 * @return the matrix created.
 */
double* loadMatrix(Prob prob,int varc,int condc,int eqc,int type);

/**
 * Prints the result.
 *
 * @param vars  name of the variables of each position of the table.
 * @param tab   table resulting from applying the <em>Simplex</em> algorithm.
 * @param varob variable to maximize/minimize.
 * @param varc  number of variables.
 * @param condc number of conditions
 * @param type  determines whether we have a maximization or minimization
 * problem (max.: -1, min.: 1).
 */
void printRes(Array vars,double* tab,const char* varob,int varc,int condc,int type);

/**
 * Checks the options specified by the user.
 *
 * @param argc number of options.
 * @param argv value of the options.
 * @param in   address for the input option.
 * @param out  address for the output option.
 *
 * @return 1 if the <tt>tables</tt> option was set; 0 otherwise.
 */
int opt(int argc,char** argv,char** in,char** out);

#endif
