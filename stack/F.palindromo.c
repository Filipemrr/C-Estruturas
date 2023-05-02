#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} Stack;

void push(Stack* stack, int data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->next = stack->top;
    stack->top = node;
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("A pilha está vazia.\n");
        return -1; // ou outro valor para indicar erro
    }
    Node* node = stack->top;
    int data = node->data;
    stack->top = node->next;
    free(node);
    return data;
}

int is_empty(Stack* stack) {
    return (stack->top == NULL);
}

int main() {
    //declarei a string
    char string[100]; 

    //aloquei memoria 
    Stack *pilha; 
    Stack *auxiliar;
    pilha = (Stack*)malloc(sizeof(Stack)); 
    auxiliar = (Stack*)malloc(sizeof(Stack)); 

    //igualei o topo de cada pilha criada a NULL
    pilha->top = NULL; 
    auxiliar->top = NULL;
  
    //li o palindromo 
    scanf(" %99[^\n]", string);
    
    
     // vi a quantidade de caracteres da string e atribui a "size"
    int size = strlen(string);


    //algoritmo em si : 


    //empilho todos os elementos na pilha principal
    for(int i = 0; i < size; i++){
        if (string[i]!= ' '){
            push(pilha,string[i]); 
        }
    }

    //empilho todos os elementos de forma invertida na pilha auxiliar 
    int j;
    for(j = size - 1; j >= 0; j--){
        if (string[j]!= ' '){
            push(auxiliar,string[j]);
        }
    }
    
    //desempilho as duas pilhas e vou comparando 
    //caso o desempilhar da pilha nao for EXATAMENTE igual, eh um palindromo
    while (1)
    {
        if(is_empty(pilha) && is_empty(auxiliar)){
            printf("Eh um palindronmo\n");
            break;
        }

        if(pop(pilha) != pop(auxiliar)){
            printf("Nao eh um palindromo\n");
            break;
        }
        if(pop(pilha) == 1)
            break;
    }    
    return 0;
}
