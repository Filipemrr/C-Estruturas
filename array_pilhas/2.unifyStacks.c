#include <stdio.h>
#include <string.h>
#define SIZE 256

int stack1[SIZE];
int stack2[SIZE]; 
int top1 = -1;
int top2 = -1;

int isEmpty1(){
    if (top1 == -1)
        return 1;
    else
        return 0;
}
int isEmpty2(){
    if (top2 == -1)
        return 1;
    else
        return 0;
}


//PUSH POP PRIMEIRA STACK:
void push1(int x ){
    top1 += 1;
    stack1[top1] = x;
}
void pop1(){
    if (isEmpty1()){
        printf("Stack 1 is Underflow");
        return;
    }
    top1 -= 1;
    return ;
}

//PUSH POP SEGUNDA STACK:
void push2(int x){
    top2 += 1;
    stack2[top2] = x;
}
void pop2(){
    if(isEmpty2()){
        printf("Stack 2 is Underflow\n");
        return;
    }
    top2 -= 1;
    return;
}

int main(){
    
    printf("\n1. PUSH ELEMENT IN STACK 1\n2. POP ELEMENT IN STACK 1\n3.PUSH ELEMENT ON STACK 2\n4.POP ELEMENT ON STACK 2\n5.VIZUALIZE STACKS\n6.UNIFY AND QUIT\n");
    

    while (1)
    {
    printf("\nPlease enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1){
        int element;
        printf("\nWich one element you want push in stack 1?: ");
        scanf("%d", &element);
        push1(element);
    }

    if (choice == 2){

        pop1();
    }

    if(choice == 3){
        int elemen;
        printf("\nWich one element you want push in stack 2?: ");
        scanf("%d", &elemen);
        push2(elemen);
    }
    if (choice == 4){

        pop2();
    }
    
    if(choice == 5){
        if(top1 == - 1)
            printf("\nSTACK 1 is UNDERFLOW\n");
         else{
        printf("\nSTACK 1:\n");
        for(int i = top1; i != -1; i--)
        {
            printf("%d\n", stack1[i]);
        }
    }
        if(top2 == - 1)
            printf("\nSTACK 2 is UNDERFLOW\n");
        else{
        printf("\nSTACK 2:\n");
        for(int i = top2; i != -1; i--)
        {
            printf("%d\n", stack2[i]);
        }
    }
    }
    if (choice == 6){
        printf("Stack 1 + Stack 2 is:\n");
        int add_tops = top1 + top2+1;
        while(1)
        {
            if(top2== -1)
                break;

            push1(stack2[top2]);
            top2--;
        }
        while(1){
            if (add_tops == -1){
                return 0;
            }
            printf("%d\n", stack1[add_tops]);
            add_tops -= 1;   
        } 
        return 0;
    }
    }

    

    return 0; 
}
