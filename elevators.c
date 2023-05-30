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
int andar_exclusao, coluna_exclusao; // auxiliar que indica o andar e a coluna do elevador mais proximo
int elevador_mais_proximo_andar, elevador_mais_proximo_coluna;
char *matriz[LINHAS][COLUNAS];
int i_fila = 0;

typedef struct
{
    int andar_atual;
    int andar_final;
    int corredor_atual;
    int corredor_final;
    int chegou;
} Call;

Call calls[15];

// limpa a matriz e printa o predio, funcoes de prompt
void limpar_matriz()
{
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (strcmp(matriz[i][j], "[\033[32m⇳\033[0m]") == 0 || strcmp(matriz[i][j], "[\033[93m⇫\033[0m]") == 0)
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
        // usleep(60000);
    }
}

void mover_ponto_vermelho_adjacente(int andar, int coluna)
{
    // Verificando e movendo o ponto vermelho para uma casa adjacente vazia
    if (coluna > 0 && matriz[andar][coluna - 1] == "[ ]")
    {
        matriz[andar][coluna - 1] = "[\033[91m⊠\033[0m]";
        matriz[andar][coluna] = "[ ]";
    }
    else if (coluna < COLUNAS - 1 && matriz[andar][coluna + 1] == "[ ]")
    {
        matriz[andar][coluna + 1] = "[\033[91m⊠\033[0m]";
        matriz[andar][coluna] = "[ ]";
    }
    else if (andar > 0 && matriz[andar - 1][coluna] == "[ ]")
    {
        matriz[andar - 1][coluna] = "[\033[91m⊠\033[0m]";
        matriz[andar][coluna] = "[ ]";
    }
    else if (andar < LINHAS - 1 && matriz[andar + 1][coluna] == "[ ]")
    {
        matriz[andar + 1][coluna] = "[\033[91m⊠\033[0m]";
        matriz[andar][coluna] = "[ ]";
    }
}

void caminhar(int andar_desejado, int andar_atual, int coluna_atual, int indice)
{
    if (andar_desejado > andar_atual)
    {
        andar_atual++;
        if (matriz[andar_atual][coluna_atual] == "[\033[31m⊠\033[0m]" || matriz[andar_atual][coluna_atual] == "[\033[91m⊠\033[0m]")
        {
            mover_ponto_vermelho_adjacente(andar_atual, coluna_atual);
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]"; // anda uma casa
            matriz[andar_atual - 1][coluna_atual] = "[ ]";            // libera a casa que ele estava anteriormente
        }
        else
        {
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]";
            matriz[andar_atual - 1][coluna_atual] = "[ ]";
        }
    }
    else if (andar_desejado > andar_atual)
    {
        andar_atual--;
        if (matriz[andar_atual][coluna_atual] == "[\033[31m⊠\033[0m]" || matriz[andar_atual][coluna_atual] == "[\033[91m⊠\033[0m]")
        {
            mover_ponto_vermelho_adjacente(andar_atual, coluna_atual);
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]"; // anda uma casa
            matriz[andar_atual - 1][coluna_atual] = "[ ]";            // libera a casa que ele estava anteriormente
        }
        else
        {
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]";
            matriz[andar_atual - 1][coluna_atual] = "[ ]";
        }
    }
    calls[indice].andar_atual = andar_atual; // atualiza a casa atual

    if (calls[indice].andar_atual == calls[indice].andar_final)
        calls[indice].chegou = 1;

    return;
}

void iniciando_elevador()
{
    srand(time(0));

    // gera a matriz
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = "[ ]";
        }
    }

    // Adicionando [elevadores] aleatoriamente em cada coluna
    // printando posicao dos elevadores
    int indice = 0;
    printf("Elevadores estao nas posicoes:\n");
    for (int j = 0; j < COLUNAS; j++)
    {
        indice++;
        for (int k = 0; k < 5; k++)
        {
            int random_row = rand() % LINHAS;
            matriz[random_row][j] = "[\033[31m⊠\033[0m]";
            printf("Elevador %d no andar %d coluna %d\n", indice, random_row, j);
            indice++;
        }
        printf("\n");
    }
}

