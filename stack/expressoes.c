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


//este codigo verfica se a expressao matematica
//esta formada corretamente
//((2 + 3) * 4)
//((3 + 4) * {5 - (2 + 1)})


/*((2+3)*4
(
*/
int main() {
    Stack *pilha; 
    pilha = (Stack*)malloc(sizeof(Stack)); 
    pilha->top = NULL;


    char string[100];
    scanf(" %99[^\n]", string);
    int size = strlen(string);

    int i;
    for(i = 0; i < size; i++){
        if(string[i] == '(' || string[i] == '{' || string[i] == '[')
            push(pilha,string[i]);

        if (string[i] == ')' || string[i] == '}' || string[i] == ']'){
            char sinal = string[i];
//---------
            if(sinal == ')'){

                if(pop(pilha) != '(')
                    break;   
            }

            if(sinal == '}'){
                if(pop(pilha) != '{')
                    break;
            }

            if(sinal == ']'){
                if(pop(pilha) != '[')
                     break;     
            } 
        }
    }
   if(is_empty(pilha))
        printf("Operacao Bem Sucedida\n");
    else
        printf("Operacao Mal Sucedida\n");
}