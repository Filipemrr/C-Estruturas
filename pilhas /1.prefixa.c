#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 150
 
 
typedef struct Pilha
{
    int topo;
    int items[STACK_SIZE];
} Pilha;
 
int isEmpty(Pilha *stack)
{
    if (stack->topo == 0)
        return 1;
    else
        return 0;
}
 
void push_int(Pilha *stack, int item){
    stack->topo++;
    stack->items[stack->topo] = item;
}
 
void push_char(Pilha *stack, char item){
    stack->topo++;
    stack->items[stack->topo] = item;
}
 
int pop_int(Pilha *stack)
{
    if (isEmpty(stack))
    {
        printf("Error: Stack is empty!\n");
        return -1;
    }
    int item = stack->items[stack->topo];
    stack->topo--;
    return item;
}
char pop_char(Pilha *stack)
{
    if (isEmpty(stack))
    {
        printf("Error: Stack is empty!\n");
        return -1;
    }
    char item = stack->items[stack->topo];
    stack->topo--;
    return item;
}
void imprimir_int(Pilha* stack) {
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
 
void imprimir_char(Pilha* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack: \n");
    for (int i = stack->topo; i > 0; i--) {
        printf("%c\n", stack->items[i]);
    }
    printf("\n");
}
 
int main()
{
    // declaro as pilhas e aloco memoria para elas.
    Pilha *numeros;
    Pilha *sinais;
    Pilha *aux_num;
    Pilha *aux_sin;
 
    numeros = (Pilha *)malloc(sizeof(Pilha));
    numeros->topo = 0;
 
    sinais = (Pilha *)malloc(sizeof(Pilha));
    sinais->topo = 0;
 
    aux_num = (Pilha *)malloc(sizeof(Pilha));
    aux_num->topo = 0;
 
    aux_sin = (Pilha *)malloc(sizeof(Pilha));
    aux_sin->topo = 0;
 
 
    // menu 8 + 9 * 12
    printf("Escreva uma expressao matematica: \n");
    char expressao[100]; // string 
    scanf(" %99[^\n]", expressao); // leio string
    int n = strlen(expressao); // tamanho da string lida 
 
    //empilhando a pilha de numeros
    for (int i = 0; i < n; i++)
    {
        //caso seja um numero... 
        // 12 + 3 * 5 
        if (expressao[i] >= '0' && expressao[i] <= '9')
        {
            //transforma string em um inteiro. 
            int buffer = expressao[i] - '0';//1
            i++;
            //caso seja um numero com mais de um digito.
            while (expressao[i] >= '0' && expressao[i] <= '9')
            {
                buffer *= 10;
                buffer += expressao[i] - '0';
                i++;
            }
            push_int(numeros,buffer);  
        }
    }
    //empilhando a pilha de operadores (por ordem de prioridade)
    
 
    //inverte ambas as pilhas e aloca as suas inversoes 
    //em suas respectivas auxiliares. 
    while(1){
        if(isEmpty(numeros) != 1)
            push_int(aux_num,pop_int(numeros));
 
        if(isEmpty(sinais) != 1)
            push_char(aux_sin,pop_char(sinais));
 
        if(isEmpty(sinais) && isEmpty(numeros))
            break;
    }
//posfixa Eu desempilho um elemento e um espaco 2x , e printo, apos isso printo o operador com maior
//prioridade e repito o ciclo. (posfixa)

    //5.1 desempilho operador com maior prioridade um espaco e em seguida dois elementos e 
    //dois espacos (prefixa).

    while(1){
        if(isEmpty(aux_sin) != 1){
            printf("%c ",pop_char(aux_sin));
        }
        if(isEmpty(aux_num) != 1){
            printf("%d ",pop_int(aux_num));
        }
 
        if(isEmpty(aux_num) != 1){
            printf("%d ",pop_int(aux_num));
        }
        if(isEmpty(aux_sin) && isEmpty(aux_sin))
            break;
    }
 
 
    return 0;
}