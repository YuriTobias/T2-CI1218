#ifndef _LIBstack_t_H
#define _LIBstack_t_H

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

#define STACK_LEN 100

typedef struct Stack {
    void** elems;
    int size;
    int head;
} Stack;

/*
 * Cria e retorna uma nova pilha com capacidade de size elementos.
 * Retorna NULL em caso de erro de alocação
 */
Stack* StackCreate(int size);

/*
 * Insere elem na pilha (politica LIFO). Caso a pilha esteja cheia, tenta realocá-la.
 * Retorna o número de elementos na pilha em caso de sucesso e -1 para falha de realocação;
 */
int StackPush(Stack* stack, void* elem);

/*
 * Remove (politica LIFO) e retorna um elemento da pilha.
 * Em caso de pilha vazia retorna 0
 */
void* StackPop(Stack* stack);

/* Similar ao Pop, mas retorna sem remover */
void* StackHead(Stack* stack);

/* Retorna o numero de elementos da pilha, que pode ser 0 */
int StackSize(Stack* stack);

/* Retorna 1 se pilha vazia, 0 em caso contrario */
int StackIsEmpty(Stack* stack);

/* Desaloca memoria de Stack e retorna NULL */
Stack* StackDestroy(Stack* stack);

#endif