 #include <stdio.h>
 #include <stdlib.h>

 int main(){

    int x = 10;
    float y = 20.50;
    char z = 'a';

    int *pX = &x; //ponteiro px aponta para o endereco da variavel x 
    float *pY = &y; // o ponteiro py aponta para o endereco da variavel y
    char *pZ = &z;// o ponteiro pZ aponta para o endereco da variavel z 

    printf("Endereco x = %d Valor x = %d\n", pX, *pX); 
    printf("Endereco y = %d Valor y = %f\n", pY, *pY); 
    printf("Endereco x = %d Valor x = %c\n", pZ, *pZ); 
    
    double soma = *pX + *pY; // somando os valores que estao 
    // nos enderecos apontados px e py, que no caso sao os valores de
    // x e y respectivamente.

    printf("\nSoma: %f\n", soma);

    // se eu printar o valor do meu ponteiro ele vai ser o valor
    // que estava alocado dentro do endereco que eu apontei ele. 
    return 0;
 }

 // *pX = valor do meu ponteiro
// pX = endereco de memoria do meu ponteiro.