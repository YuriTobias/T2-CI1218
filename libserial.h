#ifndef _LIBserial_t_H
#define _LIBserial_t_H

#include "liblist.h"
#include "libscale.h"

/*! 
 * @name findEdges
 * @brief Busca todas as arestas de todas as transações pertencentes a determinado escalonamento
 * @param s O escalonamento contendo a lista de transações
 * @result preenche a lista de arestas das transações com as respectivas arestas
 */
void findEdges(Scale *s);

/*!
 * @name isSerial
 * @brief Verifica a partir de uma lista de arestas se determinada transação eh ou não, por conflito, serializável 
 * @param txnEdges Lista de arestas de determinada transação
 * @param txnId O id da transação que será verificada se é ou não serializável
 * @result 1 se é serial e 0 caso contrário
 */
int isSerial(List *txnEdges, int txnId);

/*! 
 * @name checksSeriability
 * @brief Verifica, por conflito, se o escalonamento eh serializável ou não
 * @param s O escalonamento
 * @result 1 seé serializável e 0 caso contrário
 * */
int checksSeriality(Scale *s);

#endif