#include <stdio.h>
#include <string.h>
#define SIZE 256

int stack[SIZE]; 
int top = -1;

int isFull(){
    if(top == SIZE - 1)
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

void push(int x ){
    if(isFull()){
        printf("STACK OVERFLOW");
        return;
    }
    top += 1;
    stack[top] = x;
}

void pop(){
    if(isEmpty()){
        printf("\nSTACK UNDERFLOW\n");
        return;
    }
    top -= 1;
    return;
}

int main(){

    printf("\n1. PUSH\n2. POP\n3.PRINT THE TOP ELEMENT\n4.PRINT ALL ELEMENTS OF THE STACK\n5. QUIT\n");
    

    while (1)
    {
    printf("\nPlease enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1){
        int element;
        printf("\nWich one element you want push in the stack?: ");
        scanf("%d", &element);
        push(element);
    }

    if (choice == 2){

        pop();
    }

    if(choice == 3){
        if(top == -1){
            printf("\n The Stack have no elements\n");
        }
        else{
        printf("\nTop element of the Stack is: %d\n", stack[top]);
        }
    }
    
    if(choice == 4){
        if(top == - 1){
            printf("\nSTACK UNDERFLOW\n");
        }
        else{
        printf("\nTHE STACK IS:\n");
        for(int i = top; i != -1; i--)
        {
            printf("%d\n", stack[i]);
        }
    }
    }
    if (choice == 5){
        break;
    }
    }

    

    return 0; 
}