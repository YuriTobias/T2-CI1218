#include "liblist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */
List *ListCreate() {
    List *list;
    if (!(list = malloc(sizeof(List)))) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

Node *ListCreateNode(void *key) {
    Node *node;
    if (!(node = malloc(sizeof(Node)))) {
        return NULL;
    }
    node->key = key;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
 */
List *ListDestroy(List *l) {
    Node *ini = l->head;
    while (ini != NULL) {
        Node *target = ini;
        ini = ini->next;
        free(target->key);
        free(target);
    }
    free(l);
    return NULL;
}

List *ListRemoveAll(List *l) {
    Node *ini = l->head;
    while (ini != NULL) {
        Node *target = ini;
        ini = ini->next;
        free(target->key);
        free(target);
    }
    l->head = NULL;
    l->size = 0;
    return NULL;
}

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
 */
int ListIsEmpty(List *l) {
    if (l->size == 0) {
        return 1;
    }
    return 0;
}

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
 */
int ListSize(List *l) { return l->size; }

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int ListInsertStart(List *l, void *key) {
    Node *node = NULL;
    node = ListCreateNode(key);
    if (node != NULL) {
        if (ListIsEmpty(l)) {
            l->head = node;
        } else {
            node->next = l->head;
            l->head->prev = node;
            l->head = node;
        }
        l->size++;
        return 1;
    }
    return 0;
}

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int ListInsertEnd(List *l, void *key) {
    Node *node = NULL;
    node = ListCreateNode(key);
    if (node != NULL) {
        if (ListIsEmpty(l)) {
            l->head = node;
        } else {
            Node *target = l->head;
            while (target->next != NULL) {
                target = target->next;
            }
            target->next = node;
            node->prev = target;
        }
        l->size++;
        return 1;
    }
    return 0;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
void *ListRemoveStart(List *l) {
    if (!ListIsEmpty(l)) {
        Node *target = l->head;
        l->head = target->next;

        void *removed = (target->key);
        free(target);
        l->size--;
        return removed;
    }
    return NULL;
}

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
void *ListRemoveEnd(List *l) {
    if (!ListIsEmpty(l)) {
        Node *target = l->head;
        while (target->next) {
            target = target->next;
        }

        if (target->prev) {
            target->prev->next = NULL;
        }

        void *removed = (target->key);
        free(target);
        l->size--;
        return removed;
    }
    return NULL;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
 */
void *ListRemoveKey(List *l, void *key) {
    if (!ListIsEmpty(l) && ListContains(l, key)) {
        Node *target = l->head;

        while (target->key != key) {
            target = target->next;
        }

        if (target->prev) {
            target->prev->next = target->next;
        } else {
            l->head = target->next;
        }

        if (target->next) {
            target->next->prev = target->prev;
        }

        void *removed = (target->key);
        free(target);
        l->size--;
        return removed;
    }
    return NULL;
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
 */
int ListContains(List *l, void *key) {
    if (!ListIsEmpty(l)) {
        Node *target = l->head;
        while (target != NULL) {
            if (target->key == key) {
                return 1;
            }
            target = target->next;
        }
    }
    return 0;
}