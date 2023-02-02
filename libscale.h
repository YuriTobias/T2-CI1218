#ifndef _LIBscale_t_H
#define _LIBscale_t_H

#include "liblist.h"

typedef enum { READ, WRITE, COMMIT, INVALID } OpType;

typedef struct {
    int id;
    List *ops;
    List *edges;
} Txn;

typedef struct {
    int time;
    OpType type;
    char attr;
} Op;

typedef struct {
    int id;
    int serial;
    int equiv;
    List *txns;
} Scale;

/*!
 * @name CreateScale
 * @brief Aloca e inicializa um escalonamento.
 * @param id O id a ser atribuído ao escalonamento.
 * @result Um ponteiro para o escalonamento criado.
 */
Scale *CreateScale(int id);

/*!
 * @name CreateOp
 * @brief Aloca e inicializa uma operação.
 * @param time O id/tempo da operação.
 * @param type O tipo da operação.
 * @param attr O atributo o qual a operação está manipulando.
 * @result Um ponteiro para a operação criada.
 */
Op *CreateOp(int time, OpType type, char attr);

/*!
 * @name CreateTxn
 * @brief Aloca e inicializa uma transação.
 * @param id O id a ser atribuído à transação.
 * @result Um ponteiro para a transação criada.
 */
Txn *CreateTxn(int id);

/*!
 * @name ListInsertScale
 * @brief Cria e insere um escalonamento em uma lista de escalonamentos, respeitando o id incremental.
 * @param scales A lista onde o novo escalonamento será salvo.
 * @param curScale O escalonamento atual, cujo id será usado como base para a criação do novo.
 * @result Um ponteiro para o novo escalonamento criado e inserido.
 */
Scale *ListInsertScale(List *scales, Scale *curScale);

/*!
 * @name ConvertOpType
 * @brief Converte um caractere em tipo enumerado de operação.
 * @param c O caractere a ser convertido.
 * @result Um tipo enumerado equivalente ao caractere recebido.
 */
OpType ConvertOpType(char c);

/*!
 * @name ListDestroyScales
 * @brief Desaloca uma lista de escalonamentos, tal como os escalonamentos em si e seus dependentes.
 * @param scales A lista com os escalonamentos a serem destruídos.
 */
void ListDestroyScales(List *scales);

/*!
 * @name compareTxns
 * @brief Compara duas transações de acordo com seus ids, independente dos objetos serem iguais ou não.
 * @param txnA Uma transação.
 * @param txnB Uma transação.
 * @result 1 se as transações tiverem o mesmo id, 0 caso contrário.
 */
int compareTxns(void *txnA, void *txnB);

/*!
 * @name compareTxnId
 * @brief Checa se o id de uma transação corresponde a um id recebido.
 * @param txn Uma transação.
 * @param id Um id de transação.
 * @result 1 se a transação tiver o id recebido, 0 caso contrário.
 */
int compareTxnId(void *txn, void *id);

#endif