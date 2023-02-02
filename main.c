// TXN := Transação

#include <stdio.h>
#include <stdlib.h>

#include "liblist.h"
#include "libscale.h"
#include "libstack.h"

int main(int argc, char *argv[]) {
    int time, txnId;
    char opCode, attr;
    char *line = malloc(sizeof(char) * 9);
    List *scales, *openTxns;

    scales = ListCreate();    // Lista de escalonamentos
    openTxns = ListCreate();  // Lista de transações em andamento

    while (fgets(line, 9, stdin)) {
        if (ListIsEmpty(openTxns)) {
            ListInsertScale(scales);
        }

        Scale *curScale = (Scale *)scales->head->key;
        sscanf(line, "%d %d %c %c", &time, &txnId, &opCode, &attr);
        Txn *curTxn = ListFindTxn(curScale->txns, txnId);
        OpType op = ConvertOpType(opCode);

        if (op == COMMIT) {
            ListRemoveKey(openTxns, curTxn);
        } else {
            if (curTxn != NULL) {
                ListInsertStart(curTxn->ops, CreateOp(time, op, attr));
            } else {
                curTxn = CreateTxn(txnId);
                ListInsertStart(curScale->txns, curTxn);
                ListInsertStart(curTxn->ops, CreateOp(time, op, attr));
                ListInsertStart(openTxns, curTxn);
            }
        }
    }

    free(line);
    ListDestroy(openTxns);
    ListDestroyScales(scales);

    return 0;
}