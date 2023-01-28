#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"
#define TAM 1000

lista_t *lista_cria () {
    lista_t *l;
    l = malloc(sizeof(lista_t));
    if (l == NULL)
        return NULL;

    l->ini = malloc(sizeof(nodo_l_t));
    if (l->ini == NULL) {
        free(l);
        return NULL;
    }

    l->ini->prox = malloc(sizeof(nodo_l_t));
    if (l->ini->prox == NULL) {
        free(l->ini);
        free(l);
        return NULL;
    }

    l->ini->elemento = 0;
    l->ini->prox = NULL;
    l->tamanho = 0;
    
    return l;
}

lista_t* lista_destroi (lista_t* l) {
    int i, limite;
    int *elem;
    elem = malloc(sizeof(int));
    limite = lista_tamanho(l);

    for (i = 0; i < limite; i++)
        lista_retira_fim(l, elem);
    
    l->ini->prox = NULL;
    l->ini->elemento = 0;
    l->tamanho = 0;
    free(elem);
    free(l->ini->prox);
    free(l->ini);
    free(l);

    return NULL;
}

int lista_vazia (lista_t* l) {
    if (lista_tamanho(l) != 0)
        return 0;
    return 1;
}

int lista_tamanho (lista_t* l) {
    return l->tamanho;
}

int lista_insere_inicio (lista_t* l, int elemento) {
    if(lista_tamanho(l) == TAM)
        return 0;
    
    nodo_l_t *novo_nodo;
    novo_nodo = malloc(sizeof(nodo_l_t));
    if (novo_nodo == NULL)
        return 0;
    novo_nodo->elemento = elemento;
    novo_nodo->prox = l->ini->prox;

    l->ini->prox = novo_nodo;
    l->tamanho++;

    return 1;
}

int lista_insere_fim (lista_t* l, int elemento) {
    if(lista_tamanho(l) == TAM)
        return 0;
    
    nodo_l_t *novo_nodo, *aux;
    novo_nodo = malloc(sizeof(nodo_l_t));
    if (novo_nodo == NULL)
        return 0;
    novo_nodo->elemento = elemento;
    novo_nodo->prox = NULL;

    aux = malloc(sizeof(nodo_l_t));
    if (aux == NULL)
        return 0;
    aux->prox = l->ini->prox;

    if (lista_tamanho(l) != 0) {
        while (aux->prox->prox != NULL) {
            aux->prox = aux->prox->prox;
        }
    }

    if (lista_tamanho(l) == 0)
        l->ini->prox = novo_nodo;
    else
        aux->prox->prox = novo_nodo;
    l->tamanho++;

    free(aux); 
    return 1;    
}

/* Primeiro verifica overflow,
 * Segundo, enquanto nao for para colocar o elemento o aux avanca para o proximo nodo,
 * Quando a posicao certa eh encontrada, 
 * o aux estara apontando para o nodo com valor menor ao que sera inserido,
 * entao eh so inserir o novo_nodo e acertar os ponteiros; */
int lista_insere_ordenado (lista_t* l, int elemento) {
    if(lista_tamanho(l) == TAM)
        return 0;

    int colocou = 0;

    nodo_l_t *novo_nodo, *aux;
    novo_nodo = malloc(sizeof(nodo_l_t));
    if (novo_nodo == NULL)
        return 0;
    novo_nodo->elemento = elemento;
    novo_nodo->prox = NULL;

    aux = malloc(sizeof(nodo_l_t));
    if (aux == NULL)
        return 0;
    aux->prox = l->ini;
    
    if (lista_tamanho(l) == 0)
        aux->prox->prox = NULL;

    while (!colocou) {
        if (aux->prox->prox != NULL) {
            if ((aux->prox->prox->elemento != 0) && (aux->prox->prox->elemento < elemento))
                aux->prox = aux->prox->prox;
            else
                colocou = 1;
        } else {
            colocou = 1;
        }
    }

    if (aux->prox->prox != NULL) {
        novo_nodo->prox = aux->prox->prox;
        aux->prox->prox = novo_nodo;
    } else {
        aux->prox->prox = novo_nodo;
    }
    l->tamanho++;

    free(aux);
    return 1;
}

