#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
int Aux_arr[SIZE];

int i = 0;
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
void add(struct node *pai, struct node *filho)
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
// Função para imprimir a árvore em pré-ordem
void imprimir_arvore(node *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    printf("%d ", raiz->value);
    imprimir_arvore(raiz->primeiro_filho);
    imprimir_arvore(raiz->proximo_irmao);
}

void percorrer(node *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    Aux_arr[i] = raiz->value;
    i++;
    percorrer(raiz->primeiro_filho);
    percorrer(raiz->proximo_irmao);
}

// Exemplo de uso da árvore
int main()
{
    // primeira arvore declaracao.
    node *raiz = criar_no(1);
    node *filho1 = criar_no(2);
    node *filho2 = criar_no(3);
    node *filho3 = criar_no(4);
    node *filho4 = criar_no(90);
    add(raiz, filho1);
    add(raiz, filho2);
    add(raiz, filho3);
    add(filho3, filho4);

    // segunda arvore declaracao.
    node *raiz1 = criar_no(5);
    node *filhoum = criar_no(10);
    node *filhodois = criar_no(12);
    node *filhotres = criar_no(15);

    add(raiz1, filhoum);
    add(raiz1, filhodois);
    add(raiz1, filhotres);

    // declara ambas as arvores, vamos fazer a uniao:

    // crio a funcao void percorrer que tem uma estrutura muito
    // similar a funcao de imprimir, mas ao inves de printar ela
    // somente coleta as informacoes de uma arvore e aloca em um array.
    percorrer(raiz1);
    // eu passo de parametro a raiz da arvore que vou percorrer
    // e o array para ir coletando os valores dessa arvore.
    int tamanho_arvore1 = i - 1;
    // 5 10 12 15
    node *aux;
    for(int i = 0; i < tamanho_arvore1; i++)
    {
        aux = criar_no(Aux_arr[i]);
        add(raiz, aux);
    }
    imprimir_arvore(raiz);

    return 0;
}
//5 10 12 15 
