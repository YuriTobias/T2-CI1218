#ifndef _LIBpilha_t_H
#define _LIBpilha_t_H

typedef struct {
    int* elems;   /* espaco armazenamento dos elementos tipo int */
    int nelem;    /* qtde maxima de elementos                    */
    int topo;     /* indice para elemento do topo da pilha       */
} pilha_t;

/* 
 * Cria e retorna uma nova pilha com capacidade de nelem elementos. 
 * Retorna NULL em caso de erro de alocação 
*/
pilha_t* pilha_cria (int nelem);

/* 
 * Insere elem na pilha (politica LIFO). Retorna o número de elementos na pilha 
 * em caso de sucesso e -1 em caso de pilha cheia 
*/
int push (pilha_t* pilha, int elem);

/* 
 * Remove (politica LIFO) e retorna um elemento da pilha. 
 * Em caso de pilha vazia retorna 0 
*/
int pop (pilha_t* pilha);
 
/* Similar ao Pop, mas retorna sem remover */
int pilha_topo (pilha_t* pilha);  

/* Retorna o numero de elementos da pilha, que pode ser 0 */
int pilha_tamanho (pilha_t* pilha);

/* Retorna 1 se pilha vazia, 0 em caso contrario */ 
int pilha_vazia (pilha_t* pilha);

/* Desaloca memoria de pilha_t e retorna NULL */
pilha_t* pilha_destroi (pilha_t* pilha);

/* 
 * Imprime a pilha, da base ate o topo, este por ultimo, sem espaco no final.
 * Quando a pilha estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD pilha.
*/
void pilha_imprime (pilha_t* pilha);

#endif