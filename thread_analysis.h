#ifndef THREAD_ANALYSIS_H
#define THREAD_ANALYSIS_H

#include <pthread.h> //for threading , link with lpthread
#include "global_data.h"

void *analysis_func(void*);

void *analysis_func(void*) {

    while (true) {
        if (client_set.size() < switch_num) {
            sleep(1);
            continue;
        }
        //already received data from all switches
        //start analysis the data
    }
}

#endif
