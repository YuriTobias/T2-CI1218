#include "libvieweq.h"

#include <stdio.h>
#include <stdlib.h>

// int lastWrite(Scale *s) {
//     Node *curTxnNode = s->txns->head;
//     int last = -1;
//     // Itera todas as transações do escalonamento em busca da última operação WRITE (max{op->time})
//     while (curTxnNode != NULL) {
//         Txn *curTxn = ((Txn *)curTxnNode->key);
//         Node *curOpNode = curTxn->ops->head;

//         while (curOpNode != NULL) {
//             Op *curOp = ((Op *)curOpNode->key);

//             if (curOp->time > last) {
//                 last = curOp->time;
//             }

//             curOpNode = curOpNode->next;
//         }

//         curTxnNode = curTxnNode->next;
//     }

//     return last;
// }

int checkViewEquivalence(List *opsEmpilhadas, List *scaleAttrs) {
    Node *curOpNode = opsEmpilhadas->head;
    // Itera por todas as operações do escalonamento S' para avaliar sua equivalência com o S original
    while (curOpNode != NULL) {
        Op *curOp = ((Op *)curOpNode->key);
        Attr *curOpAttr = ((Attr *)ListFindKey(scaleAttrs, &curOp->attr, &compareAttrName));

        if (curOp->type == READ) {
            // Checa se não há writes anteriores ao read que deveriam estar após ele
            Node *prevNode = curOpNode->prev;
            int foundWritter = 0;
            while (prevNode != NULL && foundWritter == 0) {
                Op *prevOp = ((Op *)prevNode->key);

                if (prevOp->type == WRITE) {
                    // Checa se o primeiro WRITE encontrado for diferente do esperado ou sequer era esperado
                    if (curOp->lastWritter == -1 || curOp->lastWritter != prevOp->time) {
                        return 0;
                    } else {
                        foundWritter = 1;
                    }
                }

                prevNode = prevNode->prev;
            }
            // Checa se não foi encontrado WRITE em caso onde era esperado
            if (foundWritter == 0 && curOp->lastWritter != -1) {
                return 0;
            }
        } else if (curOp->type == WRITE && curOp->time == curOpAttr->lastWritter) {
            // Checa se não há writes posteriores após o que deveria ser o último
            Node *nexNode = curOpNode->next;
            while (nexNode != NULL) {
                Op *nextOp = ((Op *)nexNode->key);

                if (nextOp->type == WRITE) {
                    return 0;
                }

                nexNode = nexNode->next;
            }
        }

        curOpNode = curOpNode->next;
    }
    return 1;
}

int swapTxns(List *stackedOps, List *availableTxns, List *scaleAttrs) {
    int equiv = 0;
    if (ListIsEmpty(availableTxns)) {
        return checkViewEquivalence(stackedOps, scaleAttrs);
    } else {
        // Itera pelas transações ainda não empilhadas, realizando chamadas recursivas para cada caminho possível
        Node *curTxnNode = availableTxns->head;
        while (curTxnNode != NULL && equiv == 0) {
            Txn *curTxn = ((Txn *)curTxnNode->key);
            // Restaura o estado original das listas de empilhados e disponíveis (visto que a recursão as altera e desaloca)
            List *stackedOpsRec = ListCopy(stackedOps);
            List *availableTxnsRec = ListCopy(availableTxns);

            // Retira uma transação da lista das disponíveis e empilha suas operações na lista das empilhadas
            ListSoftRemoveKey(availableTxnsRec, curTxn, &compareTxns);
            Node *curOpNode = curTxn->ops->head;
            while (curOpNode != NULL) {
                ListInsertEnd(stackedOpsRec, curOpNode->key);
                curOpNode = curOpNode->next;
            }

            // Chama a recusão para avaliar as combinações possíveis para as transações ainda disponíveis
            equiv = swapTxns(stackedOpsRec, availableTxnsRec, scaleAttrs);

            // Desaloca as listas auxiliares que voltam alteradas da recursão
            ListSoftRemoveAll(stackedOpsRec);
            ListSoftRemoveAll(availableTxnsRec);
            free(availableTxnsRec);
            free(stackedOpsRec);

            curTxnNode = curTxnNode->next;
        }
        return equiv;
    }
}

int swapAndCheckEquivalence(Scale *s) {
    // Uma lista de operações já ordenadas conforme decorre a permutação. Inicia vazia.
    List *stackedOps = ListCreate();
    // Uma lista de transações cujas ordens ainda não foram definidas conforme decorre a permutação. Inicia com
    // todas as transações.
    List *availableTxns = ListCopy(s->txns);

    int equiv = swapTxns(stackedOps, availableTxns, s->attrs);

    ListSoftRemoveAll(stackedOps);
    ListSoftRemoveAll(availableTxns);
    free(stackedOps);
    free(availableTxns);

    return equiv;
}