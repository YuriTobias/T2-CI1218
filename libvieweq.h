#ifndef _LIBviewequiv_t_H
#define _LIBviewequiv_t_H

#include "liblist.h"
#include "libscale.h"

int ListContainsTxn(List *l, Txn *key);

int lastWrite(Scale *s);

void *ListRemoveTxn(List *l, Txn *key);

int checkEquivalence(List *opsEmpilhadas, int lastWrite);

int permutaTxns(List *stackedTxns, List *availableTxns, int lastWrite);

int checkViewEquivalence(Scale *s);

#endif