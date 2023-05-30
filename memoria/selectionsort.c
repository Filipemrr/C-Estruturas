#include <stdio.h>

// Função para trocar dois elementos de posição
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função do Selection Sort
void issaSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        int maxIndex = i;
        printf("%d\n", n);
        
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
            if (arr[j] > arr[maxIndex])
                maxIndex = j;
        }
        
        // If the minimum element is not at the starting position
        if (minIndex != i)
            swap(&arr[i], &arr[minIndex]);
        
        // If the maximum element is at the starting position after swapping
        if (maxIndex == i)
            maxIndex = minIndex;
        
        // If the maximum element is not at the last position
        if (maxIndex != n - 1)
            swap(&arr[n - 1], &arr[maxIndex]);
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
    int arr[] = {10,1,32,34,1,23,4,5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array antes da ordenação: ");
    printArray(arr, n);

    issaSort(arr, n);

    printf("Array após a ordenação: ");
    printArray(arr, n);

    return 0;
}

