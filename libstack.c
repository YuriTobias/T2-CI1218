#include "libstack.h"

#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

stack_t *create_stack(int size) {
    stack_t *stack;
    if (!(stack = malloc(sizeof(stack_t)))) {
        return NULL;
    }
    stack->head = -1;
    stack->size = size;
    if (!(stack->elems = malloc(sizeof(void *) * size))) {
        free(stack);
        return NULL;
    }
    return stack;
}

int push(stack_t *stack, void *elem) {
    if (stack_size(stack) < stack->size) {
        stack->head++;
        stack->elems[stack->head] = elem;
        return stack->head + 1;
    } else {
        if (!(stack->elems = realloc(stack->elems, sizeof(void *) * (stack->size + STACK_LEN)))) {
            return -1;
        }
        stack->size += STACK_LEN;
        push(stack, elem);
    }
    return -1;
}

void *pop(stack_t *stack) {
    void *popped;
    if (!empty_stack(stack)) {
        popped = stack_head(stack);
        stack->head--;
        return popped;
    }
    return 0;
}

void *stack_head(stack_t *stack) {
    if (!empty_stack(stack)) {
        return stack->elems[stack->head];
    }
    return 0;
}

int stack_size(stack_t *stack) { return stack->head + 1; }

int empty_stack(stack_t *stack) {
    if (stack_size(stack) == 0) {
        return 1;
    }
    return 0;
}

stack_t *destroy_stack(stack_t *stack) {
    int cont;
    for (cont = 0; cont < stack_size(stack); cont++) {
        free(stack->elems[cont]);
    }
    free(stack->elems);
    free(stack);
    return NULL;
}