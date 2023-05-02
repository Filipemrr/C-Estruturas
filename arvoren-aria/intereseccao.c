#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
int Aux_arr[SIZE];
int i = 0;
int j = 0;
// Definimos a estrutura para cada nó da árvore
typedef struct node
{
    int value;
    struct node *primeiro_filho; // Ponteiro para o primeiro filho do nó
    struct node *proximo_irmao;  // Ponteiro para o próximo irmão do nó
} node;

// Função para criar um novo nó com um valor específico
struct node *criar_no(int valor)
{
    struct node *novo_no = (struct node *)malloc(sizeof(struct node)); // ALOCA MEMORIA

    novo_no->value = valor;
    novo_no->primeiro_filho = NULL;
    novo_no->proximo_irmao = NULL;
    return novo_no;
}

// Função para adicionar um novo filho a um nó existente
void add(node *pai, node *filho)
{
    if (pai->primeiro_filho == NULL)
    {
        pai->primeiro_filho = filho;
    }
    else
    {
        struct node *irmao = pai->primeiro_filho;
        while (irmao->proximo_irmao != NULL)
        {
            irmao = irmao->proximo_irmao;
        }
        irmao->proximo_irmao = filho;
    }
}

int find(node *raiz, int valor)
{
    if (raiz != NULL)
    {
        if (valor == raiz->value)
            return 1;
        if (find(raiz->primeiro_filho, valor))
            return 1;
        if (find(raiz->proximo_irmao, valor))
            return 1;
    }
    return 0;
}

void percorrer(node *raiz, node *raiz1)
{
    if (raiz == NULL)
    {
        return;
    }
    if (find(raiz1, raiz->value))
        printf("%d ", raiz->value);

    percorrer(raiz->primeiro_filho, raiz1);
    percorrer(raiz->proximo_irmao, raiz1);
}
// Exemplo de uso da árvore
int main()
{
    // primeira arvore declaracao.
    node *raiz = criar_no(5);
    node *filho1 = criar_no(5);
    node *filho2 = criar_no(3);
    node *filho3 = criar_no(90);
    add(raiz, filho1);
    add(raiz, filho2);
    add(raiz, filho3);

    // segunda arvore declaracao.
    node *raiz1 = criar_no(5);
    node *filhoum = criar_no(5);
    node *filhodois = criar_no(3);
    node *filhotres = criar_no(90);

    add(raiz1, filhoum);
    add(raiz1, filhodois);
    add(raiz1, filhotres);

    // percorre a arvore e coloca todos seus elementos em um array.
    percorrer(raiz, raiz1);
    return 0;
}
