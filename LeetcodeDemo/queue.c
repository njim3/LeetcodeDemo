//
//  Queue.c
//  CStackDemo
//
//  Created by njim3 on 2018/9/27.
//  Copyright © 2018 njim3. All rights reserved.
//

#include "Queue.h"
#include <malloc/malloc.h>
#include <stdlib.h>
#include <stdio.h>

Queue* CreateQueue(void) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    
    if (!queue)
        return NULL;
    
    queue->front = queue->rear = NULL;
    
    return queue;
}

bool EnQueue(Queue* queue, int data) {
    if (!queue)
        return false;
    
    QNode* node = (QNode*)malloc(sizeof(QNode));
    
    node->data = data;
    node->next = NULL;
    
    if (!queue->front) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    
    return true;
}

bool DeQueue(Queue* queue, int* dataPtr) {
    if (!queue || !queue->front)
        return false;
    
    QNode* p = queue->front;
    
    queue->front = p->next;
    p->next = NULL;
    
    (* dataPtr) = p->data;
    free(p);
    
    if (!queue->front)
        queue->rear = NULL;
    
    return true;
}

void Destroy(Queue* queue) {
    if (!queue)
        return ;
    
    while (queue->front) {
        queue->rear = queue->front;
        queue->front = queue->front->next;
        
        free(queue->rear);
    }
    
    free(queue);
}

void Traverse(Queue* queue) {
    if (!queue)
        return ;
    
    QNode* p = queue->front;
    
    while (p) {
        printf("%d ", p->data);
        
        p = p->next;
    }
    
    putchar('\n');
}
