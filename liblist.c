#include "liblist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void ListHardDestroy(List *l) {
    Node *ini = l->head;
    while (ini != NULL) {
        Node *target = ini;
        ini = ini->next;
        free(target->key);
        free(target);
    }
    free(l);
}

void ListHardRemoveAll(List *l) {
    Node *ini = l->head;
    while (ini != NULL) {
        Node *target = ini;
        ini = ini->next;
        free(target->key);
        free(target);
    }
    l->head = NULL;
    l->size = 0;
}

void ListSoftRemoveAll(List *l) {
    Node *ini = l->head;
    while (ini != NULL) {
        Node *target = ini;
        ini = ini->next;
        free(target);
    }
    l->head = NULL;
    l->size = 0;
}

int ListIsEmpty(List *l) {
    if (l->size == 0) {
        return 1;
    }
    return 0;
}

int ListSize(List *l) { return l->size; }

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

void *ListSoftRemoveStart(List *l) {
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

void *ListSoftRemoveEnd(List *l) {
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

void *ListSoftRemoveKey(List *l, void *key, int (*comparator)(void *, void *)) {
    if (!ListIsEmpty(l) && ListFindKey(l, key, comparator)) {
        Node *target = l->head;

        while (!(comparator(target->key, key))) {
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

void *ListFindKey(List *l, void *key, int (*comparator)(void *, void *)) {
    if (!ListIsEmpty(l)) {
        Node *target = l->head;
        while (target != NULL) {
            if (comparator(target->key, key)) {
                return target->key;
            }
            target = target->next;
        }
    }
    return NULL;
}

List *ListCopy(List *source) {
    List *copy = ListCreate();
    Node *target = ListIsEmpty(source) ? NULL : source->head;
    while (target != NULL) {
        ListInsertEnd(copy, target->key);
        target = target->next;
    }
    return copy;
}