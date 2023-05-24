#include <stdio.h>

void ordenar(int linhas, char candidato[][100]) {
    for (int i = 0; i < linhas - 1; i++) {
        for (int j = 0; j < linhas - i - 1; j++) {
            if (candidato[j][0] < candidato[j + 1][0]) {
                char temp[100];
                for (int k = 0; k < 100; k++) {
                    temp[k] = candidato[j][k];
                    candidato[j][k] = candidato[j + 1][k];
                    candidato[j + 1][k] = temp[k];
                }
            }
        }
    }
}

int main() {
    int linhas;
    printf("Digite o número de linhas: ");
    scanf("%d", &linhas);
    getchar();

    char candidato[linhas][100];
    int valor[linhas];

    for (int i = 0; i < linhas; i++) {
        valor[i] = 0;
        scanf("%s", candidato[valor[i]]);
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        // Calcula o valor com base em a, b e c
        valor[i] = a + b + c;
    }

    // Ordenar a matriz pelo primeiro índice (valor)
    //ordenar(linhas, candidato);

    for (int i = 0; i < linhas; i++) {
        printf("%s\n",candidato[valor[i]]); // Exibe o valor e o nome do candidato
    }

    return 0;
}
