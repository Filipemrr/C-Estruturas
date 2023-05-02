 #include <stdio.h>
 #include <stdlib.h>

 int main(){
    struct horario{
        int *pHora; 
        int *pMinuto; 
        int *pSegundo;
    };
    
struct horario hoje;

    int hora = 200; 
    int minuto = 300;
    int segundo = 400;

    hoje.pHora = &hora;
    hoje.pMinuto= &minuto; 
    hoje.pSegundo = &segundo;
    
    *hoje.pHora = 1000;
    
    printf("Hora: %d\n", *hoje.pHora); // printando o valor do ponteiro
    printf("Minuto: %d\n", *hoje.pMinuto);
    printf("Segundo: %d\n", *hoje.pSegundo);

    
 }
/*
    1. declarei uma struct e  tipei ela como "horario"
    2. declarei uma variavel hoje do tipo horario
    3. declarei 3 variaveis inteiras e dei valores para elas
    4. disse que o endereco do  ponteiro "phora" dentro da minha variavel struct
    aponta no endereco de memoria de int hora; 
    5. printei o valor dentro dos ponteiros. 
    no caso os ponteiros esta apontando no endereco de memoria 
    de outras variaveis, entao eles estao meramente impimindo oque 
    esta no endereco de memoria que ele esta apontando.

*/
