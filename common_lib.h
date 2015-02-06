#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <pthread.h>

const bool OPEN_LOCK = true;

void request_mutex(pthread_mutex_t* p_mutex);
void release_mutex(pthread_mutex_t* p_mutex);

void request_mutex(pthread_mutex_t* p_mutex) {
    if (OPEN_LOCK ) {
        pthread_mutex_lock(p_mutex);
    }
}

void release_mutex(pthread_mutex_t* p_mutex) {
    if (OPEN_LOCK) {
        pthread_mutex_unlock(p_mutex);
    }
}

#endif
