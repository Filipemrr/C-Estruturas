#include <stdio.h>
#include <stdlib.h>
#define SIZE 50

// Definimos a estrutura para cada nó da árvore
typedef struct node{
    int value;
    struct node *primeiro_filho; // Ponteiro para o primeiro filho do nó
    struct node *proximo_irmao; // Ponteiro para o próximo irmão do nó
}node;

// Função para criar um novo nó com um valor específico
struct node *criar_no(int valor) {
    struct node *novo_no = (struct node*) malloc(sizeof(struct node));//ALOCA MEMORIA
    
    novo_no->value = valor;
    novo_no->primeiro_filho = NULL;
    novo_no->proximo_irmao = NULL;
    return novo_no;
}

// Função para adicionar um novo filho a um nó existente
void add(struct node *pai, struct node *filho) {
    if (pai->primeiro_filho == NULL) {
        pai->primeiro_filho = filho;
    } else {
        struct node *irmao = pai->primeiro_filho;
        while (irmao->proximo_irmao != NULL) {
            irmao = irmao->proximo_irmao;
        }
        irmao->proximo_irmao = filho;
    }
}

// Função para imprimir a árvore em pré-ordem
void imprimir_arvore(struct node *raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("%d ", raiz->value);
    imprimir_arvore(raiz->primeiro_filho);
    imprimir_arvore(raiz->proximo_irmao);
}

void percorrer(struct node *raiz) {
    if (raiz == NULL) {
        return;
    }
    printf("%d ", raiz->value);
    imprimir_arvore(raiz->primeiro_filho);
    imprimir_arvore(raiz->proximo_irmao);
}

// Exemplo de uso da árvore
int main() {
    int array_percorrer[SIZE]; // array

    //essas funcoes criar um NO sem pad
    struct node *raiz = criar_no(1);
    struct node *filho1 = criar_no(2);
    struct node *filho2 = criar_no(3);
    struct node *filho3 = criar_no(4);
    struct node *neto1 = criar_no(5);
    struct node *neto2 = criar_no(6);
    struct node *neto3 = criar_no(7);

    add(raiz, filho1);
    add(raiz, filho2);
    add(raiz, filho3);
    add(filho1, neto1);
    add(filho1, neto2);
    add(filho2, neto3);
    /* a estrutura da funcao add eh
    add(no pai, no que vai ser seu filho)
    pode ser simplesmente um numero, ou um outro no.

    essa funcao serve para fazer os parentescos. 
*/


    imprimir_arvore(raiz); // Saída esperada: 1 2 5 6 3 7 4
    return 0;
}
