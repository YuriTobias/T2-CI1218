#ifndef _LIBstack_t_H
#define _LIBstack_t_H

#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

#define STACK_LEN 100

typedef struct {
    void** elems;
    int size;
    int head;
} stack_t;

/*
 * Cria e retorna uma nova pilha com capacidade de size elementos.
 * Retorna NULL em caso de erro de alocação
 */
stack_t* create_stack(int size);

/*
 * Insere elem na pilha (politica LIFO). Caso a pilha esteja cheia, tenta realocá-la.
 * Retorna o número de elementos na pilha em caso de sucesso e -1 para falha de realocação;
 */
int push(stack_t* stack, void* elem);

/*
 * Remove (politica LIFO) e retorna um elemento da pilha.
 * Em caso de pilha vazia retorna 0
 */
void* pop(stack_t* stack);

/* Similar ao Pop, mas retorna sem remover */
void* stack_head(stack_t* stack);

/* Retorna o numero de elementos da pilha, que pode ser 0 */
int stack_size(stack_t* stack);

/* Retorna 1 se pilha vazia, 0 em caso contrario */
int empty_stack(stack_t* stack);

/* Desaloca memoria de stack_t e retorna NULL */
stack_t* destroy_stack(stack_t* stack);

#endif