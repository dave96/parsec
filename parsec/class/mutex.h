/*
 * Copyright (c) 2009-2025 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 */

#ifndef PARSEC_MUTEX_H_HAS_BEEN_INCLUDED
#define PARSEC_MUTEX_H_HAS_BEEN_INCLUDED

#include "parsec/parsec_config.h"

#include <unistd.h>
#include <pthread.h>

/**
 * @defgroup parsec_internal_classes_mutex Mutex
 * @ingroup parsec_internal_classes
 * @{
 *
 *  @brief Mutex between threads of a same node
 *
 *  @details This follows the implementation of pthread_mutex(3)
 *
 */


BEGIN_C_DECLS

#ifdef PARSEC_HAVE_NOSV
#include <nosv/compat.h>

typedef nosv_mutex_t parsec_mutex_t;
#define parsec_mutex_init nosv_mutex_init
#define parsec_mutex_lock nosv_mutex_lock
#define parsec_mutex_unlock nosv_mutex_unlock
#define parsec_mutex_destroy nosv_mutex_destroy
#define PARSEC_MUTEX_INITIALIZER NOSV_MUTEX_INITIALIZER

#else

//Note how we return a posix error code, not a parsec one.
typedef pthread_mutex_t parsec_mutex_t;
#define parsec_mutex_init pthread_mutex_init
#define parsec_mutex_lock pthread_mutex_lock
#define parsec_mutex_unlock pthread_mutex_unlock
#define parsec_mutex_destroy pthread_mutex_destroy
#define PARSEC_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER

#endif // PARSEC_HAS_NOSV

END_C_DECLS

/**
 * @}
 */

#endif  /* PARSEC_MUTEX_H_HAS_BEEN_INCLUDED */
