//
//  queue.h
//  CStackDemo
//
//  Created by njim3 on 2018/9/20.
//  Copyright © 2018 njim3. All rights reserved.
//

#ifndef queue_h
#define queue_h
#include <malloc/malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct QueueNode {
    int data;
    
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    
    QueueNode* rear;
} LinkQueue;

void CreateQueue(LinkQueue* queue);
bool EnQueue(LinkQueue* queue, int data);
bool DeQueue(LinkQueue* queue, int* dataPtr);
void Destroy(LinkQueue* queue);
void Traverse(LinkQueue* queue);

#endif /* queue_h */
