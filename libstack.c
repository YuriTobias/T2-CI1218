#include "libstack.h"

#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

Stack *StackCreate(int size) {
    Stack *stack;
    if (!(stack = malloc(sizeof(Stack)))) {
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

int StackPush(Stack *stack, void *elem) {
    if (StackSize(stack) < stack->size) {
        stack->head++;
        stack->elems[stack->head] = elem;
        return stack->head + 1;
    } else {
        if (!(stack->elems = realloc(stack->elems, sizeof(void *) * (stack->size + STACK_LEN)))) {
            return -1;
        }
        stack->size += STACK_LEN;
        StackPush(stack, elem);
    }
    return -1;
}

void *StackPop(Stack *stack) {
    void *popped;
    if (!StackIsEmpty(stack)) {
        popped = StackHead(stack);
        stack->head--;
        return popped;
    }
    return 0;
}

void *StackHead(Stack *stack) {
    if (!StackIsEmpty(stack)) {
        return stack->elems[stack->head];
    }
    return 0;
}

int StackSize(Stack *stack) { return stack->head + 1; }

int StackIsEmpty(Stack *stack) {
    if (StackSize(stack) == 0) {
        return 1;
    }
    return 0;
}

Stack *StackDestroy(Stack *stack) {
    int cont;
    for (cont = 0; cont < StackSize(stack); cont++) {
        free(stack->elems[cont]);
    }
    free(stack->elems);
    free(stack);
    return NULL;
}