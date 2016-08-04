//
//  main.c
//  PidManager
//
//  Created by COLIN TERNDRUP on 8/2/16.
//  Copyright © 2016 COLIN TERNDRUP. All rights reserved.
//

#include <stdio.h>
#include "PidManager.h"

// Global variable representing the PidManager
PidManager pidManager;

int main(int argc, const char * argv[]) {
    int status = 0;
    
    status = allocate_map();
    if (status == -1)
    {
        printf("Failed to allocate pid manager.\n");
        goto main_exit;
    }
    
    status = allocate_pid();
    if (status == -1)
    {
        printf("Failed to allocate pid.\n");
        goto main_exit;
    }
    
    printf("pid allocated = %d\n", status);
    
    release_pid(status);
    
main_exit:
    return 0;
}
