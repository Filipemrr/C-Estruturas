/*Reorganizar as ESTANTES pegando os livros das PRATILEIRAS DE CIMA P BAIXO, ESQUERDA P DIREITA.
ENTRADA: / \ = começo e fim da pratileira
ESTANTE = MAX 6 PRATILEIRAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct no {
    int elemento;
    struct no *proximo;
} No;

typedef struct pilha {
    struct no *topo;
} Pilha;

void empilhar(int dado, Pilha *valor) {
    No *novo = (No*)malloc(sizeof(No));
    if (novo != NULL) {
        novo->elemento = dado;
        if (valor->topo == NULL || dado > valor->topo->elemento) {
            novo->proximo = valor->topo;
            valor->topo = novo;
        } else {
            No *atual = valor->topo;
            while (atual->proximo != NULL && dado <= atual->proximo->elemento) {
                atual = atual->proximo;
            }
            novo->proximo = atual->proximo;
            atual->proximo = novo;
        }
    }
    //printf("empilhei esse num %d\n", dado);
}

int desempilhar(Pilha *valor) {
    No *novo = valor->topo;
    int elemento;
    if (novo != NULL) {
        valor->topo = novo->proximo;
        novo->proximo = NULL;
        elemento = novo->elemento;
        free(novo);
    }
    return elemento;
}

int main()
{
    printf("Quantas estantes você quer organizar?\n");
    int num_est;
    scanf("%d", &num_est);
    printf("Qual seu limite de livros por pratieira? De 1 a 10\nobs:esse limite definirá a organização das pratileiras\n");
    int limite;
    scanf("%d", &limite);
    if(limite < 1 || limite > 10){printf("ERRO:limite inválido"); return 1;}
    printf("Quantas prateleiras há em CADA estante, digite uma por uma\n");
    int num_prat[num_est];
    for(int i =0; i < num_est;i++)
    {
        scanf("%d", &num_prat[i]);
       
        if(num_prat[i] > 6)
        {
            printf("ERRO: mais prateleiras que o devido\n");
            return 1;
        }
    }
    for(int i =1; i <=num_est; i++)
    { 
        Pilha *estante;
        estante = (Pilha*)malloc(sizeof(Pilha));
        if (estante == NULL) {
            printf("ERRO: falha ao alocar memória\n");
            return 1;
        }
        estante->topo = NULL;

        printf("Escreva o conteúdo (altura de cada livro de 0 a 99 cm) da estante %d, cada prateleira em uma linha delimitada por /\\ \n", i);
        char prateleira[35]; 

        for(int l=1; l<=num_prat[i - 1];l++) //empilhar tds as prateleiras da estante i
        {
            srand(time(NULL));
            limite = rand() % limite;

            for(int i =0; i < limite; i++)
            {
                int valores;
                srand(time(NULL));
                valores= rand() % 99;
                prateleira[i] = valores;
            }
            
            getchar(); // limpa o buffer do teclado
            int tam = strlen(prateleira);
        
                for(int j =0; j <tam; j++)
                {
                    if (prateleira[j] != '/' && prateleira[j] != '\\' && prateleira[j] != ' ') {
                        char p[3] = "";
                        int k = 0;
                        while (prateleira[j] != ' ' ) {
                            p[k] = prateleira[j];
                            j++;  
                            k++;
                        }
                        int tam2 = strlen(p);
                        
                        if(tam2>3){printf("ERRO:livro maior que o tamanho permitido\n"); return 1;}
                        int prat = atoi(p);
                        empilhar(prat, estante);
                    }

                }
            
        }
        int limite_total = limite * num_prat[i-1];
        printf("\n");
        printf("ESTANTE %d : ", i);
        printf("\n");
        
        int lim= 0;
        int y = 0;
        while(estante->topo != NULL)
        {
            if(lim == 0){printf("/");}
            int x =desempilhar(estante);
            y++;
            if(y > limite_total)
            {
                printf("ERRO: colocou mais livros na estante do que o permitido, o máximo que a estante permite está acima\n");
                return 1;
            }
            printf(" %d ", x);
            lim++;
            if(lim == limite || estante->topo == NULL)
            {
                printf("\\");
                printf("\n");
                lim = 0;
            }
       
    }
        printf("\n");
    
    // falta ver como imprimir todas as estantes de uma vez e tb quebra de linha e /\ qnd passar de 10 por pratileira
    
}
}
