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
    int numero;
    int andar_atual;
    int andar_final;
    int corredor_atual;
    int corredor_final;
    int chegou;
} Call;

Call calls[15];

// limpa a matriz e printa o predio, funcoes primarias
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
    printf("\033[32m____________________\033[0m");
    printf("\n");
    for (int j = 0; j < COLUNAS; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            int random_row = rand() % LINHAS;
            matriz[random_row][j] = "[\033[31m⊠\033[0m]";
            printf("Elevador %d no andar %d coluna %d\n", indice, random_row, j);
            indice++;
        }
        printf("\n");
    }
    printf("\033[32m____________________\033[0m");
    printf("\n");

    return;
}

//Funcoes de deslocamento
void mover_ponto_vermelho_adjacente(int andar, int coluna)
{
    // Verificando e movendo o ponto vermelho para uma casa adjacente vazia
    
    //coluna
    if (coluna > 0 && matriz[andar][coluna - 1] == "[ ]")
    {
        matriz[andar][coluna - 1] = "[\033[91m⊠\033[0m]";

        for(int i = 0; i < i_fila; i++){
            if(calls[i].andar_atual == andar && calls[i].corredor_atual == coluna){
                calls[i].corredor_atual = coluna - 1;
            }
        }

        matriz[andar][coluna] = "[ ]";
    }
    //coluna 
    else if (coluna < COLUNAS - 1 && matriz[andar][coluna + 1] == "[ ]")
    {
        matriz[andar][coluna + 1] = "[\033[91m⊠\033[0m]";
        
        for(int i = 0; i < i_fila; i++){
            if(calls[i].andar_atual == andar && calls[i].corredor_atual == coluna){
                calls[i].corredor_atual = coluna + 1;
            }
        }

        matriz[andar][coluna] = "[ ]";
    }
    
    //andar
    else if (andar > 0 && matriz[andar - 1][coluna] == "[ ]")
    {
        matriz[andar - 1][coluna] = "[\033[91m⊠\033[0m]";
        //atualizando posicao do elevador deslocado
        for(int i = 0; i < i_fila; i++){
            if(calls[i].andar_atual == andar && calls[i].corredor_atual == coluna){
                calls[i].andar_atual = andar - 1;
            }
        }

        matriz[andar][coluna] = "[ ]";
    }

    //andar
    else if (andar < LINHAS - 1 && matriz[andar + 1][coluna] == "[ ]")
    {
        matriz[andar + 1][coluna] = "[\033[91m⊠\033[0m]";
        for(int i = 0; i < i_fila; i++){
            if(calls[i].andar_atual == andar && calls[i].corredor_atual == coluna){
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
        if (matriz[andar_atual + 1][coluna_atual] == "[\033[31m⊠\033[0m]" || matriz[andar_atual + 1][coluna_atual] == "[\033[91m⊠\033[0m]")
        {
            mover_ponto_vermelho_adjacente(andar_atual + 1, coluna_atual);
            andar_atual ++;
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]"; // anda uma casa
            matriz[andar_atual - 1][coluna_atual] = "[ ]";            // libera a casa que ele estava anteriormente
        }
        else
        {
            andar_atual++;
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]";
            matriz[andar_atual - 1][coluna_atual] = "[ ]";
        }
    }
    else if (andar_desejado < andar_atual)
    {
        if (matriz[andar_atual - 1][coluna_atual] == "[\033[31m⊠\033[0m]" || matriz[andar_atual - 1][coluna_atual] == "[\033[91m⊠\033[0m]")
        {
            mover_ponto_vermelho_adjacente(andar_atual - 1, coluna_atual);
            andar_atual--;
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]"; // anda uma casa
            matriz[andar_atual - 1][coluna_atual] = "[ ]";            // libera a casa que ele estava anteriormente
        }
        else
        {
            andar_atual--;
            matriz[andar_atual][coluna_atual] = "[\033[91m⊠\033[0m]";
            matriz[andar_atual - 1][coluna_atual] = "[ ]";
        }
    }
    calls[indice].andar_atual = andar_atual; // atualiza a casa

    if (calls[indice].andar_atual == calls[indice].andar_final)
        calls[indice].chegou = 1;

    return;
}


//funcoes de procura
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
    printf("\n");
    printf("\033[31m____________________\033[0m\n");

    printf("Elevador %d esta sendo usado\n", i_fila);

    printf("ANDAR ATUAL %d\n",calls[i_fila].andar_atual = andar);
    printf("PORTA ATUAL %d\n",calls[i_fila].corredor_atual = porta);
    printf("ANDAR DESTINO %d\n",calls[i_fila].andar_final = andar_destino);
    printf("CORREDOR FINAL %d\n",calls[i_fila].corredor_final = porta);
    calls[i_fila].chegou = 0;
    i_fila++;

    printf("\033[31m____________________\033[0m\n");

}

int main()
{
    // inicia elevadores.
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
            // anda uma casa pra todo mundo
            for (int i = 0; i < i_fila; i++)
            {
                if (calls[i].chegou == 0)
                    caminhar(calls[i].andar_final, calls[i].andar_atual, calls[i].corredor_atual, i);
            }
        }
        if (escolha == 2)
        {
            for (int i = 0; i < i_fila; i++)
            {
                while (calls[i].chegou == 0)
                {
                    caminhar(calls[i].andar_final, calls[i].andar_atual,calls[i].corredor_atual, i);
                }
                usleep(60000);
                printf("\033[32mO elevador %d chegou ao seu destino: Andar: %d pela Porta: %d\n\033[0m", i, calls[i].andar_atual, calls[i].corredor_atual);
            }
            exit(1);
        }
    }
    return 0;
}