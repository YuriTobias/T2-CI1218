// TXN := Transação

#include <stdio.h>
#include <stdlib.h>

#include "escalona.h"
#include "liblist.h"
#include "libstack.h"

typedef enum { READ, WRITE, COMMIT } OpType;

int main(int argc, char *argv[]) {
    int time, txn_id;
    char op, attr;
    char *line = malloc(sizeof(char) * 9);
    list_t *scales, *open_txns;

    scales = create_list();
    open_txns = create_list();

    while (fgets(line, 9, stdin)) {
        if (is_list_empty(open_txns)) {
            list_insert_start(scales, createScale(is_list_empty(scales) ? 0 : ((scale_t *)scales->head->key)->id + 1));
        }
        sscanf(line, "%d %d %c %c", &time, &txn_id, &op, &attr);
        if (op != 'C') {
            txn_t *target = list_contains_txn(((scale_t *)scales->head->key)->txns, txn_id);
            if (target != NULL) {
                list_insert_start(target->ops, createOp(time, op, attr));
            } else {
                target = createTxn(txn_id);
                list_insert_start(((scale_t *)scales->head->key)->txns, target);
                list_insert_start(target->ops, createOp(time, op, attr));
                list_insert_start(open_txns, target);
            }
        } else {
            txn_t *target = list_contains_txn(((scale_t *)scales->head->key)->txns, txn_id);
            list_remove_node(open_txns, target);
        }
    }
    imprime_operacoes(scales);

    return 0;
}