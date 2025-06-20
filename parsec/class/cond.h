/*
 * Copyright (c) 2009-2025 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 */

#ifndef PARSEC_COND_H_HAS_BEEN_INCLUDED
#define PARSEC_COND_H_HAS_BEEN_INCLUDED

#include "parsec/parsec_config.h"

#include <unistd.h>
#include <pthread.h>

/**
 * @defgroup parsec_internal_classes_cond Condition variables
 * @ingroup parsec_internal_classes
 * @{
 *
 *  @brief Condition variables between threads of a same node
 *
 *  @details This follows the implementation of pthread_cond(3)
 *
 */


BEGIN_C_DECLS

#ifdef PARSEC_HAVE_NOSV
#include <nosv/compat.h>

typedef nosv_cond_t parsec_cond_t;
#define parsec_cond_init nosv_cond_init
#define parsec_cond_wait nosv_cond_wait
#define parsec_cond_signal nosv_cond_signal
#define parsec_cond_broadcast nosv_cond_broadcast
#define parsec_cond_destroy nosv_cond_destroy
#define PARSEC_COND_INITIALIZER NOSV_COND_INITIALIZER

#else

//Note how we return a posix error code, not a parsec one.
typedef pthread_cond_t parsec_cond_t;
#define parsec_cond_init pthread_cond_init
#define parsec_cond_wait pthread_cond_wait
#define parsec_cond_signal pthread_cond_signal
#define parsec_cond_broadcast pthread_cond_broadcast
#define parsec_cond_destroy pthread_cond_destroy
#define PARSEC_COND_INITIALIZER PTHREAD_COND_INITIALIZER

#endif // PARSEC_HAS_NOSV

END_C_DECLS

/**
 * @}
 */

#endif  /* PARSEC_COND_H_HAS_BEEN_INCLUDED */
