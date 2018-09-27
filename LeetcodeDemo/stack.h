//
//  Stack.h
//  CStackDemo
//
//  Created by njim3 on 2018/9/26.
//  Copyright © 2018 njim3. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <stdbool.h>

#define SIZE            5
#define INCREMENT       3

typedef struct Stack {
    int* base;
    
    int top;
    int size;
} Stack;

Stack* CreateStack(void);
Stack* CreateStackWithArray(int* arr, int size);
void DestroyStack(Stack* stack);
bool ExtendStack(Stack* stack);
void PushStack(Stack* stack, int data);
int PopStack(Stack* stack);
bool IsStackEmpty(Stack* stack);
int LengthOfStack(Stack* stack);

void TraverseStack(Stack* stack);


#endif /* Stack_h */
