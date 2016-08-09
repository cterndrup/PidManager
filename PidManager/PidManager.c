//
//  PidManager.c
//  PidManager
//
//  Created by COLIN TERNDRUP on 8/2/16.
//  Copyright © 2016 COLIN TERNDRUP. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "PidManager.h"

/* ------------------------- External Definitions --------------------------- */

/*!
 * External defintion of global variable in main.c
 */
extern PidManager pidManager;

/* ------------------------- Function Definitions --------------------------- */

/*!
 * Creates and initializes a data structure for representing pids
 *
 * @return -1 if unsuccessful
 * @return  0 if successful
 */
int allocate_map(void)
{
    int status = 0;
    int i;
    
    // Initialize the two queues
    status = construct(&pidManager.availablePids);
    if (status != 0)
    {
        return -1;
    }
    
    // Add all available pids to the "available" queue
    for (i = MIN_PID; i <= MAX_PID; i++)
    {
        pidManager.availablePids.enqueue(&pidManager.availablePids, i);
    }
    
    // Initialize numAvailablePids
    pidManager.numAvailablePids = NUM_PIDS;
    
    // Initialize the PidManager lock
    status = pthread_mutex_init(&pidManager.lock, NULL);
    if (status != 0)
        status = -1;
    
    return status;
}

/*!
 * Destroys data structure constructed in @ref allocate_map()
 *
 * @return -1 if unsuccessful
 * @return 0 if successful
 */
int destroy_map(void)
{
    int status;
    
    // Deallocate queue if not already NULL
    if (pidManager.availablePids.queue != NULL)
        destruct(&pidManager.availablePids);
    
    // Destroy the PidManager lock
    status = pthread_mutex_destroy(&pidManager.lock);
    if (status != 0)
        status = -1;
    return status;
}

/*!
 * Allocates and returns a pid
 *
 * @param[out] pid  pointer to a pid populated by the function
 *
 * @return -1 if unsuccessful
 * @return  valid pid if successful
 */
void allocate_pid(int *pid)
{
    int status;
    
    // Acquire the lock for allocation
    status = pthread_mutex_lock(&pidManager.lock);
    if (status != 0)
    {
        *pid = status;
        return;
    }
    
    // Ensure a valid pid is available, otherwise exit early
    if (pidManager.numAvailablePids == 0)
    {
        *pid = -1;
        return;
    }
    
    // Dequeue front of available queue and return it
    *pid = pidManager.availablePids.dequeue(&pidManager.availablePids);
    if (*pid != -1)
        pidManager.numAvailablePids--;
    
    // Release the lock
    status = pthread_mutex_unlock(&pidManager.lock);
    if (status != 0) {
        *pid = status;
    }
    
    return;
}

/*!
 * Releases a pid
 *
 * @param[in] pid   Process ID to be released
 */
void release_pid(int pid)
{
    int status;
    
    // Ensure pid argument is valid
    if (pid < MIN_PID || pid > MAX_PID)
        return;
    
    // Acquire the lock to release pid
    status = pthread_mutex_lock(&pidManager.lock);
    if (status != 0)
        return;
    
    // Place pid onto the queue
    status = pidManager.availablePids.enqueue(&pidManager.availablePids, pid);
    
    if (status != -1)
        pidManager.numAvailablePids--;
    
    // Release the lock
    status = pthread_mutex_unlock(&pidManager.lock);
    
    return;
}
