//
//  Queue.c
//  PidManager
//
//  Created by COLIN TERNDRUP on 8/3/16.
//  Copyright © 2016 COLIN TERNDRUP. All rights reserved.
//

/* ----------------------- Includes ----------------------------------------- */
#include <stdlib.h>
#include "Queue.h"

/* ----------------------- Function Definitions ----------------------------- */

/*!
 * Constructs a queue
 */
int construct(Queue *fifo)
{
    // Sanity check the input pointer
    if (fifo == NULL)
        return -1;
    
    // Initialize the node count
    fifo->numNodes = 0;
    
    // Initialize Queue public methods
    fifo->enqueue = enqueue;
    fifo->dequeue = dequeue;
    fifo->peek    = peek;
    
    return 0;
}

/*!
 * Destructs a queue
 */
void destruct(Queue *fifo)
{
    QNode *q;
    
    // Sanity check the input pointer
    if (fifo == NULL)
        return;
    
    // Iterate through queue nodes and free them
    for (q = fifo->queue; q != NULL; q = q->next)
    {
        free(q);
    }
}

/*!
 * Enqueues a node to the back of the queue
 */
int enqueue(Queue *fifo, int n)
{
    QNode *node = NULL;
    
    // Sanity check the input pointer
    if (fifo == NULL)
        return -1;
    
    // Construct and initialize the new queue node
    node = (QNode *)malloc(sizeof(QNode));
    if (node == NULL)
        return -1;
    node->val = n;
    
    // Add the new node to the back of the FIFO
    if (fifo->numNodes == 0)
    {
        fifo->queue = node;
        fifo->back  = fifo->queue;
        node->next  = NULL;
    }
    else
    {
        fifo->back->next = node;
        fifo->back = node;
    }
    
    // Increment the node count
    fifo->numNodes++;
    
    return 0;
}

/*!
 * Dequeues a node from the front of the queue and return it
 */
int dequeue(Queue *fifo)
{
    int    n;
    QNode *front = NULL;
    
    // Sanity check the input pointer
    if (fifo == NULL)
        return -1;
    
    // Ensure the queue is not empty; if it is, return early
    if (fifo->numNodes == 0)
        return -1;
    
    //
    // Remove the node from the front of the queue, deconstruct it,
    // and return its value
    //
    front = fifo->queue;
    n = front->val;
    fifo->queue = front->next;
    front->next = NULL;
    free(front);
    
    // Decrement the node count
    fifo->numNodes--;
    
    return n;
}

/*!
 * Similar to Dequeue, but does not remove from the front of the queue
 */
int peek(Queue *fifo)
{
    // Sanity check the input pointer
    if (fifo == NULL)
        return -1;
    
    // Ensure the queue is not empty; if it is, return early
    if (fifo->numNodes == 0)
        return -1;
    
    return fifo->queue->val;
}