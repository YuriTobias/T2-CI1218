#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "liblist.h"
#include "libscale.h"
#include "libstack.h"
#include "libvieweq.h"

List *readScales() {
    char *line = malloc(sizeof(char) * 255);
    List *scales, *openTxns;
    int time, txnId;
    Scale *curScale = NULL;
    char opCode, attrName;

    scales = ListCreate();    // Lista de escalonamentos
    openTxns = ListCreate();  // Lista de transações em andamento

    while (fgets(line, 255, stdin)) {
        // Cria um novo escalonamento se não há transações ativas
        if (ListIsEmpty(openTxns)) {
            curScale = ListInsertScale(scales, curScale);
        }

        sscanf(line, "%d %d %c %c", &time, &txnId, &opCode, &attrName);
        // Busca a transação com o timestamp fornecido
        Txn *curTxn = ListFindKey(curScale->txns, &txnId, &compareTxnId);
        Attr *curAttr = ListFindKey(curScale->attrs, &attrName, &compareAttrName);
        OpType op = ConvertOpType(opCode);

        if (op == COMMIT) {
            ListSoftRemoveKey(openTxns, curTxn, &compareTxns);
        } else {
            // Se o atributo operado não está na lista de atributos do escalonamento, insere-o
            if (curAttr == NULL) {
                curAttr = CreateAttr(attrName);
                ListInsertEnd(curScale->attrs, curAttr);
            }

            if (op == WRITE) {
                curAttr->lastWritter = time;
            }

            if (curTxn != NULL) {
                // Se o timestamp fornecido for de uma transação existente, apenas insere a operação
                ListInsertEnd(curTxn->ops, CreateOp(time, op, attrName, curAttr->lastWritter));
            } else {
                // Cria também a transação se o timestamp fornecido não pertencer a transação existente
                curTxn = CreateTxn(txnId);
                ListInsertEnd(curScale->txns, curTxn);
                ListInsertEnd(curTxn->ops, CreateOp(time, op, attrName, curAttr->lastWritter));
                // Insere a transação na lista de transações abertas
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
        curSc->serial = 0;
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