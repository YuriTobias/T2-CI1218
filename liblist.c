#include "liblist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
 */
list_t *create_list() {
  list_t *list;
  if (!(list = malloc(sizeof(list_t)))) {
    return NULL;
  }
  list->head = NULL;
  list->size = 0;
  return list;
}

node_l_t *create_node(void *key) {
  node_l_t *node;
  if (!(node = malloc(sizeof(node_l_t)))) {
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
list_t *destroy_list(list_t *l) {
  node_l_t *ini = l->head;
  while (ini != NULL) {
    node_l_t *target = ini;
    ini = ini->next;
    free(target->key);
    free(target);
  }
  free(l);
  return NULL;
}

list_t *empty_list(list_t *l) {
  node_l_t *ini = l->head;
  while (ini != NULL) {
    node_l_t *target = ini;
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
int is_list_empty(list_t *l) {
  if (l->size == 0) {
    return 1;
  }
  return 0;
}

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
 */
int list_size(list_t *l) { return l->size; }

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int list_insert_start(list_t *l, void *key) {
  node_l_t *node = NULL;
  node = create_node(key);
  if (node != NULL) {
    if (is_list_empty(l)) {
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
int list_insert_end(list_t *l, void *key) {
  node_l_t *node = NULL;
  node = create_node(key);
  if (node != NULL) {
    if (is_list_empty(l)) {
      l->head = node;
    } else {
      node_l_t *target = l->head;
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
int list_remove_start(list_t *l) {
  if (!is_list_empty(l)) {
    node_l_t *target = l->head;
    l->head = target->next;

    free(target->key);
    free(target);
    l->size--;
    return 1;
  }
  return 0;
}

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int list_remove_end(list_t *l) {
  if (!is_list_empty(l)) {
    node_l_t *target = l->head;
    while (target->next) {
      target = target->next;
    }

    if (target->prev) {
      target->prev->next = NULL;
    }

    free(target->key);
    free(target);
    l->size--;
    return 1;
  }
  return 0;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
 */
int list_remove_key(list_t *l, void *key) {
  if (!is_list_empty(l) && list_contains(l, key)) {
    node_l_t *target = l->head;

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

    free(target->key);
    free(target);
    l->size--;
    return 1;
  }
  return 0;
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
 */
int list_contains(list_t *l, void *key) {
  if (!is_list_empty(l)) {
    node_l_t *target = l->head;
    while (target != NULL) {
      if (target->key == key) {
        return 1;
      }
      target = target->next;
    }
  }
  return 0;
}