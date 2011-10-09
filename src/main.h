/**
 * Definição das funções usadas na 'main'.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file main.h
 * @version 1.2
 * @date 02/2009
 */
#ifndef _MAIN_
#define _MAIN_

#include "array.h"
#include "read.h"

/**
 * A partir das informações recolhidas pelo @a parser cria uma matriz
 *   representativa do problema de acordo com o modelo usado pela função
 *   @c simplex.
 *
 * @param prob  conjunto de informações sobre o problema.
 * @param varc  número de variáveis.
 * @param condc número de condições.
 * @param eqc   número de vezes que o operador igualdade aparece nas condições.
 * @param type  indica se o problema é de maximização ou minimização (max.: -1,
 *              min.: 1).
 *
 * @return matriz criada.
 */
double* loadMatrix(Prob prob,int varc,int condc,int eqc,int type);

/**
 * Imprime o resultado obtido.
 *
 * @attention restrições que tenham o operador de igualdade contam como duas.
 *
 * @param vars  nome das variáveis associadas a cada posição da tabela.
 * @param tab   tabela resultante da aplicação do @a Algoritmo @a Simplex ao
 *              problema.
 * @param varob variável a maximizar/minimizar.
 * @param varc  número de variáveis do problema.
 * @param condc número de condições do problema.
 * @param type  tipo de problema (max.: -1,min.: 1).
 */
void printRes(Array vars,double* tab,const char* varob,int varc,int condc,int type);

/**
 * Verifica as opções especificadas pelo utilizador.
 *
 * @param argc número de opções lidas.
 * @param argv opções lidas.
 * @param in   endereço onde será colocado o argumento associado à opção
 *             @a input.
 * @param out  endereço onde será colocado o argumento associado à opção
 *             @a output.
 *
 * @return 1 se for reconhecida a opção @a table;\n
 *         0 caso contrário.
 */
int opt(int argc,char** argv,char** in,char** out);

#endif