// essas 2 funcoes interagem juntas e servem para tracar a busca ate o pedido que foi feito
//"buscando pedido" recebe o pedido, usa a "achar mais proximo" para encontrar o elevador mais proximo
// entao, o elevador mais proximo vai ate o pedido que foi feito.
void tracar_busca(int andar1, int coluna1, int andar2, int coluna2)
{
    int indice_andar = andar1;
    int indice_coluna = coluna1;

    int delta_andar = (andar2 > andar1) ? 1 : -1;
    int delta_coluna = (coluna2 > coluna1) ? 1 : -1;

    while (indice_andar != andar2 || indice_coluna != coluna2)
    {
        if (indice_andar != andar1 || indice_coluna != coluna1)
        {
            matriz[indice_andar][indice_coluna] = "[\033[32m⇳\033[0m]";
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
            // achou
            if (matriz[andar + i][w] == "[\033[31m⊠\033[0m]")
            {
                flag_up = 1;

                if (matriz[andar + i][porta] != "[ ]")
                    coluna_cima = porta;
                else
                    coluna_cima = w;

                andar_cima = andar + i;

                break;
            }

            // matriz[andar + i][w] = "[\033[32m⊠\033[0m]";
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
    for (int i = 1; i < 300; i++)
    {
        porta = 1;
        for (int w = 0; w < 3; w++)
        {

            // achou
            if (matriz[andar - i][w] == "[\033[31m⊠\033[0m]")
            {
                flag_down = 1;
                andar_baixo = andar - i;

                if (matriz[andar + i][porta] != "[ ]")
                    coluna_baixo = porta;
                else
                    coluna_baixo = w;
                break;
            }
            // matriz[andar - i][w] = "[\033[32m⊠\033[0m]";
            if (andar - i <= 0)
            {
                // printf("\nNenhuma elevador acima");
                break;
            }
        }

        if (flag_down == 1)
        {
            break;
        }
    }

    int elevador_cima;
    int elevador_baixo;

    elevador_cima = (andar_cima - andar) + (coluna_cima - porta);
    elevador_baixo = (andar - andar_baixo) + (porta - coluna_baixo);

    // varredura de cima eh mais proxima
    if (elevador_cima < elevador_baixo && flag_up == 1)
        return 1;
    // varredura de baixo eh mais proxima
    else if (elevador_baixo < elevador_cima && flag_down == 1)
        return 0;
    else // ambas tem mesma distancia
        return 2;
}

void buscando_pedido()
{
    int flagCima = 0;
    int flagBaixo = 0;
    int andar, porta;
    int andar_destino;

    // pra onde foi pedido o elevador
    printf("\nQue andar voce esta? ");
    scanf("%d", &andar);

    porta = rand() % COLUNAS;

    printf("\nPara que andar vai ?");
    scanf("%d", &andar_destino);

    matriz[andar][porta] = "[\033[93m⊠\033[0m]"; //vermelho de uso

    if (andar > 299 || porta < 0 || porta > 2)
    {
        printf("Erro, entrada Invalida\n");
        exit(1);
    }

    retorno = achar_mais_proximo(andar, porta);

    if (retorno == 1 || retorno == 2)
    {
        // tracar_busca(andar, porta, andar_cima, coluna_cima);
        flagCima = 1;
        andar_exclusao = andar_cima;
        coluna_exclusao = coluna_cima;
    }

    if (retorno == 0)
    {
        // tracar_busca(andar, porta, andar_baixo, coluna_baixo);
        flagBaixo = 1;
        andar_exclusao = andar_baixo;
        coluna_exclusao = coluna_baixo;
    }
    matriz[andar][porta] = "[\033[91m⊠\033[0m]"; // tom de vermelho diferente
    matriz[andar_exclusao][coluna_exclusao] = "[ ]"; // onde ele achou o mais prox


    //inicia um elevador
    printf("%d\n",calls[i_fila].andar_atual = andar);
    printf("%d\n",calls[i_fila].corredor_atual = porta);
    printf("%d\n",calls[i_fila].andar_final = andar_destino);
    printf("%d\n",calls[i_fila].corredor_final = porta);
    calls[i_fila].chegou = 0;
    i_fila++;
}

int main()
{
    // inicia elevadores.
    iniciando_elevador();
    int escolha;

    while (1)
    {
        // solicita um elevador
        printf("Aperte 1 para pedir um elevador?\n");
        printf("Aperte 2 para encerrar");
        printf("\nFaça uma escolha: ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            buscando_pedido();
            // anda uma casa pra todo mundo
            exit(1);
            for (int i = 0; i < i_fila; i++)
            {
                if (calls[i].chegou == 0)
                    caminhar(calls[i].andar_final, calls[i].andar_atual, calls[i].andar_final, i);
            }
        }
        if (escolha == 2)
        {
            for (int i = 0; i < i_fila; i++)
            {
                while (calls[i].chegou == 0)
                {
                    caminhar(calls[i].andar_final, calls[i].andar_atual, calls[i].andar_final, i);
                }
                printf("O elevador %d chegou ao seu destino: ANDAR %d PORTA%d", i, calls[i].andar_atual, calls[i].corredor_atual);
            }
            exit(1);
        }
    }
    return 0;
}