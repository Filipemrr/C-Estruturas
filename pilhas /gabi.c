#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct no{
    int elemento;
    struct no *proximo;
}No;

typedef struct pilha{
    struct no *topo;
}pilha;

// funcao push. 
void empilhar(char dado , pilha *principal){
    No *novo = (No*)malloc(sizeof(No));

    if (novo != NULL){
        novo -> elemento = dado; 
        novo -> proximo = principal -> topo;
        principal -> topo = novo;
    }
    else    
        printf("Erro em alocar memoria");
    return;
}
//funcao pop
int desempilhar(pilha *principal){
    No *novo = principal -> topo;
    int elemento;
    if (novo != NULL){
        principal -> topo = novo->proximo;
        novo -> proximo = NULL;
        elemento = novo -> elemento;
        free(novo);
        return elemento;
    }
    return 0;
}
//imprimir 
void imprimir(char posfixa[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c", posfixa[i]); // printa o array "posfixa "
    }
}


int main(){
    //primeiro bloco - basico entre todas 
    pilha *principal; // cria uma struct do tipo pilha chamada de principal
    principal = (pilha*) malloc(sizeof(pilha));//aloca memoria para pilha principal
    principal -> topo = NULL; //declara o topo da pilha principal como null

    printf("Escreva uma expressao infixa (exemplo: a+b*c), sem espacos: \n");
    char expressao[100];
    scanf(" %99[^\n]", expressao);//le a infixa 
    int n = strlen(expressao);//confere a quantidade de caracteres e atribui a n; 
    //primeiro bloco - basico entre todas 
    int j = 0; //indice para o array "posfixa"
    char posfixa[n];//array com a mesma quantidade de caracteres da expressao.


    // VAI COMECAR A LER A EXPRESSA0 INFIXA ((a+b)*c)
    for(int i = 0; i < n; i++)
    {
        if(expressao[i] == '('){ // se o codigo achar o ( ele impilha.
            empilhar(expressao[i], principal);//o (
        }

        else if(expressao[i] == ')') // se o codigo achar o ) ele:
        {
            while(principal->topo != NULL && principal->topo->elemento != '(')
            {
                posfixa[j] = desempilhar(principal);
                j++;
            }

            if(principal->topo != NULL && principal->topo->elemento == '(')
            {
                desempilhar(principal);
            }
        }

        //se ele achar o operando 
        else if(expressao[i] == '+' || expressao[i] == '-' || expressao[i] == '*' || expressao[i] == '/')
        {
            //enquanto o topo da pilha principal nao for null e o elemento do topo for diferente de ( e a expressao sendo lida for uma multiplicacao ou uma divisao ou o elemento for uma soma ou uma adicao
            while(principal->topo != NULL && principal->topo->elemento != '(' && ((expressao[i] == '*' || expressao[i] == '/') || (principal->topo->elemento == '+' || principal->topo->elemento == '-')))
            {
                posfixa[j] = desempilhar(principal);
                j++;
            }

            empilhar(expressao[i], principal);
        }

        // se achar o a,b ou c 
        else
        {
            posfixa[j] = expressao[i]; //GUARDA O OPERADOR no array "posfixa"
            j++; //incrementa o indice do pos fixa 
        }
    } 
        imprimir(posfixa,n);
}

/*
    logica: 
    - a expressao vai sendo varrida
    - se ela achar um ( ele empilha 
    -se achar um operando
    - se achar um a,b ou c ele joga no array. 


    exemplo no codigo: entrada: (a+b)* c ( resposta = ab+c*)


(a+b)*c
pos fixa exemplos: 

(a-(b*c)) = abc*-
(a*(b-c)) = abc-* 
((a*b)-c) = ab*c-
((A-B)*C) = AB-C*














 infixa: operandos sao colocados entre os operadores, ou seja, uma
    operacao normal (ex: 3+4 * 5)

    pos fixa: operandos soa colocados depois dos operadores. 
    ex:(3 4 5 * +) para a operacao (3+4 * 5)

    prefixa: operandos sao colocados antes dos operadores 
    (ex: +3 * 4 5) (equixvalente a 3+4 * 5 na infixa)

*/






