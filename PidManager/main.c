//
//  main.c
//  PidManager
//
//  Created by COLIN TERNDRUP on 8/2/16.
//  Copyright © 2016 COLIN TERNDRUP. All rights reserved.
//

/* ------------------------ System Includes --------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ------------------------ Application Includes ---------------------------- */
#include "PidManager.h"

/* ------------------------ Global Variables -------------------------------- */

// Number of threads to create
#define NUM_THREADS 16

// Global variable representing the PidManager
PidManager pidManager;

/* ------------------------ Function Prototypes ----------------------------- */

/*!
 * Called on creation of a new thread
 *
 * @param[in] args     void pointer to an unsigned integer representing the 
 *                     amount of time the calling thread should sleep
 *
 * @return NULL
 */
void* acquireAndReleasePid(void *args);

/* ------------------------ Main Function ----------------------------------- */

int main(int argc, const char * argv[]) {
    
    int i;
    int status;
    pthread_t tids[NUM_THREADS];
    unsigned int sleepTimes[NUM_THREADS];
    
    // Generate random times for each thread to sleep for
    for (i = 0; i < NUM_THREADS; i++)
    {
        sleepTimes[i] = rand();
    }
    
    // Allocate the PidManager
    status = allocate_map();
    if (status != 0)
        goto main_exit;
    
    //
    // Create a bunch of threads
    // Then for each thread:
    // 1). sleep for random amount of time
    // 2). acquire pid
    // 3). sleep for random amount of time
    // 4). release pid
    //
    for (i = 0; i < NUM_THREADS; i++)
    {
        status = pthread_create(&tids[i], NULL, acquireAndReleasePid,
                                (void *)&sleepTimes[i]);
        if (status != 0)
            goto main_exit;
    }
    
    // Main thread waits until specified thread has terminated
    for (i=0; i< NUM_THREADS; i++)
    {
        status = pthread_join(tids[i], NULL);
        if (status != 0)
            goto main_exit;
    }
    
main_exit:
    // destroy the PidManager
    status = destroy_map();
    return status;
}

/* ----------------------- Function Definitions ----------------------------- */

/*!
 * See function documentation above
 */
void* acquireAndReleasePid(void *args)
{
    // 1). sleep for random amount of time
    unsigned int sleepTime = *((unsigned int *)args);
    sleep(sleepTime);
    
    // 2). acquire pid
    int pid;
    allocate_pid(&pid);
    
    // 3). sleep for random amount of time
    sleep(sleepTime);
    
    // 4). release pid
    release_pid(pid);
    
    return NULL;
}
