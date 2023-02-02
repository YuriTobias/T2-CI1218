#include <stdio.h>
#include <stdlib.h>

#include "libvieweq.h"

int lastWrite(Scale *s) {
    Node *curTxn = s->txns->head;
    int last = -1;
    // Itera nas operações do escalonamento a fim de achar o último WRITE
    while (curTxn != NULL) {
        Node *curOp = ((Txn *)curTxn->key)->ops->head;
        while (curOp != NULL) {
            if (((Op *)curOp->key)->time > last) {
                last = ((Op *)curOp->key)->time;
            }
            curOp = curOp->next;
        }
        curTxn = curTxn->next;
    }
    return last;
}

int checkViewEquivalence(List *opsEmpilhadas, int lastWrite) {
    Node *curNode = opsEmpilhadas->head;
    while (curNode != NULL) {
        Op *curOp = ((Op *)curNode->key);

        if (curOp->type == READ) {
            // Checa se não há writes anteriores ao read que deveriam estar após ele
            Node *prevNode = curNode->prev;
            while (prevNode != NULL) {
                Op *prevOp = ((Op *)prevNode->key);
                if (prevOp->type == WRITE && prevOp->time > curOp->time) {
                    return 0;
                }
                prevNode = prevNode->prev;
            }

        } else if (curOp->type == WRITE && curOp->time == lastWrite) {
            // Checa se não há writes posteriores após o que deveria ser o último
            Node *nexNode = curNode->next;
            while (nexNode != NULL) {
                Op *nextOp = ((Op *)nexNode->key);
                if (nextOp->type == WRITE && nextOp->time > curOp->time) {
                    return 0;
                }
                nexNode = nexNode->next;
            }
        }

        curNode = curNode->next;
    }
    return 1;
}

int swapTxns(List *stackedTxns, List *availableTxns, int lastWrite) {
    if (ListIsEmpty(availableTxns)) {
        return checkViewEquivalence(stackedTxns, lastWrite);

    } else {
        // Itera pelas transações ainda não empilhadas, realizando chamadas recursivas para cada caminho possível
        Node *curTxnNode = availableTxns->head;
        while (curTxnNode != NULL) {
            Txn *curTxn = ((Txn *)curTxnNode->key);
            // Empilha uma transações dentre as disponíveis e realiza a chamada recursiva
            List *stackedTxnsRec = ListCopy(stackedTxns);
            List *availableTxnsRec = ListCopy(availableTxns);
            ListRemoveTxn(availableTxnsRec, curTxn);

            Node *curOpNode = curTxn->ops->head;
            while (curOpNode != NULL) {
                ListInsertEnd(stackedTxnsRec, curOpNode->key);
                curOpNode = curOpNode->next;
            }

            if (swapTxns(stackedTxnsRec, availableTxnsRec, lastWrite) == 1) {
                ListSoftRemoveAll(stackedTxnsRec);
                ListSoftRemoveAll(availableTxnsRec);
                free(availableTxnsRec);
                free(stackedTxnsRec);
                return 1;
            }

            ListSoftRemoveAll(stackedTxnsRec);
            ListSoftRemoveAll(availableTxnsRec);
            free(availableTxnsRec);
            free(stackedTxnsRec);
            curTxnNode = curTxnNode->next;
        }
        return 0;
    }
}

int checkViewEquivalenceWrapper(Scale *s) {
    // Empilhará as transações em todas as ordens possíveis
    List *stackedTxns = ListCreate();         // Lista vazia com os nodos empilhados
    List *availableTxns = ListCopy(s->txns);  // Lista com os nodos ainda disponíveis para empilhar (todos)

    if (swapTxns(stackedTxns, availableTxns, lastWrite(s)) == 1) {
        ListSoftRemoveAll(stackedTxns);
        ListSoftRemoveAll(availableTxns);
        free(stackedTxns);
        free(availableTxns);
        return 1;
    }
    ListSoftRemoveAll(stackedTxns);
    ListSoftRemoveAll(availableTxns);
    free(stackedTxns);
    free(availableTxns);
    return 0;
}