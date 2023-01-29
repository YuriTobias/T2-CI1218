#include "libscale.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liblist.h"

Txn *ListFindTxn(List *l, int id) {
    if (!ListIsEmpty(l)) {
        Node *target = l->head;
        while (target != NULL) {
            if (((Txn *)target->key)->id == id) {
                return ((Txn *)target->key);
            }
            target = target->next;
        }
    }
    return NULL;
}

Scale *CreateScale(int id) {
    Scale *s = malloc(sizeof(Scale));
    s->id = id;
    s->equiv = 0;
    s->serial = 0;
    s->txns = ListCreate();
    return s;
}

Op *CreateOp(int time, OpType type, char attr) {
    Op *o = malloc(sizeof(Op));
    o->time = time;
    o->attr = attr;
    o->type = type;
    return o;
}

Txn *CreateTxn(int id) {
    Txn *t = malloc(sizeof(Txn));
    t->id = id;
    t->ops = ListCreate();
    t->edges = ListCreate();
    return t;
}

// void ImprimeOperacoes(List *scales) {
//     Node *cur_sc = scales->head;
//     while (cur_sc != NULL) {
//         getchar();
//         Node *cur_tx = (((Scale *)cur_sc->key)->txns->head);
//         while (cur_tx != NULL) {
//             getchar();
//             Node *cur_op = (((Txn *)cur_tx->key)->ops->head);
//             while (cur_op != NULL) {
//                 getchar();
//                 Op *op = ((Op *)cur_op->key);
//                 Txn *txn = ((Txn *)cur_tx->key);
//                 Scale *scale = ((Scale *)cur_sc->key);
//                 printf("%i %i %i %c %c\n", scale->id, op->time, txn->id, op->type, op->attr);
//                 getchar();
//                 cur_op = cur_op->next;
//             }
//             cur_tx = cur_tx->next;
//         }
//         cur_sc = cur_sc->next;
//     }
// }

void ListInsertScale(List *scales) {
    ListInsertStart(scales, CreateScale(ListIsEmpty(scales) ? 0 : ((Scale *)scales->head->key)->id + 1));
}

OpType ConvertOpType(char c) {
    switch (c) {
        case 'R':
            return READ;
        case 'W':
            return WRITE;
        case 'C':
            return COMMIT;

        default:
            return INVALID;
    }
}

void ListDestroyScales(List *scales) {
    Node *curSc = scales->head;
    while (curSc != NULL) {
        Node *curTx = ((Scale *)curSc->key)->txns->head;
        while (curTx != NULL) {
            Node *curOp = ((Txn *)curTx->key)->ops->head;
            while (curOp != NULL) {
                Node *target = curOp;
                curOp = curOp->next;
                free(target->key);
                free(target);
            }
            free(((Txn *)curTx->key)->ops);
            Node *curEd = ((Txn *)curTx->key)->edges->head;
            while (curEd != NULL) {
                Node *target = curEd;
                curEd = curEd->next;
                free(target->key);
                free(target);
            }
            free(((Txn *)curTx->key)->edges);
            Node *target = curTx;
            curTx = curTx->next;
            free(target->key);
            free(target);
        }
        free(((Scale *)curSc->key)->txns);
        Node *target = curSc;
        curSc = curSc->next;
        free(target->key);
        free(target);
    }
    free(scales);
}