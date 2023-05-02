#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct no
{
    int elemento;
   struct no  *proximo;

}No;

typedef struct pilha
{
    struct no *topo;
}pilha;


void push(int dado, pilha *principal)
{
    No *novo = (No*)malloc(sizeof(No));
    if (novo != NULL)
    {
        novo -> elemento = dado;
        novo->proximo = principal->topo;
        principal-> topo = novo;
    }
}

int pop(pilha *principal)
{
    No *novo = principal -> topo;
    int elemento; 
    if(novo != NULL){
        principal -> topo = novo -> proximo; 
        novo->proximo = NULL;
        elemento = novo ->elemento;
        free(novo);
        return elemento;
    }
    return 0;
}

void imprimir(pilha *principal){
    No* novo = principal -> topo;
    if(novo != NULL){
        while(novo != NULL){
            printf("%d\n", novo->elemento);
            novo = novo->proximo;
        }
    }
}

int main()
{
    pilha *stack;
    stack = (pilha*)malloc(sizeof(pilha));
    stack->topo = NULL;
    printf("\n1. PUSH\n2. POP\n3.PRINT THE TOP ELEMENT\n4.PRINT ALL ELEMENTS OF THE STACK\n5. QUIT\n");
    
    while(1){
    int opcao; 
    printf("Escolha uma funcao: ");
    scanf("%d", &opcao);
    if (opcao == 1){
        int element;
        printf("\nWich one element you want push in the stack?: ");
        scanf("%d", &element);
        push(element, stack);
    }
    if (opcao == 2){
        if(stack->topo != NULL)
            pop(stack);
        else
            printf("Stack Underflow");
    }
    if (opcao == 3){
        if(stack->topo != NULL){
            printf("%d\n", stack->topo->elemento);
        }
        else    
            printf("Stack Underflow");
    }
    if (opcao == 4){
        if(stack->topo != NULL){
            imprimir(stack);
        }
        else
            printf("Stack Underflow");
    }
    if (opcao == 5)
        break;
}
   