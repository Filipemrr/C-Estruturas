#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAX_STRING_SIZE 1000
#define MAX_OUTPUTS 100
#define LINHAS 300
#define COLUNAS 3
int andar_cima = 0;
int coluna_cima = 0;
int andar_baixo = 0;
int coluna_baixo = 0;
int tem_gente = 0;
int retorno;
int andar_exclusao, coluna_exclusao; // auxiliar que indica o andar e a coluna do elevador mais proximo
int elevador_mais_proximo_andar, elevador_mais_proximo_coluna;
char *matriz[LINHAS][COLUNAS];
int i_fila = 0;

typedef struct
{
    int andar_atual;
    int andar_final;
    int corredor_final;
    int corredor_atual;
    int andar_de_busca;
    int corredor_de_busca;
    int pedida;
    int chegou;
    int tem_gente;
} Call;

Call calls[15];

void iniciando_elevador()
{
    srand(time(0));

    // Limpa a matriz
    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = "[ ]";
        }
    }

    // Adiciona 15 elevadores distribuídos na matriz
    matriz[3][0] = "[\033[91m⊠\033[0m]";
    matriz[279][0] = "[\033[91m⊠\033[0m]";
    matriz[70][0] = "[\033[91m⊠\033[0m]";
    matriz[137][0] = "[\033[91m⊠\033[0m]";
    matriz[240][0] = "[\033[91m⊠\033[0m]";

    matriz[148][1] = "[\033[91m⊠\033[0m]";
    matriz[224][1] = "[\033[91m⊠\033[0m]";
    matriz[93][1] = "[\033[91m⊠\033[0m]";
    matriz[118][1] = "[\033[91m⊠\033[0m]";
    matriz[293][1] = "[\033[91m⊠\033[0m]";

    matriz[268][2] = "[\033[91m⊠\033[0m]";
    matriz[192][2] = "[\033[91m⊠\033[0m]";
    matriz[27][2] = "[\033[91m⊠\033[0m]";
    matriz[52][2] = "[\033[91m⊠\033[0m]";
    matriz[162][2] = "[\033[91m⊠\033[0m]";

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            if (matriz[i][j] == "[\033[91m⊠\033[0m]")
            {
                printf("Elevador encontrado no andar %d, coluna %d\n", i, j);
            }
        }
    }

    return;
}

