#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>


#define MAX_SIZE 100

typedef struct {
    char paciente[MAX_SIZE][MAX_SIZE];
    int length;
} StaticList;

void initializeList(StaticList *list) {
    list->length = 0;
}

void removeElement(StaticList *list, int index) {
if (index < 0 || index >= list->length) {
printf("Error: invalid index\n");
return;
}
for (int i = index; i < list->length - 1; i++) {
strcpy(list->paciente[i], list->paciente[i + 1]);
}
list->length--;
}

void insertElement(StaticList *list, char element[MAX_SIZE]) {
    if (list->length >= MAX_SIZE) {
        printf("Error: list overflow\n");
        return;
    }
    int size = strlen(element);
     for (int i = 0; i < size; i++) {
        if (isdigit(element[i])) {
            printf("\n-----ERRO caracteres numericos nao sao permitidos-----");
            break;
        }
    }
    int i;
    for (i = 0; i < list->length; i++) {
        if (strcmp(element, list->paciente[i]) < 0) {
            break;
        }
    }
    for (int j = list->length - 1; j >= i; j--) {
        strcpy(list->paciente[j + 1], list->paciente[j]);
    }
    strcpy(list->paciente[i], element);
    list->length++;
}

void insertSpaces(StaticList *list, char element[MAX_SIZE]) {
    if (list->length >= MAX_SIZE) {
        printf("Error: list overflow\n");
        return;
    }
    strcpy(list->paciente[list->length], element);
    list->length++;
}
void swapElements(StaticList *list, int index1, int index2) {
    if (index1 < 0 || index1 >= list->length || index2 < 0 || index2 >= list->length) {
        printf("Error: invalid indices\n");
        return;
    }
    char temp[MAX_SIZE];
    strcpy(temp, list->paciente[index1]);
    strcpy(list->paciente[index1], list->paciente[index2]);
    strcpy(list->paciente[index2], temp);
}



void printList(StaticList list) {
    printf("\n");
    printf("Fila: ");
    printf("\n");
    for (int i = 0; i < list.length; i++) {
        printf("[%s]-(%d)\n", list.paciente[i], i);
    }
    printf("\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define NUM_NAMES 50

const char *first_names[] = {
    "Enzo",
    "Valentina",
    "Miguel",
    "Alice",
    "Arthur",
    "Sophia",
    "Bernardo",
    "Helena",
    "Heitor",
    "Isabella",
    "Davi",
    "Manuela",
    "Lorenzo",
    "Laura",
    "Théo",
    "Lívia",
    "Pedro",
    "Giovanna",
    "Gabriel",
    "Maria",
    "Matheus",
    "Ana",
    "Vitor",
    "Eduarda",
    "Lucas",
    "Luiza",
    "Vinícius",
    "Carolina",
    "Pedro Henrique",
    "Beatriz",
    "Gustavo",
    "Gabriela",
    "Felipe",
    "Amanda",
    "Henrique",
    "Juliana",
    "Rafael",
    "Julia",
    "Igor",
    "Mariana",
    "André",
    "Camila",
    "Leonardo",
    "Bruna",
    "Fernando",
    "Fernanda",
    "Renato",
    "Isabel",
    "Luciano",
    "Thaís",
    "Guilherme"
};

char *generateName() {
    char *name = malloc((MAX_NAME_LENGTH + 1) * sizeof(char));
    int index = rand() % NUM_NAMES;
    strcpy(name, first_names[index]);
    return name;
}

