#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *next;
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
    printf("Carta A %d X Carta B %d\n", carta_A,Carta_B);
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

void embaralhar_pilha(Stack* stack) {
    // Caso a pilha tenha menos de dois elementos, não há o que embaralhar
    if (stack->top == NULL || stack->top->next == NULL) {
        return;
    }
    
    // Conta o número de elementos na pilha
    int count = 0;
    Node* node = stack->top;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    
    // Percorre a pilha e troca cada nó com outro nó aleatório
    node = stack->top;
    for (int i = 0; i < count; i++) {
        // Encontra um nó aleatório
        int random_index = rand() % count;
        Node* random_node = stack->top;
        for (int j = 0; j < random_index; j++) {
            random_node = random_node->next;
        }
        
        // Troca os dados dos nós
        int temp = node->data;
        node->data = random_node->data;
        random_node->data = temp;
        
        // Avança para o próximo nó
        node = node->next;
    }
}

void imprimir(Stack *principal){
    Node *novo = principal -> top;
    if(novo != NULL){
        while(novo != NULL){
            novo->data +=2;
            printf("%d\n", novo->data);
            novo = novo->next;
        }
    }
}


int main(){
    printf("\n");
    printf("Digite 1 para o baralho ter tamanho gerado aleatoriamente\n");
    printf("Digite 2 para escolher o tamanho do baralho\n");
    printf("Escolha um numero: ");
    int numero_de_Cartas;
    scanf("%d", &numero_de_Cartas);

    if(numero_de_Cartas == 1){
        srand(time(NULL));
        numero_de_Cartas = rand() % 21;
//leio o numero total de cartas
    }
    else{
        printf("Escolha o tamanho do baralho: ");
        scanf("%d", &numero_de_Cartas);
    }

    printf("o tamanho do baralho na partida foi: %d\n", numero_de_Cartas);


    Stack *baralho;
    baralho = (Stack*)malloc(sizeof(Stack));
    baralho->top = NULL;

    //criando o baralho
    for (int i = 0; i < numero_de_Cartas; i++) {
        int carta = (rand() % 51) + 1;
        if(carta == -1)
            carta+=2;
        push(baralho,carta);
    }

    //CRIANDO as duas pilhas de jogadores no qual vao estar seus baralhos.
    Stack *jogador_A; 
    Stack *jogador_B;
    jogador_A = (Stack*)malloc(sizeof(Stack)); 
    jogador_B = (Stack*)malloc(sizeof(Stack));
    jogador_A->top = NULL; 
    jogador_B->top = NULL;
    //destribui as cartas
    printf("\n");
    while(1){
        if(is_empty(baralho))
            break;

        push(jogador_A,pop(baralho));
        push(jogador_B,pop(baralho));
    }
    
    //embaralhar_pilha(jogador_A);
    printf("cartas do jogador A:\n");
    imprimir(jogador_A);

    //embaralhar_pilha(jogador_B);
    printf("cartas do jogador B:\n");
    imprimir(jogador_B);
    
    printf("\n :---- As Rodadas foram ----:\n");

    while(1)
    {
        if(is_empty(jogador_A) || is_empty(jogador_B)){
            if(is_empty(jogador_A) && is_empty(jogador_B) == 0){
                printf("\n\n:------O jogador B ganhou-------:\n");
                printf("E Seu baralho final foi:\n");
                imprimir(jogador_B);
                break;
            }
            else if(is_empty(jogador_B) && is_empty(jogador_A) == 0){
                printf("\n\n:------O jogador A ganhou--------:\n");
                printf("E Seu baralho final foi:\n");
                imprimir(jogador_A);
                break;
            }
            else{
                printf("Empate");
                break;
            }
        }

        batalha(jogador_A,jogador_B);
        embaralhar_pilha(jogador_A);
        embaralhar_pilha(jogador_B);
    }
    printf("\n");
    return 0;
}