void imprimir_matriz()
{
    printf("\n");
    printf("\033[32m____________________\033[0m");
    printf("\n");

    for (int i = LINHAS - 1; i >= 0; i--)
    {
        printf("%3d ", i);
        for (int j = 0; j < COLUNAS; j++)
        {
            printf("%s ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\033[32m____________________\033[0m");
    printf("\n");
}

void reaproveitar_elevadores()
{

    for (int i = 0; i < LINHAS; i++)
    {
        for (int j = 0; j < COLUNAS; j++)
        {
            matriz[i][j] = "[\033[91m⊠\033[0m]"; // vermelho claro (disponivel))
            matriz[i][j] = "[\033[31m⊠\033[0m]"; // vermelho escuro (indisponivel)
        }
    }

    for (int i = 0; i < i_fila; i++)
    {
        calls[i].andar_final = 0;
        calls[i].andar_atual = 0;
        calls[i].corredor_atual = 0;
        calls[i].corredor_final = 0;
        calls[i].chegou = 0;
    }
    i_fila = 0;
}

// Funcoes de deslocamento
void mover_ponto_vermelho_adjacente(int andar, int coluna)
{
    // Verificando e movendo o ponto vermelho para uma casa adjacente vazia

    // coluna
    if (coluna > 0 && matriz[andar][coluna - 1] == "[ ]")
    {
        matriz[andar][coluna - 1] = "[\033[91m⊠\033[0m]";

        for (int i = 0; i < i_fila; i++)
        {
            if (calls[i].andar_atual == andar && calls[i].corredor_atual == coluna)
            {
                calls[i].corredor_atual = coluna - 1;
            }
        }

        matriz[andar][coluna] = "[ ]";
    }
    // coluna
    else if (coluna < COLUNAS - 1 && matriz[andar][coluna + 1] == "[ ]")
    {
        matriz[andar][coluna + 1] = "[\033[91m⊠\033[0m]";

        for (int i = 0; i < i_fila; i++)
        {
            if (calls[i].andar_atual == andar && calls[i].corredor_atual == coluna)
            {
                calls[i].corredor_atual = coluna + 1;
            }
        }

        matriz[andar][coluna] = "[ ]";
    }

    // andar
    else if (andar > 0 && matriz[andar - 1][coluna] == "[ ]")
    {
        matriz[andar - 1][coluna] = "[\033[91m⊠\033[0m]";
        // atualizando posicao do elevador deslocado
        for (int i = 0; i < i_fila; i++)
        {
            if (calls[i].andar_atual == andar && calls[i].corredor_atual == coluna)
            {
                calls[i].andar_atual = andar - 1;
            }
        }

        matriz[andar][coluna] = "[ ]";
    }

    // andar
    else if (andar < LINHAS - 1 && matriz[andar + 1][coluna] == "[ ]")
    {
        matriz[andar + 1][coluna] = "[\033[91m⊠\033[0m]";
        for (int i = 0; i < i_fila; i++)
        {
            if (calls[i].andar_atual == andar && calls[i].corredor_atual == coluna)
            {
                calls[i].andar_atual = andar + 1;
            }
        }
        matriz[andar][coluna] = "[ ]";
    }
}
void caminhar(int andar_desejado, int andar_atual, int coluna_atual, int indice)
{
    if (andar_desejado > andar_atual)
    {
        if (matriz[andar_atual + 1][coluna_atual] == "[\033[91m⊠\033[0m]" || matriz[andar_atual + 1][coluna_atual] == "[\033[31m⊠\033[0m]")
        {
            for (int i = 0; i < i_fila; i++)
            {
                if (andar_atual + 1 == calls[i].andar_atual && coluna_atual == calls[i].corredor_atual)
                {
                    calls[i].chegou = 0;
                    break;
                }
            }
            mover_ponto_vermelho_adjacente(andar_atual + 1, coluna_atual);
            andar_atual++;
            matriz[andar_atual][coluna_atual] = "[\033[31m⊠\033[0m]"; // anda uma casa
            matriz[andar_atual - 1][coluna_atual] = "[ ]";            // libera a casa que ele estava anteriormente
        }
        else
        {
            matriz[andar_atual + 1][coluna_atual] = "[\033[31m⊠\033[0m]";
            matriz[andar_atual][coluna_atual] = "[ ]";
            andar_atual++;
        }

        printf("\033[32mO elevador %d subiu do andar [%d] para o andar [%d] em direcao ao andar %d\033[0m\n", indice, andar_atual - 1, andar_atual, andar_desejado);
    }
    else if (andar_desejado < andar_atual)
    {

        if (matriz[andar_atual - 1][coluna_atual] == "[\033[91m⊠\033[0m]" || matriz[andar_atual - 1][coluna_atual] == "[\033[31m⊠\033[0m]")
        {
            for (int i = 0; i < i_fila; i++)
            {
                if (andar_atual - 1 == calls[i].andar_atual && coluna_atual == calls[i].corredor_atual)
                {
                    calls[i].chegou = 0;
                    break;
                }
            }
            mover_ponto_vermelho_adjacente(andar_atual - 1, coluna_atual);
            andar_atual--;
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]"; // anda uma casa
            matriz[andar_atual - 1][coluna_atual] = "[ ]";            // libera a casa que ele estava anteriormente
        }
        else
        {
            matriz[andar_atual - 1][coluna_atual] = "[\033[91m⊠\033[0m]";
            matriz[andar_atual][coluna_atual] = "[ ]";
            andar_atual--;
        }

        printf("\033[32mO elevador %d desceu do andar [%d] para o andar [%d]  em direcao  %d\033[0m\n", indice, andar_atual + 1, andar_atual, andar_desejado);
    }

    calls[indice].andar_atual = andar_atual; // atualiza a casa
    // marca que o elevador buscou os passageiros
    if (andar_atual == calls[indice].pedida && calls[indice].tem_gente == 0)
        calls[indice].tem_gente = 1;

    // marca que o elevador chegou ao destino final
    if (calls[indice].andar_atual == calls[indice].andar_final && calls[indice].tem_gente == 1)
        calls[indice].chegou = 1;

    return;
}

void terminar_execucao()
{
    
    int chegou_todos = 0;
    while (!chegou_todos)
    {
        chegou_todos = 1; // Supomos que todos os elevadores chegaram ao destino

        for (int i = 0; i < i_fila; i++)
        {
            //printf("LINE: %d\n", __LINE__);//
            if (calls[i].chegou == 0)
            {
                if (calls[i].tem_gente == 0)
                    caminhar(calls[i].pedida, calls[i].andar_atual, calls[i].corredor_atual, i);
                else
                    caminhar(calls[i].andar_final, calls[i].andar_atual, calls[i].corredor_atual, i);

                chegou_todos = 0; // Pelo menos um elevador não chegou ao destino
            }
        }
    }
    for (int i = 0; i < i_fila; i++)
    {
        printf("\033[32mO elevador  chegou ao seu destino: Andar: %d pela Porta: %d\n\033[0m", calls[i].andar_atual, calls[i].corredor_atual);
        // usleep(600000);
    }
}

// funcoes de procura
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
            if (matriz[andar + i][w] == "[\033[91m⊠\033[0m]")
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
                // printf("\nNenhuma elevador acima");
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
            if (matriz[andar - i][w] == "[\033[91m⊠\033[0m]")
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
int buscando_pedido()
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

    printf("\n");
    printf("\033[31m____________________\033[0m\n");

    printf("Chamada %d cadastrada\n", i_fila);

    printf("ANDAR ATUAL %d\n", calls[i_fila].andar_atual = andar_exclusao);
    printf("PORTA ATUAL %d\n", calls[i_fila].corredor_atual = coluna_exclusao);
    printf("ANDAR DESTINO %d\n", calls[i_fila].andar_final = andar_destino);
    printf("ANDAR DE BUSCA %d\n", calls[i_fila].andar_de_busca = andar_exclusao);
    printf("CORREDOR DA BUSCA %d\n", calls[i_fila].corredor_de_busca = coluna_exclusao);
    printf("PEDIDA %d\n", calls[i_fila].pedida = andar);

    calls[i_fila].chegou = 0;
    calls[i_fila].tem_gente = 0;

    i_fila++;
    printf("\033[31m____________________\033[0m\n");

    return retorno;
}

