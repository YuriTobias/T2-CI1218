// TXN := Transação

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "liblist.h"
#include "libscale.h"
#include "libstack.h"
#include "libvieweq.h"

List *readScales() {
    char *line = malloc(sizeof(char) * 9);
    List *scales, *openTxns;
    int time, txnId;
    char opCode, attr;

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
                ListInsertEnd(curTxn->ops, CreateOp(time, op, attr));
            } else {
                curTxn = CreateTxn(txnId);
                ListInsertEnd(curScale->txns, curTxn);
                ListInsertEnd(curTxn->ops, CreateOp(time, op, attr));
                ListInsertEnd(openTxns, curTxn);
            }
        }
    }

    free(line);
    ListDestroy(openTxns);
    return scales;
}

int main(int argc, char *argv[]) {
    List *scales = readScales();
    Node *curScale = scales->head;
    while (curScale != NULL) {
        printf("%i ", ((Scale *)curScale->key)->id);
        Node *curTxn = ((Scale *)curScale->key)->txns->head;
        printf("%i", ((Txn *)curTxn->key)->id);
        curTxn = curTxn->next;
        while (curTxn != NULL) {
            printf(",%i", ((Txn *)curTxn->key)->id);
            curTxn = curTxn->next;
        }
        printf(" ?? %s\n", (checkViewEquivalence(((Scale *)curScale->key))) ? "SV" : "NV");
        curScale = curScale->next;
    }
    ListDestroyScales(scales);

    return 0;
}