/**
 * Definição de tipos de dados e funções necessários para ler e armazenar os
 *   dados de um problema.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file read.h
 * @version 1.3
 * @date 02/2009
 */
#ifndef _READ_
#define _READ_

#include "array.h"
#include "hashmap.h"
#include "list.h"

/**
 * Estrutura de dados que representa a informação de uma expressão.
 */
typedef struct sExp
{
  ///Coeficientes das variáveis numa determinada expressão.
  Array coefs;
  ///Operador relacional da expressão.
  int op;
  ///Lado direito da expressão.
  double rhs;
}SExp;

/**
 * Definição de uma expressão.
 */
typedef SExp* Exp;

/**
 * Estrutura de dados que representa a informação de um problema.
 */
typedef struct sProb
{
  ///Contém as variáveis e o seu índice.
  HashMap pos;
  ///Permite saber qual a variável associada a um índice.
  Array invpos;
  ///Lista de expressões (função objectivo e condições).
  List exps;
}SProb;

/**
 * Definição de um problema.
 */
typedef SProb* Prob;

//##############################################################################

/**
 * Inicializa uma variável do tipo @c Exp.
 * Se ocorrer algum erro devolve NULL.
 *
 * @param arraysize tamanho do array dos coeficientes.
 *
 * @return variável inicializada (ou NULL).
 */
Exp newExp(int arraysize);

/**
 * Inicializa uma variável do tipo @c Prob.
 * Se ocorrer algum erro devolve NULL.
 *
 * @return variável inicializada ou NULL.
 */
Prob newProb();

/**
 * Função de @a hash que será usada para o nome das variáveis.
 *
 * @param varid identificador da variável.
 *
 * @return número de hash.
 */
int varhash(const char* varid);

/**
 * Adiciona uma nova condição ao problema e adiciona o coeficiente de uma
 *   variável.
 * Se a variável ainda não existir no conjunto de variáveis, esta é adicionada.
 *
 * @param prob  dados do problema.
 * @param varid identificador da variável.
 * @param varc  índice que a variável terá caso ainda não exista.
 * @param coef  coeficiente da variável.
 *
 * @return 0 se a variável já existia;\n
 *         1 caso contrário.
 */
int addCoefHead(Prob prob,const char* varid,int varc,double coef);

/**
 * Adiciona o coeficiente de uma variável.
 * Se a variável ainda não existir no conjunto de variáveis, esta é adicionada.
 *
 * @param prob  dados do problema.
 * @param varid identificador da variável.
 * @param varc  índice que a variável terá caso ainda não exista.
 * @param coef  coeficiente da variável.
 *
 * @return 0 se a variável já existia;\n
 *         1 caso contrário.
 */
int addCoefTail(Prob prob,const char* varid,int varc,double coef);

/**
 * Adiciona informações sobre o operador relacional e o lado direito de uma
 *   condição.
 *
 * @param prob dados do problema.
 * @param op   identificador do operador relacional.
 * @param rhs  lado direito da condição.
 *
 * @return 0.
 */
int setOpRHS(Prob prob,int op,double rhs);

#endif
