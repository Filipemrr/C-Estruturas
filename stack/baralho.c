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

int isEmpty(Stack* stack) {
    if(stack->top == NULL)
        return 1;
    else
        return 0;
}

int batalha(Stack *jogador_A, Stack *jogador_B){
    int carta_A;
    int Carta_B;
    carta_A = pop(jogador_A); 
    Carta_B = pop(jogador_B);

    if(carta_A > Carta_B){
        push(jogador_A,carta_A);
        return 1;
    }
    if(carta_A < Carta_B){
        push(jogador_B,Carta_B);
        return 2;
    }
    if(carta_A == Carta_B)
        return 0;
}


int main(){
    int n; //numero total de cartas  
    scanf("%d",&n);//leio o numero total de cartas 

    Stack *baralho;
    baralho = (Stack*)malloc(sizeof(Stack));
    baralho->top = NULL;

    //criando o baralho
    for(int i = 0; i < n; i++){
        int numero_carta;
        scanf("%d", numero_carta); 
        push(baralho,numero_carta);
    }

    //CRIANDO as duas pilhas de jogadores no qual vao estar seus baralhos.
    Stack *jogador_A; 
    Stack *jogador_B;
    jogador_A = (Stack*)malloc(sizeof(Stack)); 
    jogador_B = (Stack*)malloc(sizeof(Stack));
    jogador_A->top = NULL; 
    jogador_B->top = NULL;

    while(1){
        if(is_empty(baralho))
            break;

        push(jogador_A,pop(baralho));
        push(jogador_B,pop(baralho));
    }

    while(1)
    {
        if(is_empty(jogador_A) || is_empty(jogador_B)){
            if(is_empty(jogador_A) && is_empty(jogador_B) == 0){
                printf("O jogador B ganhou");
                break;
            }
            else if(is_empty(jogador_B) && is_empty(jogador_A) == 0){
                printf("O jogador A ganhou");
                break;
            }
            else{
                printf("Empate");
                break;
            }
        }

        batalha(jogador_A,jogador_B);
        embaralha_pilha(jogador_A);
        embaralha_pilha(jogador_B);

        
    }
    





    return 0;
}