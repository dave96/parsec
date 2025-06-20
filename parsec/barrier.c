/*
 * Copyright (c) 2009-2021 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 */

#include "parsec/parsec_config.h"
#include "parsec/class/barrier.h"
#include "parsec/class/cond.h"
#include "parsec/class/mutex.h"

#if PARSEC_IMPLEMENT_BARRIERS

int parsec_barrier_init(parsec_barrier_t* barrier, const void* attr, unsigned int count)
{
    int rc;

    if( 0 != (rc = parsec_mutex_init(&(barrier->mutex), attr)) ) {
        return rc; // Note how we return a posix error code, not a parsec one. This is mimicking pthreads API.
    }

    barrier->count      = count;
    barrier->curcount   = 0;
    barrier->generation = 0;
    if( 0 != (rc = parsec_cond_init(&(barrier->cond), NULL)) ) {
        parsec_mutex_destroy( &(barrier->mutex) );
        return rc;
    }
    return 0;
}

int parsec_barrier_wait(parsec_barrier_t* barrier)
{
    int generation;

    parsec_mutex_lock( &(barrier->mutex) );
    if( (barrier->curcount + 1) == barrier->count) {
        barrier->generation++;
        barrier->curcount = 0;
        parsec_cond_broadcast( &(barrier->cond) );
        parsec_mutex_unlock( &(barrier->mutex) );
        return 1;
    }
    barrier->curcount++;
    generation = barrier->generation;
    for(;;) {
        parsec_cond_wait( &(barrier->cond), &(barrier->mutex) );
        if( generation != barrier->generation ) {
            break;
        }
    }
    parsec_mutex_unlock( &(barrier->mutex) );
    return 0;
}

int parsec_barrier_destroy(parsec_barrier_t* barrier)
{
    parsec_mutex_destroy( &(barrier->mutex) );
    parsec_cond_destroy( &(barrier->cond) );
    barrier->count    = 0;
    barrier->curcount = 0;
    return 0;
}

#endif  /* !(defined(_POSIX_BARRIERS) && (_POSIX_BARRIERS - 20012L) >= 0) */