int lista_retira_inicio (lista_t* l, int* elemento) {
    if(lista_tamanho(l) == 0)
        return 0;
    
    nodo_l_t *aux;
    aux = malloc(sizeof(nodo_l_t));
    if (aux == NULL)
        return 0;
    aux->prox = l->ini->prox->prox;
    *elemento = l->ini->prox->elemento;

    l->ini->prox->elemento = 0;
    l->ini->prox->prox = NULL;
    free(l->ini->prox);
    l->ini->prox = aux->prox;
    l->tamanho--;

    aux->prox = NULL;
    free(aux);

    return 1;
}

/* Primeiro verifica se na lista nao existe um unico elemento,
 * Se for o caso, simplesmente remove este unico nodo,
 * Se nao, busca o ultimo elemento, ou seja, prox == NULL,
 * Quando este for encontrado, aux apontara para o penultimo elemento,
 * Ai eh so remover o ultimo e acertar os ponteiros; */
int lista_retira_fim (lista_t* l, int* elemento) {
    if (lista_tamanho(l) == 0)
        return 0;

    nodo_l_t *aux;
    aux = malloc(sizeof(nodo_l_t));
    if (aux == NULL)
        return 0;
    aux->prox = l->ini->prox;

    if (lista_tamanho(l) == 1) {
        *elemento = l->ini->prox->elemento;
        l->ini->prox->elemento = 0;
        l->ini->prox->prox = NULL;
        free(l->ini->prox);
    }

    if (lista_tamanho(l) > 1) {
        while (aux->prox->prox->prox != NULL) {
            aux->prox = aux->prox->prox;
        }
        *elemento = aux->prox->prox->elemento;
        aux->prox->prox->elemento = 0;
        aux->prox->prox->prox = NULL;
        free(aux->prox->prox);
        aux->prox->prox = NULL;
    }
    l->tamanho--;

    free(aux);
    return 1;
}

/* Cria dois auxs, um que aponta pro elemento a ser removido se for o caso,
 * E o outro pro elemento anterior para acertar os ponteitos; 
 * Primeiro verifica se o elemento ja se encontra no primeiro nodo,
 * Se sim, acerta os ponteiros e remove o nodo,
 * Se nao, faz a busca para os demais nodos; */
int lista_retira_elemento (lista_t *l, int *elemento) {
    nodo_l_t *aux, *auxAnt;
    aux = malloc(sizeof(nodo_l_t));
    if (aux == NULL)
        return 0;
    aux->prox = l->ini->prox;

    auxAnt = malloc(sizeof(nodo_l_t));
    if (auxAnt == NULL)
        return 0;
    
    if (*elemento == aux->prox->elemento) {
        l->ini->prox = aux->prox->prox;
        aux->prox->elemento = 0;
        aux->prox->prox = NULL;
        free(aux->prox);
        l->tamanho--;
        return 1;
    } else {
        while (aux->prox->prox != NULL) {
            auxAnt->prox = aux->prox;
            aux->prox = aux->prox->prox;
            if(*elemento == aux->prox->elemento) {
                auxAnt->prox->prox = aux->prox->prox;
                aux->prox->elemento = 0;
                aux->prox->prox = NULL;
                free(aux->prox);
                l->tamanho--;
                return 1;
            }
        }
    }

    free(aux);
    free(auxAnt);
    return 0;
}

int lista_pertence (lista_t* l, int elemento) {
    nodo_l_t *aux;
    aux = malloc(sizeof(nodo_l_t));
    if (aux == NULL)
        return 0;
    aux->prox = l->ini->prox;

    if (elemento == aux->prox->elemento)
        return 1;

    if (lista_tamanho(l) > 1) {
        while (aux->prox->prox != NULL) {
            aux->prox = aux->prox->prox;
            if(elemento == aux->prox->elemento)
                return 1;
        }
    }

    return 0;
}

void lista_imprime (lista_t* l) {
    int limite = l->tamanho;

    if (limite != 0) {
        int i;
        nodo_l_t *aux;
        aux = malloc(sizeof(nodo_l_t));
        aux = l->ini->prox;

        for (i = 0; i < limite; i++) {
            if(i < limite -1)
                printf("%d ", aux->elemento);
            else
                printf("%d", aux->elemento);
            aux = aux->prox;
        }
        printf("\n");

        free(aux);
    }
}