#include <stdio.h>
#include <stdlib.h>

#include "libvieweq.h"

int ListContainsTxn(List *l, Txn *key) {
    if (!ListIsEmpty(l)) {
        Node *target = l->head;
        while (target != NULL) {
            if (((Txn *)target->key)->id == key->id) {
                return 1;
            }
            target = target->next;
        }
    }
    return 0;
}

int lastWrite(Scale *s) {
    Node *curTxn = s->txns->head;
    int last = -1;
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

void *ListRemoveTxn(List *l, Txn *key) {
    if (!ListIsEmpty(l) && ListContainsTxn(l, key)) {
        Node *target = l->head;

        while (((Txn *)target->key)->id != key->id) {
            target = target->next;
        }

        if (target->prev) {
            target->prev->next = target->next;
        } else {
            l->head = target->next;
        }

        if (target->next) {
            target->next->prev = target->prev;
        }

        void *removed = (target->key);
        free(target);
        l->size--;
        return removed;
    }
    return NULL;
}

int checkEquivalence(List *opsEmpilhadas, int lastWrite) {
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

int permutaTxns(List *stackedTxns, List *availableTxns, int lastWrite) {
    if (ListIsEmpty(availableTxns)) {
        // Node *c = stackedTxns->head;
        // while (c != NULL) {
        //     printf("%i ", ((Op *)c->key)->time);
        //     c = c->next;
        // }
        // printf("%s\n", checkEquivalence(stackedTxns, lastWrite) ? "Equivalente" : "Não Equivalente");
        return checkEquivalence(stackedTxns, lastWrite);
    } else {
        Node *curNode = availableTxns->head;
        while (curNode != NULL) {
            List *stackedTxnsRec = ListCopy(stackedTxns);
            List *availableTxnsRec = ListCopy(availableTxns);
            ListRemoveTxn(availableTxnsRec, ((Txn *)curNode->key));

            Node *opAtual = ((Txn *)curNode->key)->ops->head;
            while (opAtual != NULL) {
                ListInsertEnd(stackedTxnsRec, opAtual->key);
                opAtual = opAtual->next;
            }

            if (permutaTxns(stackedTxnsRec, availableTxnsRec, lastWrite) == 1) {
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
            curNode = curNode->next;
        }
        return 0;
    }
}

int checkViewEquivalence(Scale *s) {
    // Empilhará as transações em todas as ordens possíveis
    List *stackedTxns = ListCreate();         // Lista vazia com os nodos empilhados
    List *availableTxns = ListCopy(s->txns);  // Lista com os nodos ainda disponíveis para empilhar (todos)

    if (permutaTxns(stackedTxns, availableTxns, lastWrite(s)) == 1) {
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