#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#define size 100

char stack[size];
int top = -1;

int isEmpty(){
    if (top == -1)
        return 1;
    else 
        return 0;
}

void push(char byte)
{
    top += 1;
    stack[top] = byte;
}

void pop()
{
    printf("%c", stack[top]);
    top -= 1;
    return;
}

int main()
{
    char text[size];
    fgets(text, size, stdin);
    int tam = strlen(text);
    tam -= 1;
    int y = 0;

    while(1){
        
        if(y >= tam){
            printf("\n");
            return 0;
        }
            
        
        while(1)
        {
            if((isspace(text[y]))){
                y++;
                break;
            }
            push(text[y]);
            y++;
        }
       while(1)
        {
            if(isEmpty())
                break;;
            pop();
        }
        printf(" ");
    }
    
    return 0;
}
