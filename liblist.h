#ifndef _LIBlist_t_H
#define _LIBlist_t_H

typedef struct Node {
    void* key;         /* lista de numeros inteiros */
    struct Node* prev; /* ponteiro para o proximo   */
    struct Node* next; /* ponteiro para o proximo   */
} Node;

typedef struct List {
    Node* head; /* ponteiro para o inicio da lista */
    int size;   /* numero de elementos na lista    */
} List;

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */
List* ListCreate();

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
 */
List* ListDestroy(List* l);

List* ListRemoveAll(List* l);

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
 */
int ListIsEmpty(List* l);

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
 */
int ListSize(List* l);

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int ListInsertStart(List* l, void* key);

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int ListInsertEnd(List* l, void* key);

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
void* ListRemoveStart(List* l);

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
void* ListRemoveEnd(List* l);

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
 */
void* ListRemoveKey(List* l, void* key);

int list_remove_node(List* l, void* key);

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
 */
int ListContains(List* l, void* key);

#endif