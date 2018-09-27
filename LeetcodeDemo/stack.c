//
//  Stack.c
//  CStackDemo
//
//  Created by njim3 on 2018/9/26.
//  Copyright © 2018 njim3. All rights reserved.
//

#include "Stack.h"
#include <malloc/malloc.h>
#include <stdlib.h>
#include <stdio.h>

Stack* CreateStack(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    
    if (!stack)
        return NULL;
    
    stack->base = (int*)malloc(sizeof(int) * SIZE);
    
    if (!stack->base)
        return NULL;
    
    stack->top = 0;
    stack->size = SIZE;
    
    return stack;
}

Stack* CreateStackWithArray(int* arr, int size) {
    if (size == 0)
        return NULL;
    
    Stack* stack = CreateStack();
    
    for (int i = 0; i < size; ++i) {
        PushStack(stack, arr[i]);
    }
    
    return stack;
}

void DestroyStack(Stack* stack) {
    free(stack->base);
    free(stack);
}

bool ExtendStack(Stack* stack) {
    int newSize = stack->size + INCREMENT;
    int* extendedBase = (int*)realloc(stack->base, sizeof(int) * newSize);
    
    if (!extendedBase)
        return false;
    
    stack->base = extendedBase;
    
    printf("Extended stack size from %d -> %d.\n", stack->size, newSize);
    
    stack->size = newSize;
    
    return true;
}

void PushStack(Stack* stack, int data) {
    if (stack->top >= stack->size) {
        if (!ExtendStack(stack))
            return ;
    }
    
    stack->base[stack->top++] = data;
}

int PopStack(Stack* stack) {
    if (stack->top == 0)
        return -1;
    
    return stack->base[--stack->top];
}

bool IsStackEmpty(Stack* stack) {
    return stack->top == 0;
}

int LengthOfStack(Stack* stack) {
    return stack->size;
}

void TraverseStack(Stack* stack) {
    if (stack->top == 0 || !stack)
        return ;
    
    printf("Traverse from bottom to top: \n");
    for (int i = 0; i < stack->top; ++i) {
        printf("%d ", stack->base[i]);
    }
    
    printf("\n");
}
