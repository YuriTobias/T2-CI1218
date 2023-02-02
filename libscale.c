#include "libscale.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liblist.h"

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

Scale *ListInsertScale(List *scales, Scale *curScale) {
    Scale *newScale = CreateScale(curScale == NULL ? 0 : curScale->id + 1);
    ListInsertStart(scales, newScale);
    return newScale;
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
    Node *curScNode = scales->head;
    while (curScNode != NULL) {
        Scale *curScale = ((Scale *)curScNode->key);
        Node *curTxnNode = ((Scale *)curScNode->key)->txns->head;
        while (curTxnNode != NULL) {
            Txn *curTxn = ((Txn *)curTxnNode->key);
            ListHardDestroy(curTxn->ops);
            ListHardDestroy(curTxn->edges);
            Node *target = curTxnNode;
            curTxnNode = curTxnNode->next;
            free(target->key);
            free(target);
        }
        free(curScale->txns);
        Node *target = curScNode;
        curScNode = curScNode->next;
        free(target->key);
        free(target);
    }
    free(scales);
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

int compareTxns(void *txnA, void *txnB) { return (((Txn *)txnA)->id == ((Txn *)txnB)->id); }