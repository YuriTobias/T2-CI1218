#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "liblist.h"
#include "libscale.h"
#include "libstack.h"
#include "libvieweq.h"
#include "libserial.h"

List *readScales() {
    char *line = malloc(sizeof(char) * 255);
    List *scales, *openTxns;
    int time, txnId;
    Scale *curScale = NULL;
    char opCode, attr;

    scales = ListCreate();    // Lista de escalonamentos
    openTxns = ListCreate();  // Lista de transações em andamento

    while (fgets(line, 255, stdin)) {
        if (ListIsEmpty(openTxns)) {
            curScale = ListInsertScale(scales, curScale);
        }

        sscanf(line, "%d %d %c %c", &time, &txnId, &opCode, &attr);
        Txn *curTxn = ListFindKey(curScale->txns, &txnId, &compareTxnId);
        OpType op = ConvertOpType(opCode);

        if (op == COMMIT) {
            ListSoftRemoveKey(openTxns, curTxn, &compareTxns);
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
    ListHardDestroy(openTxns);
    return scales;
}

void checkResults(List *scales) {
    Node *curScNode = scales->head;

    while (curScNode != NULL) {
        Scale *curSc = ((Scale *)curScNode->key);
        curSc->serial = (checksSeriality(curSc));
        curSc->equiv = (swapAndCheckEquivalence(curSc));
        curScNode = curScNode->next;
    }
}

void printResults(List *scales) {
    Node *curScNode = scales->head;

    while (curScNode != NULL) {
        Scale *curSc = ((Scale *)curScNode->key);
        printf("%i ", curSc->id);

        Node *curTxnNode = curSc->txns->head;
        Txn *curTxn = ((Txn *)curTxnNode->key);
        printf("%i", curTxn->id);

        curTxnNode = curTxnNode->next;
        while (curTxnNode != NULL) {
            curTxn = ((Txn *)curTxnNode->key);
            printf(",%i", curTxn->id);
            curTxnNode = curTxnNode->next;
        }

        printf(" %s", curSc->serial ? "SS" : "NS");
        printf(" %s\n", curSc->equiv ? "SV" : "NV");
        curScNode = curScNode->next;
    }
}

int main(int argc, char *argv[]) {
    List *scales = readScales();
    checkResults(scales);
    printResults(scales);
    ListDestroyScales(scales);

    return 0;
}