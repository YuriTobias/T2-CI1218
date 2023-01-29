#ifndef _LIBescalona_t_H
#define _LIBescalona_t_H

#include "liblist.h"

typedef struct txn_t {
    int id;
    list_t *ops;
    list_t *edges;
} txn_t;

typedef struct op_t {
    int time;
    char type;
    char attr;
} op_t;

typedef struct scale_t {
    int id;
    int serial;
    int equiv;
    list_t *txns;
} scale_t;

txn_t *list_contains_txn(list_t *l, int id);

scale_t *createScale(int id);

op_t *createOp(int time, char type, char attr);

txn_t *createTxn(int id);

void imprime_operacoes(list_t *scales);

#endif