#ifndef _LIBlist_t_H
#define _LIBlist_t_H

struct node_l {
    void* key;           /* lista de numeros inteiros */
    struct node_l* prev; /* ponteiro para o proximo   */
    struct node_l* next; /* ponteiro para o proximo   */
};
typedef struct node_l node_l_t;

struct list {
    node_l_t* head; /* ponteiro para o inicio da lista */
    int size;       /* numero de elementos na lista    */
};
typedef struct list list_t;

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */
list_t* create_list();

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
 */
list_t* destroy_list(list_t* l);

list_t* empty_list(list_t* l);

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
 */
int is_list_empty(list_t* l);

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
 */
int list_size(list_t* l);

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int list_insert_start(list_t* l, void* key);

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int list_insert_end(list_t* l, void* key);

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int list_remove_start(list_t* l);

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int list_remove_end(list_t* l);

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
 */
int list_remove_key(list_t* l, void* key);

int list_remove_node(list_t* l, void* key);

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
 */
int list_contains(list_t* l, void* key);

#endif