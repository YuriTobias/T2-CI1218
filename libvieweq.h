#ifndef _LIBvieweq_t_H
#define _LIBvieweq_t_H

#include "liblist.h"
#include "libscale.h"

/*!
 * @name checkViewEquivalence
 * @brief Checa se um escalonamento S' serial pode ser considerado equivalente ao escalonamento S original
 * @param stackedOps Uma lista com as operações do escalonamento, na ordem de S', mas mantendo os atributos originais de S.
 * @param scaleAttrs Uma lista dos atributos operados pelo escalonamento original S.
 * @result 1 se o escalonamento S' for equivalente ao original S, 0 caso contrário.
 */
int checkViewEquivalence(List *stackedOps, List *scaleAttrs);

/*!
 * @name swapTxns
 * @brief Permuta as transações de um escalonamento e avalia equivalência para cada uma das ordens possíveis.
 * @param stackedOps Uma lista de operações já ordenadas conforme decorre a permutação. Inicia vazia.
 * @param availableTxns Uma lista de transações cujas ordens ainda não foram definidas conforme decorre a permutação. Inicia com
 * todas as transações.
 * @param scaleAttrs Uma lista dos atributos operados pelo escalonamento original S.
 * @result 1 se houver algum escalonamento S' equivalente ao original S, 0 caso contrário.
 */
int swapTxns(List *stackedOps, List *availableTxns, List *scaleAttrs);

/*!
 * @name swapAndCheckEquivalence
 * @brief Função wrapper para a recursão swapTxns.
 * @param s O escalonamento no qual deseja-se avaliar a equivalência por visão.
 * @result 1 se houver algum escalonamento S' equivalente ao original S, 0 caso contrário.
 */
int swapAndCheckEquivalence(Scale *s);

#endif