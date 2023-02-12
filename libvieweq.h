#ifndef _LIBviewequiv_t_H
#define _LIBviewequiv_t_H

#include "liblist.h"
#include "libscale.h"

int lastWrite(Scale *s);

int checkViewEquivalence(List *opsEmpilhadas, int lastWrite);

int swapTxns(List *stackedTxns, List *availableTxns, int lastWrite);

int checkViewEquivalenceWrapper(Scale *s);

#endif