#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define LINHAS 9
#define COLUNAS 3
char *matriz[LINHAS][COLUNAS];

void printar_predio()
    {
        for (int i = LINHAS - 1; i >= 0; i--)
        {
            if (i <= 9)
            {
                printf("   %d", i);
            }
            else if (i > 9 && i <= 99)
            {
                printf("  %d", i);
            }
            else
            {
                printf(" %d", i);
            }

            for (int j = COLUNAS - 1; j >= 0; j--)
            {
                printf("%s ", matriz[i][j]);
            }
            printf("\n");
            // usleep(6000);
        }
    }

int main(){
     for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = "[ ]";
        }
    }

     for (int j = 0; j < COLUNAS; j++)
    {
        for (int k = 0; k < 1; k++)
        {
            int random_row = rand() % LINHAS;
            matriz[random_row][j] = "[\033[31m⊠\033[0m]";
        }
    }

    printar_predio();
    return 0;
}