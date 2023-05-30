#include <stdio.h>

// Função para trocar dois elementos de posição
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função do ISSA (Improved Selection Sort Algorithm)
void issaSort(int arr[], int n) {
    int left = 0;   // Índice inicial do array
    int right = n - 1;  // Índice final do array 

    while (left < right) {
        int min_idx = left;
        int max_idx = left;
        printf("%d\n", right);

        // Encontre o índice do mínimo e do máximo elemento do array
        for (int i = left + 1; i <= right; i++) {
            if (arr[i] < arr[min_idx]) {
                min_idx = i;
            } 
			else if (arr[i] > arr[max_idx]) {
                max_idx = i;
            }
        }

        // Coloque o mínimo na posição correta no início do array classificado
        swap(&arr[left], &arr[min_idx]);

        // Se o máximo estiver na posição left, após a troca acima,
        // atualize o índice do máximo para a nova posição correta
        if (max_idx == left) {
            max_idx = min_idx;
        }

        // Coloque o máximo na posição correta no final do array classificado
        swap(&arr[right], &arr[max_idx]);

        // Atualize os índices para a próxima iteração
        left++;
        right--;
    }
}

// Função auxiliar para imprimir o array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array antes da ordenação: ");
    printArray(arr, n);

    issaSort(arr, n);

    printf("Array após a ordenação: ");
    printArray(arr, n);

    return 0;
}