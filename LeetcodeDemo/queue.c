//
//  queue.c
//  CStackDemo
//
//  Created by njim3 on 2018/9/20.
//  Copyright © 2018 njim3. All rights reserved.
//

#include "queue.h"

void CreateQueue(LinkQueue* queue) {
    queue->front = queue->rear = NULL;
}

bool EnQueue(LinkQueue* queue, int data) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    
    if (!node)
        return false;
    
    node->data = data;
    node->next = NULL;
    
    if (queue->front == NULL) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear = node;
    }
    
    return true;
}

bool DeQueue(LinkQueue* queue, int* dataPtr) {
    if (queue->front == NULL)
        return NULL;
    
    QueueNode* p = queue->front->next, *q = queue->front;
    
    queue->front = p;
    q->next = NULL;
    
    (*dataPtr) = q->data;
    
    free(q);
    
    return true;
}

void Destroy(LinkQueue* queue) {
    while (queue->front) {
        queue->rear = queue->front->next;
        
        free(queue->front);
        queue->front = queue->rear;
    }
}

void Traverse(LinkQueue* queue) {
    QueueNode* p = queue->front;
    
    while(p) {
        printf("%d ", p->data);
        
        p = p->next;
    }
}
