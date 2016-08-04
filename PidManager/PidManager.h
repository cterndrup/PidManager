//
//  PidManager.h
//  PidManager
//
//  Created by COLIN TERNDRUP on 8/2/16.
//  Copyright © 2016 COLIN TERNDRUP. All rights reserved.
//

#ifndef PidManager_h
#define PidManager_h

/* ---------------------- Includes ------------------------------------------ */
#include "Queue.h"

/* ---------------------- Macros and Defines -------------------------------- */

//
// Min and Max process ID numbers PidManager is
// responsible for
//
#define MIN_PID     300
#define MAX_PID     5000
#define NUM_PIDS    ((MAX_PID - MIN_PID) + 1)
#define INVALID_PID -1

/* ---------------------- Datatypes ----------------------------------------- */

/*!
 * Data structure representing pids
 */
struct PidManager
{
    // Queue containing available pids
    Queue availablePids;
    
    // number of available pids
    int numAvailablePids;
};

typedef struct PidManager PidManager;

/* ---------------------- Function Prototypes ------------------------------- */

/*!
 * Creates and initializes a data structure for representing pids
 */
int allocate_map(void);

/*!
 * Allocates and returns a pid
 */
int allocate_pid(void);

/*!
 * Releases a pid
 */
void release_pid(int pid);

#endif /* PidManager_h */
