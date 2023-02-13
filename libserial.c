#include "libserial.h"
#include "libscale.h"

#include <stdio.h>
#include <stdlib.h>

void findEdges(Scale *s) {
    Node *txnNode = s->txns->head, *tgTxnNode, *opNode, *tgOpNode;
    Txn *curTxn, *tgTxn;
    Op *curOp, *tgOp;

    // Percorre todas as transações para verificar as propriedades para cada operação dentro de determinada transação
    for(int i = 0; i < s->txns->size; i++) {
        curTxn = txnNode->key;
        opNode = curTxn->ops->head;
        // Percorre todas as operações de curTxn; 
        for(int j = 0; j < curTxn->ops->size; j++) {
            curOp = opNode->key;
            tgTxnNode = s->txns->head;
            // Percorre todas as outras transações do escalonamento buscando as arestas
            for(int k = 0; k < s->txns->size; k++) {
                tgTxn = tgTxnNode->key;
                // Não precisa buscar arestas dentro da mesma transação
                if(tgTxn->id != curTxn->id) {
                    tgOpNode = tgTxn->ops->head;
                    // Percorre todas as operações fazendo as comparações
                    for(int l = 0; l < tgTxn->ops->size; l++) {
                        tgOp = tgOpNode->key;
                        // Verifica se estão acessando o mesmo atributo
                        if(tgOp->attr == curOp->attr) {
                            switch(curOp->type) {
                                // Aresta Ti -> Tj para cada w(x) em Tj(tgOp) depois de r(x) em Ti(curOp)
                                case READ:
                                    if((tgOp->time > curOp->time) && (tgOp->type == WRITE)) {
                                        if(ListFindKey(curTxn->edges, tgTxn, &compareTxns) == NULL)
                                            ListInsertEnd(curTxn->edges, tgTxn);
                                    }
                                    break;

                                // Aresta Ti -> Tj para cada r(x) ou w(x) em Tj(tgOp) depois de w(x) em Ti(curOp)
                                case WRITE:
                                    if((tgOp->time > curOp->time)) {
                                        if(ListFindKey(curTxn->edges, tgTxn, &compareTxns) == NULL)
                                            ListInsertEnd(curTxn->edges, tgTxn);
                                    }

                                default:
                                    break;
                            }
                        }
                        tgOpNode = tgOpNode->next;
                    }
                }
                tgTxnNode = tgTxnNode->next;
            }
            opNode = opNode->next;
        }
        txnNode = txnNode->next;
    }
}

int isSerial(List *txnEdges, int txnId) {
    Node *auxNode;
    Txn *auxTxn;

    if(txnEdges == NULL)
        return 1;

    auxNode = txnEdges->head;
    for(int i = 0; i < txnEdges->size; i++) {
        auxTxn = auxNode->key;
        if(auxTxn->id == txnId)
            return 0;
        
        if(!isSerial(auxTxn->edges, txnId))
            return 0;

        auxNode = auxNode->next;
    }

    return 1;
}

int checksSeriality(Scale *s) {
    Node *auxTxn = s->txns->head;
    Txn *curTxn;

    findEdges(s);
    
    while(auxTxn != NULL) {
        curTxn = auxTxn->key;
        if(!isSerial(curTxn->edges, curTxn->id)) {
            return 0;
        }
        auxTxn = auxTxn->next;
    }

    return 1;
}