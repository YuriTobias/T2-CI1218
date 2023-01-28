//TXN := Transação

#include <stdio.h>
#include "liblista.h"

typedef struct txn_t {
  int id;
  lista_t *ops;
  lista_t *edges;
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
  lista_t *txns;
} scale_t;

void listAdd(){
    
}

void* createScale(){

}

void* createTxn(){

}

void* listLast(){

}

void* listRemove(){

}

void* listIsEmpty(){

}

int main(int argc, char *argv[]) {
    int time, txn_id;
    char op, attr;
    char *line = malloc(sizeof(char) * 9);
    list_t *scales, *open_txns;

    listAdd(scales, createScale(1));

    while (fgets(line, 9, stdin)) {
        sscanf(line, "%d %d %c %c", &time, &txn_id, &op, &attr);
        if(op!='C'){
            listaAdd(((scale_t*)listLast(scales))->txns, createTxn(time, txn_id, op, attr));
            listaAdd(open_txns, txn_id);
        }else{
            listRemove(open_txns, txn_id);
        }

        if(listIsEmpty(open_txns)){
            listAdd(scales, createScale((((scale_t *)listLast)->id)+1));
        }
    }

    return 0;
}