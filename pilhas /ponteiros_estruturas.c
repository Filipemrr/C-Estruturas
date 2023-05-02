 #include <stdio.h>
 #include <stdlib.h>

 int main(){
    struct horario{
        int hora; 
        int minuto; 
        int segundo;
    };
    
struct horario agora, *depois;
//declaramos uma estrutura do tipo horario chamada agora 
// e um ponteiro que aponta para uma estrutura do tipo horario.

depois = &agora;
// o endereco de memorio do meu ponteiro eh = o endereco de memoria da
// struct "agora", ou seja o ponteiro aponta para struct.

depois->hora = 20;
depois->minuto=15;
depois->segundo = 50; 
// a seta serve pra apontar para qual
// variavel da strct eu quero mudar

printf("%d:%d:%d\n", agora.hora, agora.hora, agora.segundo);
 }


/*
    1. DECLAREI UMA STRUCT E DEFINI QUE O TIPO DELA EH HORARIO
    2. CRIEI DUAS VARIAVEIS DO TIPO HORARIO
    3. APONTEI O PONTEIRO PARA A VARIAVEL "AGORA"
    4. ATRAVES DO PONTEIRO EU ATRIBUI VALORES A STRUCT "AGORA" DO TIPO
    HORARIO.
*/