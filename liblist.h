#ifndef _LIBlist_t_H
#define _LIBlist_t_H

typedef struct Node {
    void* key;         /* Uma chave que estará armazenada na lista ligada */
    struct Node* prev; /* Ponteiro para o nó anterior de uma lista ligada */
    struct Node* next; /* Ponteiro para o próximo nó de uma lista ligada */
} Node;

typedef struct List {
    Node* head; /* Ponteiro para o inicio da lista */
    int size;   /* Número de elementos na lista    */
} List;

/*!
 * @name ListCreate
 * @brief Cria uma lista vazia.
 * @result Um ponteiro para a lista criada.
 */
List* ListCreate();

/*!
 * @name ListHardDestroy
 * @brief Desaloca a lista e todas as suas chaves.
 * @param l A lista que será desalocada junto com suas chaves.
 */
void ListHardDestroy(List* l);

/*!
 * @name ListHardRemoveAll
 * @brief Remove todas as chaves da lista e também as desaloca.
 * @param l A lista na qual todas as chaves serão removidas e desalocadas.
 */
void ListHardRemoveAll(List* l);

/*!
 * @name ListSoftRemoveAll
 * @brief Remove todas as chaves da lista.
 * @param l A lista na qual todas as chaves serão removidas.
 */
void ListSoftRemoveAll(List* l);

/*!
 * @name ListIsEmpty
 * @brief Informa se a lista está vazia.
 * @param l A lista que deseja-se saber estar vazia ou não.
 * @result 1 se a lista estiver vazia, 0 caso contrário.
 */
int ListIsEmpty(List* l);

/*!
 * @name ListSize
 * @brief Informa o tamanho da lista.
 * @param l A lista cujo tamanho deseja-se saber.
 * @result O tamanho da lista.
 */
int ListSize(List* l);

/*!
 * @name ListInsertStart
 * @brief Insere uma chave no início da lista.
 * @param l A lista na qual a chave será inserida.
 * @param key A chave que será inserida.
 * @result 1 para operação bem sucedida, 0 caso contrário.
 */
int ListInsertStart(List* l, void* key);

/*!
 * @name ListInsertEnd
 * @brief Insere uma chave no fim da lista.
 * @param l A lista na qual a chave será inserida.
 * @param key A chave que será inserida.
 * @result 1 para operação bem sucedida, 0 caso contrário.
 */
int ListInsertEnd(List* l, void* key);

/*!
 * @name ListSoftRemoveStart
 * @brief Remove a primeira chave da lista.
 * @param l A lista na qual a chave será removida.
 * @result Um ponteiro para a chave removida da lista ou NULL caso não encontre-a.
 */
void* ListSoftRemoveStart(List* l);

/*!
 * @name ListSoftRemoveEnd
 * @brief Remove a última chave da lista.
 * @param l A lista na qual a chave será removida.
 * @result Um ponteiro para a chave removida da lista ou NULL caso não encontre-a.
 */
void* ListSoftRemoveEnd(List* l);

/*!
 * @name ListSoftRemoveKey
 * @brief Busca uma chave específica na lista e a remove.
 * @param l A lista na qual a chave será buscada e removida.
 * @param key A chave que será buscada e removida.
 * @result Um ponteiro para a chave removida da lista ou NULL caso não encontre-a.
 */
void* ListSoftRemoveKey(List* l, void* key);

/*!
 * @name ListContains
 * @brief Informa se uma chave está ou não contida na lista.
 * @param l A lista na qual a chave será buscada.
 * @param key A chave que será buscada.
 * @result 1 se encontrar a chave, 0 caso contrário.
 */
int ListContains(List* l, void* key);

/*!
 * @name ListCopy
 * @brief Realiza a cópia de uma lista fornecida.
 * @param source A lista fonte a ser copiada.
 * @result Um ponteiro para a cópia realizada.
 */
List* ListCopy(List* source);

#endif