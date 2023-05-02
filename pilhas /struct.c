#include <stdio.h>
#define SIZE 256

// tipo da struct.
// como ela vai ser representada, com que variaveis. 
struct ficha_aluno{
    char nome[40]; 
    int numero; 
    float nota; 
};

struct ficha_aluno aluno1;//tipo: ficha aluno, para o aluno1 
struct ficha_aluno aluno2; 

int main (){

printf("\n ------------- Cadastro de Aluno ---------\n\n\n"); 

// depositando o nome do aluno dentro da viriavel 
printf("Nome do Aluno .......: "); 
fgets(aluno1.nome, 40, stdin);

//depositando o numero do aluno 
printf("Digite o numero do aluno: ");
scanf("%d", &aluno1.numero);

//depositando a nota do aluno
printf("informe a nota do aluno: ");
scanf("%f", &aluno1.nota);
   
printf("%.1f", aluno1.nota);

}