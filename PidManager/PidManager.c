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
    
    // Initialize the two queues
    status = construct(&pidManager.availablePids);
    if (status != 0)
    {
        return -1;
    }
    
    // Add all available pids to the "available" queue
    int i;
    for (i = MIN_PID; i <= MAX_PID; i++)
    {
        pidManager.availablePids.enqueue(&pidManager.availablePids, i);
    }
    
    // Initialize numAvailablePids
    pidManager.numAvailablePids = NUM_PIDS;
    
    return 1;
}

/*!
 * Allocates and returns a pid
 *
 * @return -1 if unsuccessful
 * @return  valid pid if successful
 */
int allocate_pid(void)
{
    // Ensure a valid pid is available, otherwise exit early
    if (pidManager.numAvailablePids == 0)
        return -1;
    
    // Dequeue front of available queue and return it
    int pid = pidManager.availablePids.dequeue(&pidManager.availablePids);
    if (pid != -1)
        pidManager.numAvailablePids--;
    
    return pid;
}

/*!
 * Releases a pid
 */
void release_pid(int pid)
{
    // Ensure pid argument is valid
    if (pid < MIN_PID || pid > MAX_PID)
        return;
    
    // Place pid onto the queue
    int status =
        pidManager.availablePids.enqueue(&pidManager.availablePids, pid);
    
    if (status != -1)
        pidManager.numAvailablePids--;
    
    return;
}