#include "escalona.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liblist.h"

txn_t *list_contains_txn(list_t *l, int id) {
    if (!is_list_empty(l)) {
        node_l_t *target = l->head;
        while (target != NULL) {
            if (((txn_t *)target->key)->id == id) {
                return ((txn_t *)target->key);
            }
            target = target->next;
        }
    }
    return NULL;
}

scale_t *createScale(int id) {
    scale_t *s = malloc(sizeof(scale_t));
    s->id = id;
    s->equiv = 0;
    s->serial = 0;
    s->txns = create_list();
    return s;
}

op_t *createOp(int time, char type, char attr) {
    op_t *o = malloc(sizeof(op_t));
    o->time = time;
    o->attr = attr;
    o->type = type;
    return o;
}

txn_t *createTxn(int id) {
    txn_t *t = malloc(sizeof(txn_t));
    t->id = id;
    t->ops = create_list();
    t->edges = create_list();
    return t;
}

void imprime_operacoes(list_t *scales) {
    node_l_t *cur_sc = scales->head;
    while (cur_sc != NULL) {
        getchar();
        node_l_t *cur_tx = (((scale_t *)cur_sc->key)->txns->head);
        while (cur_tx != NULL) {
            getchar();
            node_l_t *cur_op = (((txn_t *)cur_tx->key)->ops->head);
            while (cur_op != NULL) {
                getchar();
                op_t *op = ((op_t *)cur_op->key);
                txn_t *txn = ((txn_t *)cur_tx->key);
                scale_t *scale = ((scale_t *)cur_sc->key);
                printf("%i %i %i %c %c\n", scale->id, op->time, txn->id, op->type, op->attr);
                getchar();
                cur_op = cur_op->next;
            }
            cur_tx = cur_tx->next;
        }
        cur_sc = cur_sc->next;
    }
}