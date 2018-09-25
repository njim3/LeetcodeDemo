//
//  stack.h
//  CStackDemo
//
//  Created by njim3 on 2018/9/20.
//  Copyright © 2018 njim3. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdlib.h>
#include <malloc/malloc.h>
#include <stdbool.h>

#define SIZE        1000
#define INCREMENT   100

typedef struct Stack {
    int* base;
    
    int top;
    int size;
} Stack;

Stack* createStack(void);
Stack* createStackWithArray(int* arr, int size);
void destroyStack(Stack* stack);
bool extendStack(Stack* stack);
void pushStack(Stack* stack, int data);
int popStack(Stack* stack);
bool isStackEmpty(Stack* stack);
int sizeOfStack(Stack* stack);
int lengthOfStack(Stack* stack);

void traverseStack(Stack* stack);

#endif /* stack_h */