int main()
{
    iniciando_elevador();
    int escolha;

    while (1)
    {
        // solicita um elevador
        printf("\n\n");
        printf("Aperte 1 para pedir um elevador?\n");
        printf("Aperte 2 para encerrar");
        printf("\nFaça uma escolha: ");
        scanf("%d", &escolha);

        if (escolha == 1)
        {
            buscando_pedido();

            for (int i = 0; i < i_fila; i++)
            {
                // se o elevador ja chegou no seu destino
                if (calls[i].chegou == 1)
                    continue;

                // se o elevador esta indo buscar os passageiros
                if (calls[i].tem_gente == 0)
                    caminhar(calls[i].pedida, calls[i].andar_atual, calls[i].corredor_atual, i);

                // se o elevador esta indo levar os passageiros no destino
                if (calls[i].tem_gente == 1)
                {
                    printf("- %d %d %d", calls[i].andar_final, calls[i].andar_atual, calls[i].corredor_atual);
                    caminhar(calls[i].andar_final, calls[i].andar_atual, calls[i].corredor_atual, i);
                }
            }

            // printar matriz ao final de toda interacao
            imprimir_matriz();
        }

        if (escolha == 2)
        {
            terminar_execucao();
            imprimir_matriz();
            exit(1);
        }
    }
    return 0;
}
