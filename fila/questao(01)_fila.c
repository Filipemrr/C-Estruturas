#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

typedef struct {
    char paciente[MAX_SIZE][MAX_SIZE];
    int length;
} StaticList;

void initializeList(StaticList *list);
void insertElement(StaticList *list, char element[MAX_SIZE]);
void insertSpaces(StaticList *list, char element[MAX_SIZE]);
void removeElement(StaticList *list, int index);
void swapElements(StaticList *list, int index1, int index2);
void printList(StaticList list);
char *generateName();


int main() {

    //criando a fila 
    StaticList pacientes;
    initializeList(&pacientes);

    //adicionando espacos vazios no comeco da fila 
    srand(time(NULL));
    int gaps = (rand() % 10) + 1;
    for (int i = 0; i < gaps; i++)
    {
        char gap[MAX_SIZE] = " ";
        insertSpaces(&pacientes, gap);
    }   

    while (1)
    {
        int valor; 
        printf("\n\n\n1.Digite 1 para adicionar um nome aleatorio\n");
        printf("2.Digite 2 para ver a como esta a fila\n");
        printf("3.Digite 3 para adicionar um nome de sua escolha\n");
        printf("4. Digite 4 para retirar um elemento da lista\n");
        printf("5.Digite 5 para fazer a troca de posicao de elementos\n");
        printf("6.Digite 6 para finalizar operecao\n");
        

        printf("Digite uma opcao: ");
        

        scanf("%d",&valor);

        if(valor == 1){
        srand(time(NULL));
        char *name = generateName();
        insertElement(&pacientes,name);
        free(name);
        }

        if(valor == 2){
            printList(pacientes);
        }
        
        if(valor == 3){
            char nome[MAX_SIZE];
            scanf(" %[^\n]", nome);
            insertElement(&pacientes,nome);
        }
        if(valor == 4){
            printf("digite o indice do elemento que quer retirar: ");
            int indice;
            scanf("%d", &indice);
            removeElement(&pacientes, indice);
        }
        if(valor == 5){
            int elemento1;
            int elemento2;
            printf("quais elementos quer trocar de posicao:\n");
            printf("cite um elemento pelo indice: ");
            scanf("%d", &elemento1);
            printf("cite outro elemento: ");
            scanf("%d", &elemento2);

            swapElements(&pacientes, elemento1, elemento2);
        }

        if(valor == 6){
            exit(1);
        }
    }
    

    return 0;
}
