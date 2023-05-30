#include <stdio.h>

void bubble(int array[], int n) {
    int i, j, aux;
    int trocas;

    for (i = 0; i < n - 1; i++) {
        trocas = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
                trocas = 1;
            }
        }

        if (trocas == 0) {
            // Nenhuma troca ocorreu nesta iteração, o array está ordenado
            break;
        }
    }
}

int main() {
    int array[] = {3, 6, 2, 7, 8};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Array antes da ordenacao: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    bubble(array, n);

    printf("Array apos a ordenacao: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
