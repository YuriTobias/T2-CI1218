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

Txn *ListFindTxn(List *l, int id);

Scale *CreateScale(int id);

Op *CreateOp(int time, OpType type, char attr);

Txn *CreateTxn(int id);

Scale *ListInsertScale(List *scales, Scale *curScale);

OpType ConvertOpType(char c);

void ListDestroyScales(List *scales);
void *ListRemoveTxn(List *l, Txn *key);
int ListContainsTxn(List *l, Txn *key);
int compareTxns(void *txnA, void *txnB);

#endif