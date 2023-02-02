#ifndef _LIBvieweq_t_H
#define _LIBvieweq_t_H

#include "liblist.h"
#include "libscale.h"

/*!
 * @name lastWrite
 * @brief Busca a última operação de WRITE de um escalonamento.
 * @param s O escalonamento do qual será buscada a última operação WRITE.
 * @result O id/tempo da última operação.
 */
int lastWrite(Scale *s);

/*!
 * @name checkViewEquivalence
 * @brief Checa se um escalonamento S' serial pode ser considerado equivalente ao escalonamento S original
 * @param stackedOps Uma lista com as operações do escalonamento, na ordem de S', mas mantendo os atributos originais de S.
 * @param lastWrite O id/tempo do último write do escalonamento original S.
 * @result 1 se o escalonamento S' for equivalente ao original S, 0 caso contrário.
 */
int checkViewEquivalence(List *stackedOps, int lastWrite);

/*!
 * @name swapTxns
 * @brief Permuta as transações de um escalonamento e avalia equivalência para cada uma das ordens possíveis.
 * @param stackedOps Uma lista de operações já ordenadas conforme decorre a permutação. Inicia vazia.
 * @param availableTxns Uma lista de transações cujas ordens ainda não foram definidas conforme decorre a permutação. Inicia com
 * todas as transações.
 * @param lastWrite O id/tempo do último write do escalonamento original S.
 * @result 1 se houver algum escalonamento S' equivalente ao original S, 0 caso contrário.
 */
int swapTxns(List *stackedOps, List *availableTxns, int lastWrite);

/*!
 * @name swapAndCheckEquivalence
 * @brief Função wrapper para a recursão swapTxns.
 * @param s O escalonamento no qual deseja-se avaliar a equivalência por visão.
 * @result 1 se houver algum escalonamento S' equivalente ao original S, 0 caso contrário.
 */
int swapAndCheckEquivalence(Scale *s);

#endif