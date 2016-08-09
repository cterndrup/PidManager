//
//  Queue.h
//  PidManager
//
//  Created by COLIN TERNDRUP on 8/3/16.
//  Copyright © 2016 COLIN TERNDRUP. All rights reserved.
//

#ifndef Queue_h
#define Queue_h

/* ----------------------- Forward Definitions ------------------------------ */
typedef struct QNode QNode;
typedef struct Queue Queue;

/* ----------------------- Typedefs ----------------------------------------- */

/*!
 * Constructs a queue
 *
 * @param[in] fifo  a pointer to a FIFO queue
 *
 * @return -1 if there is a failure during queue construction;
 *          0 if construction is successful
 */
typedef int    Construct(Queue *fifo);

/*!
 * Destructs a queue
 *
 * @param[in] back  a pointer to a FIFO queue
 * 
 * @return -1 if there is a failure during queue construction;
 *          0 if destruction is successful
 */
typedef void   Destruct(Queue *queue);

/*!
 * Enqueues a node to the back of the queue
 *
 * @param[in] fifo  a pointer to a fifo queue
 * @param[in] n     an integer to be added to the end of the queue
 *
 * @return -1 if there is enqueue fails;
 *          0 if enqueue is successful
 */
typedef int    Enqueue(Queue *fifo, int n);

/*!
 * Dequeues a node from the front of the queue and returns it
 *
 * @param[in] fifo  a pointer to a fifo queue
 *
 * @return the integer at the front of the queue;
 *         -1 if dequeue fails
 */
typedef int     Dequeue(Queue *fifo);

/*!
 * Similar to Dequeue, but does not remove from the front of the queue
 *
 * @param[in] fifo  a pointer to a fifo queue
 *
 * @return the integer at the front of the queue;
 *         -1 if peek fails
 */
typedef int     Peek(Queue *fifo);

/* ----------------------- Datatypes ---------------------------------------- */

/*!
 * FIFO queue node
 */
struct QNode
{
    // Integer value of the node
    int val;
    
    // Pointer to the next node
    QNode *next;
};

/*!
 * FIFO queue data structure
 */
struct Queue
{
    // The actual queue
    QNode *queue;
    
    // Pointer to the back of the queue
    QNode *back;
    
    // Number of nodes in the queue
    unsigned int numNodes;
    
    // Queue methods
    Enqueue *enqueue;
    Dequeue *dequeue;
    Peek    *peek;
};

/* ----------------------- Function Prototypes ------------------------------ */
Construct   construct;
Destruct    destruct;
Enqueue     enqueue;
Dequeue     dequeue;
Peek        peek;

#endif /* Queue_h */
