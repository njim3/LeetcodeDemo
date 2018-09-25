//
//  stack.c
//  CStackDemo
//
//  Created by njim3 on 2018/9/20.
//  Copyright © 2018 njim3. All rights reserved.
//

#include "stack.h"
#include <stdio.h>

Stack* createStack(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    
    if (!stack)
        return NULL;
    
    stack->base = (int*)malloc(sizeof(int) * SIZE);
    stack->top = 0;
    stack->size = SIZE;
    
    return stack;
}

Stack* createStackWithArray(int* arr, int size) {
    if (size == 0)
        return NULL;
    
    Stack* stack = createStack();
    
    for (int i = 0; i < size; ++i) {
        pushStack(stack, arr[i]);
    }
    
    return stack;
}

void destroyStack(Stack* stack) {
    free(stack->base);
    free(stack);
}

bool extendStack(Stack* stack) {
    int newSize = stack->size + INCREMENT;
    int* extendedBase = (int*)realloc(stack->base, sizeof(int) * newSize);
    
    if (!extendedBase)
        return false;
    
    stack->base = extendedBase;
    stack->size = newSize;
    
    return true;
}

void pushStack(Stack* stack, int data) {
    if (stack->top >= stack->size) {
        if (!extendStack(stack))
            return ;
    }
    
    stack->base[stack->top++] = data;
}

int popStack(Stack* stack) {
    if (stack->top == 0)
        return -1;
    
    return stack->base[--stack->top];
}

bool isStackEmpty(Stack* stack) {
    return stack->top == 0;
}

int sizeOfStack(Stack* stack) {
    return stack->size;
}

int lengthOfStack(Stack* stack) {
    return stack->top;
}

void traverseStack(Stack* stack) {
    if (stack->top == 0 || !stack)
        return ;
    
    printf("Traverse from Bottom to top: \n");
    for (int i = 0; i < stack->top; ++i) {
        printf("%d ", stack->base[i]);
    }
    
    printf("\n");
}



