#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"

pilha_t *pilha_cria (int nelem) {
    pilha_t *p;
    p = malloc(sizeof(pilha_t));
    if (p == NULL)
        return NULL;
    p->elems = malloc(sizeof(int)*nelem);
    if (p->elems == NULL) {
        free(p);
        return NULL;
    }
    p->topo = 0;
    p->nelem = nelem;
    return p;
}

int push (pilha_t *p, int elem) {
    if (p->topo == p->nelem) {
        return -1;
    }
    p->elems[p->topo] = elem;
    p->topo++;
    return p->topo;
}

int pop (pilha_t *p) {
    if (pilha_vazia(p))
        return 0;
    p->topo--;
    int tmp = p->elems[p->topo];
    p->elems[p->topo] = 0;
    return tmp;
}

int pilha_topo (pilha_t *p) {
    if (pilha_tamanho(p) == 0)
        return p->topo; 
    return p->elems[p->topo - 1];
}

int pilha_tamanho (pilha_t* p) {
    return p->topo;
}

int pilha_vazia (pilha_t *p) {
    if (p->topo != 0)
        return 0;
    return 1;
}

pilha_t *pilha_destroi (pilha_t *p) {
    int i;
    for (i = p->topo - 1; i >= 0; i--)
        p->elems[i] = 0;
    p->topo = 0;
    p->nelem = 0;
    free(p->elems);
    free(p);
    return NULL;
}

void pilha_imprime (pilha_t* p) {
    int i;
    for (i = 0; i < pilha_tamanho(p); i++)
        printf("%d ", p->elems[i]);
    if (pilha_tamanho(p) != 0) 
        printf("\n");
}