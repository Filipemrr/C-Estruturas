#include <stdio.h>
#include <stdlib.h>
#define STACK_SIZE 10

typedef struct Pilha {
    int topo;
    int items[STACK_SIZE];
} Pilha;

int isEmpty(Pilha* stack) {
    if(stack->topo == 0)
        return 1;
    else
        return 0;
}
int isFull(Pilha* stack) {
   if(stack->topo == STACK_SIZE-1)
    return 1;
   else 
    return 0;
}

void push(Pilha* stack, int item) {
    if (isFull(stack)) {
        printf("Error: Stack is full!\n");
        return;
    }
    stack->topo++;
    stack->items[stack->topo] = item;
}

int pop(Pilha* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty!\n");
        return -1;
    }
    int item = stack->items[stack->topo];
    stack->topo--;
    return item;
}
void imprimir(Pilha* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack: \n");
    for (int i = stack->topo; i > 0; i--) {
        printf("%d\n", stack->items[i]);
    }
    printf("\n");
}



int main() {
    Pilha *stack;
    stack = (Pilha*)malloc(sizeof(Pilha));
    stack->topo = 0;

    


    return 0;
}

/*
    infixo (a+b)*c 
    posfixo ab+c*
    prefixo *c+ab


    4 pilhas 
    1- para os operandos (a b c)
    2- para os operadores ( + - * /)
    3- auxiliar operando.
    4-auxiliar operador.

    entrada exemplo: 8 + 2 / 3 (infixo-normal)
    posfixa: 8 2 + 3 /



    logica: 
    1.ler a string que seria a expressao matematica infixa

    2.percorre a string verificando se a posicao eh numero operador ou espaco, caso seja numero, 
    imprilhar um numero na pilha numero, caso seja um operador empilhar na de operador, caso seja
    espaco empilhar na puilha de espaco.
    
    3. empilhados todos os elementos em suas respectivas pilha e inverto a pilha dos numeros.

    4. Crio uma funcao chamada "ordem de prioridade" em que em um array, eu aloco do menor para o maior
    os operandos que tem prioridade.
    
    arr[0] = +;
    arr[1] = -;
    arr[2] = *; 
    arr[3] = *;
    arr[4] = *;

    5.0 Eu desempilho um elemento e um espaco 2x , e printo, apos isso printo o elemento com maior
    prioridade. (posfixa)

    5.1 desempilho operador com maior prioridade um espaco e em seguida dois elementos e 
    dois espacos (prefixa).

    5.2 desempilho intercalado numero -  um espaco - um operador ate o fim das pilhas.  



    6. apos isso vou desempilhando o resto da pilha de numero 2 em 2 e printando o array com a prioridade
    subsequente.  

   

    

*/
