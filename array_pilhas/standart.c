#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX 5
int stack[MAX];
int top = -1;  

int isFull(){
    if(top == MAX - 1)
        return 1;
    else
        return 0;
}
int isEmpty(){
    if (top == -1)
        return 1;
    else 
        return 0;
}

int push(int x){
    if (isFull()){
        return 1; 
    } 
    top += 1;
    stack[top] = x;
    printf("%d\n", stack[top]);
    return 0;
}

void pop(){
    if (isEmpty()){
        printf("Stack Underflow\n");
        exit(1);
    }
    int value; 
    value = stack[top];
    top -= 1;
    printf("%d\n", value);     
}

int main () {
    printf ("Empilhando: \n");
    
    for (int i = 0;i < MAX + 1; i++){
        if (push(i) == 1){
            printf("Stack Overflow\n"); 
            break;
        }
    }

    while(1){
        pop();
    }
  
    
    return 0; 
}