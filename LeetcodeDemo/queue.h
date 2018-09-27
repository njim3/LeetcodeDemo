//
//  Queue.h
//  CStackDemo
//
//  Created by njim3 on 2018/9/27.
//  Copyright © 2018 njim3. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

#include <stdbool.h>

typedef struct QNode {
    int data;
    
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front, * rear;
} Queue;

Queue* CreateQueue(void);
bool EnQueue(Queue* queue, int data);
bool DeQueue(Queue* queue, int* dataPtr);
void Destroy(Queue* queue);
void Traverse(Queue* queue);





#endif /* Queue_h */
