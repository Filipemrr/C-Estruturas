#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no{
    int dado;
    struct no *proximo;
}No;

typedef struct{
    No *primeiro; 
    No *ultimo;
    int tamanho;
}Fila;

void criar_fila(Fila *nova_fila){
    nova_fila -> primeiro = NULL;
    nova_fila -> ultimo = NULL;
    nova_fila -> tamanho = 0;
}


void inserir(Fila *fila, int valor){
    No* novo = (No*) malloc(sizeof(No)); // aloquei
    novo -> dado = valor; //inseri o valor pedido
    novo -> proximo = NULL; // setei o proximo como NULL

    if(fila->tamanho == 0){//a fila esta vazia
        fila->primeiro = novo;
        fila->ultimo = novo;
        fila->tamanho = 1;
    }

    else{
        fila->ultimo->proximo = novo; // novo = proximo no do ultimo
        fila->ultimo = novo;
        fila->tamanho++;
    }
}

int remover(Fila *fila){
    if(fila->tamanho == 0){
        printf("Fila vazia");
        return 0;
    }
    int valor_removido = fila->primeiro->dado;
    No* no_removido = fila->primeiro;
    fila ->primeiro = fila->primeiro->proximo;
    free(no_removido);
    fila->tamanho--;
    return valor_removido;
}

void imprimir(Fila *fila) {
    No* auxiliar = fila->primeiro; // Cria um ponteiro auxiliar para percorrer a fila

    while (auxiliar != NULL) { // Percorre a fila enquanto o ponteiro auxiliar não for NULL
        printf("%d ", auxiliar->dado); // Imprime o valor do elemento apontado pelo ponteiro auxiliar
        auxiliar = auxiliar->proximo; // Atualiza o ponteiro auxiliar para apontar para o próximo elemento
    }

    printf("\n");
}


int main(){
        Fila *pessoas; 
        pessoas = (Fila*)malloc(sizeof(Fila)); 
        criar_fila(pessoas); // Inicializa a fila

        while (1){
            int valor;
            printf("Digite um comando: ");
            scanf("%d", &valor);

            if(valor == 1){
                printf("\nDigite um numero para adicionar a fila: ");
                scanf("%d", &valor);
                inserir(pessoas,valor);
            }
            if(valor ==2){
                remover(pessoas);
            }
            if(valor == 3){
                imprimir(pessoas);
            }
            if(valor == 4){
                exit(1);
            }
        }
        

    return 0;
}