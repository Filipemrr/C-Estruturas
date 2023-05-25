#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LINHAS 300
#define COLUNAS 3
int andar_cima = 0;
int coluna_cima = 0;
int andar_baixo = 0;
int coluna_baixo = 0;
int retorno;
int elevador_mais_proximo_andar, elevador_mais_proximo_coluna;
char *matriz[LINHAS][COLUNAS];

int achar_mais_proximo(int andar, int porta)
{
    int flag_up = 0;
    int flag_down = 0;

    // varre pra cima
    for (int i = 1; i < 300; i++)
    {
        porta = 0;
        for (int w = 0; w < 3; w++)
        {
            //achou
            if (matriz[andar + i][w] != "[ ]"){
                flag_up = 1;

                if(matriz[andar + i][porta] != "[ ]")
                    coluna_cima = porta;
                else
                    coluna_cima = w;
    
                andar_cima = andar + i;

                break;
            }

            //matriz[andar + i][w] = "[\033[32m⊠\033[0m]";
            if (andar + i >= LINHAS)
            {
                flag_up = 0;
                printf("\nNenhuma elevador acima");
                break;
            }
        }
        if (flag_up == 1)
            break;
    }

    // varre pra baixo
    for (int i = 1; i < 300; i++){
        porta = 1;
        for (int w = 0; w < 3; w++){

            //achou
            if (matriz[andar - i][w] != "[ ]"){
                flag_down = 1;
                andar_baixo = andar - i;

                if(matriz[andar + i][porta] != "[ ]")
                    coluna_baixo = porta;
                else
                    coluna_baixo = w;

                break;
            }
            //matriz[andar - i][w] = "[\033[32m⊠\033[0m]";
            if (andar - i <= 0){
                printf("\nNenhuma elevador acima");
                break;
            }
        }

        if (flag_down == 1){
            break;
        }
    }

    int elevador_cima;
    int elevador_baixo;

    elevador_cima = (andar_cima - andar) + (coluna_cima - porta);
    elevador_baixo = (andar - andar_baixo) + (porta - coluna_baixo);

    //varredura de cima eh mais proxima
    if(elevador_cima < elevador_baixo)
        return 1;
    //varredura de baixo eh mais proxima
    else if (elevador_baixo < elevador_cima)
        return 0;
    else//ambas tem mesma distancia
        return 2;
    
}

void limpar_matriz()
    {
        for (int i = 0; i < LINHAS; i++)
        {
            for (int j = 0; j < COLUNAS; j++)
            {
                if (strcmp(matriz[i][j], "[\033[32m⊠\033[0m]") == 0 || strcmp(matriz[i][j], "[\033[93m⊠\033[0m]") == 0)
                {
                    matriz[i][j] = "[ ]";
                }
            }
        }
    }

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

void tracar_caminho(int andar1, int coluna1, int andar2, int coluna2)
{
    int indice_andar = andar1;
    int indice_coluna = coluna1;

    int delta_andar = (andar2 > andar1) ? 1 : -1;
    int delta_coluna = (coluna2 > coluna1) ? 1 : -1;

    while (indice_andar != andar2 || indice_coluna != coluna2)
    {
        if (indice_andar != andar1 || indice_coluna != coluna1)
        {
            matriz[indice_andar][indice_coluna] = "[\033[32m⊠\033[0m]";
        }

        if (indice_coluna != coluna2)
        {
            indice_coluna += delta_coluna;
        }
        else if (indice_andar != andar2)
        {
            indice_andar += delta_andar;
        }
    }
}



int main()
{
    // Inicializando a semente do gerador de números aleatórios
    srand(time(0));

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = "[ ]";
        }
    }

    // Adicionando [E] aleatoriamente em cada coluna
    for (int j = 0; j < COLUNAS; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            int random_row = rand() % LINHAS;
            matriz[random_row][j] = "[\033[31m⊠\033[0m]";
        }
    }
    printf("\n");
    printar_predio();
    printf("     2   1   0\n\n");

    while (1)
    {
        int andar, porta, escolha;

        printf("Quer pedir um elevador? Aperte 1\n");
        printf("Se já chegou onde quer, aperte 2\n");
        printf("Faça uma escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            andar = rand() % LINHAS;
            porta = rand() % COLUNAS;

            matriz[andar][porta] = "[\033[93m⊠\033[0m]";
            retorno = achar_mais_proximo(andar, porta);
        }
        if (escolha == 2)
        {
            if (retorno == 1 || retorno == 2)
                tracar_caminho(andar, porta, andar_cima, coluna_cima);

            if (retorno == 0)
                tracar_caminho(andar, porta, andar_baixo, coluna_baixo);
        }
        if (escolha == 3)
        {
            printar_predio();
        }

        // usleep(1000000);  // Pausa de 1 segundo
    }

    return 0;
}
