#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define LINE printf("linha %d\n", __LINE__);

typedef struct no
{
    int elemento;
   struct no  *proximo;

}No;

typedef struct pilha
{
    struct no *topo;
}pilha;


// função que adiciona um principal à pilha
void push(int dado, pilha *principal)
{
    No *novo = (No*)malloc(sizeof(No)); //cria um ponteiro chamado novo, do tipo "no", e aloca
    if (novo != NULL)
    {
        LINE
        novo -> elemento = dado; // atribui o item novo do elemento no,
        // ao dado passado por parametro.
        novo->proximo = principal->topo;//atribui ao ponteiro "proximo" do novo
        // no = ao topo da pilha principal. que por sua vez eh o ultimo elemento
        //empilhado.
        principal-> topo = novo; //atribui o topo ao no atual. 
    }
}

int pop(pilha *principal)
{
    No *novo = principal -> topo; // cria variavel novo
    // do tipo no e iguala ao topo da pilha principal
    int elemento; 
    if(novo != NULL){ // verifica a alocacao de memoria.
        principal -> topo = novo -> proximo; 
        novo->proximo = NULL;
        elemento = novo ->elemento;
        free(novo);
        return elemento;
    }
    return 0;
}

void imprimir(pilha *principal){
    No* novo = principal -> topo;//criei um variavel chamada novo
    // do tipo no, e igualei ao topo da pilha principal

    if(novo != NULL){
        
        while(novo != NULL){
            printf("%d\n", novo->elemento);
            novo = novo->proximo; // iguala o no "novo" ao ele
            //mento de baixo da pilha.
        }
    }
}

int main()
{
    pilha *stack;//pilha principal
    stack = (pilha*)malloc(sizeof(pilha));
    stack->topo = NULL;
    printf("\n1. PUSH\n2. POP\n3.PRINT THE TOP ELEMENT\n4.PRINT ALL ELEMENTS OF THE STACK\n5. QUIT\n");
    LINE

    while(1){
    LINE
    int opcao; 
    printf("Escolha uma funcao: ");
    scanf("%d", &opcao);
    if (opcao == 1){ // push 
        int element;
        printf("\nWich one element you want push in the stack?: ");
        scanf("%d", &element);
        push(element, stack);//empilha o elemento dado pelo teclado
    }
    if (opcao == 2){
        if(stack->topo != NULL)
            pop(stack);//desempilha um elemento dado pelo teclado 
        else
            printf("Stack Underflow");
    }
    if (opcao == 3){
        if(stack->topo != NULL){
            printf("%d\n", stack->topo->elemento);
            LINE
        }
        else    
            printf("Stack Underflow");
    }
    if (opcao == 4){
        if(stack->topo != NULL){
            imprimir(stack);
            LINE
        }
        else
            printf("Stack Underflow");
    }
    if (opcao == 5)
        break;
}
    return 0;
}

/*
    A funcao Push: 

    push basicamente faz 4 operacoes: 

    - cria e aloca memoria para um novo no. 
    
    - dentro do novo no tem uma variavel chamada elemento, a funcao 
    push guarda um dado como parametro, entao atribui a variavel elemnto
    do novo no ao dado passado como parametro da funcao. 
                    (novo -> elemento = dado)
    
    -Para fazermos uma pilha precisamos ligar os elementos entre si
    por isso nessa linha o ponteiro "proximo" do no, aponta para o topo
    da pilha principal
                (novo -> proximo = principal -> topo)

    -Para finalizar, ja que a estrutura eh do tipo pilha, seu topo 
    eh sempre o ultimo elemento a ser empilhado, entao, atribuimos o 
    no "novo" ao topo da pilha principal.
                    (principal -> topo = novo)


    a funcao pop: 
        
    - Cria um novo no e a aloca memoria para ele 
    - Cria um If que verifica se a alocacao foi bem sucedida pela memoria 
    
        - o topo da pilha principal eh atualizado para o proximo elemento da pilha
                        (principal -> topo = novo -> proximo)

        -o proximo elemento do no novo, eh atualizado para NULL
                        (novo -> proximo = NULL) 

        -iguala a variavel "elemento" a variavel elemento, do novo no. 
                        (elemento = nov -> elemento)

        - a funcao pronta "free (novo)" libera o ponteiro novo. 
                                (free(novo);)

            return elemento. (vai retornar o elemento que estava dentro do no)
            que foi liberado. 
        



*/