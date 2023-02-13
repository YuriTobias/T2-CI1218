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
    s->attrs = ListCreate();
    return s;
}

Op *CreateOp(int time, OpType type, char attr, int lastWritter) {
    Op *o = malloc(sizeof(Op));
    o->time = time;
    o->attr = attr;
    o->type = type;
    o->lastWritter = lastWritter;
    return o;
}

Attr *CreateAttr(char name) {
    Attr *a = malloc(sizeof(Attr));
    a->name = name;
    a->lastWritter = -1;
    return a;
}

Txn *CreateTxn(int id) {
    Txn *t = malloc(sizeof(Txn));
    t->id = id;
    t->ops = ListCreate();
    t->edges = ListCreate();
    return t;
}

Scale *ListInsertScale(List *scales, Scale *curScale) {
    Scale *newScale = CreateScale(curScale == NULL ? 1 : curScale->id + 1);
    ListInsertEnd(scales, newScale);
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
            curTxnNode = curTxnNode->next;
        }

        ListHardDestroy(curScale->txns);
        ListHardDestroy(curScale->attrs);
        curScNode = curScNode->next;
    }
    ListHardDestroy(scales);
}

int compareTxns(void *txnA, void *txnB) { return (((Txn *)txnA)->id == ((Txn *)txnB)->id); }
int compareTxnId(void *txn, void *id) { return (((Txn *)txn)->id == (*(int *)id)); }
int compareAttrs(void *attrA, void *attrB) { return (((Attr *)attrA)->name == ((Attr *)attrB)->name); }
int compareAttrName(void *attr, void *name) { return (((Attr *)attr)->name == (*(char *)name)); }