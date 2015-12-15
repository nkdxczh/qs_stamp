/* =============================================================================
 *
 * thread.h
 *
 * =============================================================================
 *
 * Copyright (C) Stanford University, 2006.  All Rights Reserved.
 * Author: Chi Cao Minh
 *
 * =============================================================================
 *
 * For the license of bayes/sort.h and bayes/sort.c, please see the header
 * of the files.
 * 
 * ------------------------------------------------------------------------
 * 
 * For the license of kmeans, please see kmeans/LICENSE.kmeans
 * 
 * ------------------------------------------------------------------------
 * 
 * For the license of ssca2, please see ssca2/COPYRIGHT
 * 
 * ------------------------------------------------------------------------
 * 
 * For the license of lib/mt19937ar.c and lib/mt19937ar.h, please see the
 * header of the files.
 * 
 * ------------------------------------------------------------------------
 * 
 * For the license of lib/rbtree.h and lib/rbtree.c, please see
 * lib/LEGALNOTICE.rbtree and lib/LICENSE.rbtree
 * 
 * ------------------------------------------------------------------------
 * 
 * Unless otherwise noted, the following license applies to STAMP files:
 * 
 * Copyright (c) 2007, Stanford University
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 * 
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 * 
 *     * Neither the name of Stanford University nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY STANFORD UNIVERSITY ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL STANFORD UNIVERSITY BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * =============================================================================
 */


#ifndef THREAD_H
#define THREAD_H 1


#include <pthread.h>
#include <stdlib.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TABLE_ROW_INDEXES 31
#define TABLE_COLUMN_INDEXES 10
#define TABLE_ROW_STEP 0.1
#define TABLE_COLUMN_STEP 0.01

extern const float GAUSSIAN_TABLE[31][10];


#define THREAD_T                            pthread_t
#define THREAD_ATTR_T                       pthread_attr_t

#define THREAD_ATTR_INIT(attr)              pthread_attr_init(&attr)
#define THREAD_JOIN(tid)                    pthread_join(tid, (void**)NULL)
#define THREAD_CREATE(tid, attr, fn, arg)   pthread_create(&(tid), \
                                                           &(attr), \
                                                           (void* (*)(void*))(fn), \
                                                           (void*)(arg))

#define THREAD_LOCAL_T                      pthread_key_t
#define THREAD_LOCAL_INIT(key)              pthread_key_create(&key, NULL)
#define THREAD_LOCAL_SET(key, val)          pthread_setspecific(key, (void*)(val))
#define THREAD_LOCAL_GET(key)               pthread_getspecific(key)

#define THREAD_MUTEX_T                      pthread_mutex_t
#define THREAD_MUTEX_INIT(lock)             pthread_mutex_init(&(lock), NULL)
#define THREAD_MUTEX_LOCK(lock)             pthread_mutex_lock(&(lock))
#define THREAD_MUTEX_UNLOCK(lock)           pthread_mutex_unlock(&(lock))

#define THREAD_COND_T                       pthread_cond_t
#define THREAD_COND_INIT(cond)              pthread_cond_init(&(cond), NULL)
#define THREAD_COND_SIGNAL(cond)            pthread_cond_signal(&(cond))
#define THREAD_COND_BROADCAST(cond)         pthread_cond_broadcast(&(cond))
#define THREAD_COND_WAIT(cond, lock)        pthread_cond_wait(&(cond), &(lock))

#ifdef SIMULATOR
#  define THREAD_BARRIER_T                  pthread_barrier_t
#  define THREAD_BARRIER_ALLOC(N)           ((THREAD_BARRIER_T*)malloc(sizeof(THREAD_BARRIER_T)))
#  define THREAD_BARRIER_INIT(bar, N)       pthread_barrier_init(bar, 0, N)
#  define THREAD_BARRIER(bar, tid)          pthread_barrier_wait(bar)
#  define THREAD_BARRIER_FREE(bar)          free(bar)
#else /* !SIMULATOR */

#ifdef LOG_BARRIER
#  define THREAD_BARRIER_T                  thread_barrier_t
#  define THREAD_BARRIER_ALLOC(N)           thread_barrier_alloc(N)
#  define THREAD_BARRIER_INIT(bar, N)       thread_barrier_init(bar)
#  define THREAD_BARRIER(bar, tid)          thread_barrier(bar, tid)
#  define THREAD_BARRIER_FREE(bar)          thread_barrier_free(bar)
#else
#  define THREAD_BARRIER_T                  barrier_t
#  define THREAD_BARRIER_ALLOC(N)           barrier_alloc()
#  define THREAD_BARRIER_INIT(bar, N)       barrier_init(bar, N)
#  define THREAD_BARRIER(bar, tid)          barrier_cross(bar)
#  define THREAD_BARRIER_FREE(bar)          barrier_free(bar)
#endif /* !LOG_BARRIER */
#endif /* !SIMULATOR */

# define NO_TASK 20000
# define NO_LOCK 10000
# define CONST_A 2.71
# define CONST_R 2
# define STDEV_SCALE 0.8
# define RBT_ID 1
# define GENOME_ID 2
# define INTRUDER_ID 3
# define KMEANS_ID 4
# define LABYRINTH_ID 5
# define SSCA2_ID 6
# define VACATION_ID 7
# define YADA_ID 8
# define PADDEDSIZE 32

// # define CPU_LOCKS 4

#include "../htm.h"

typedef struct thread_metadata {
    unsigned short profile;
    unsigned short cpuId;/*0-7*/
    unsigned short cpuLockId;/*0-3*/

    unsigned short neighbourghSample;

    unsigned long abortStats[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
    unsigned long commitStats[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
    unsigned long totalExecutions[NUMBER_ATOMIC_BLOCKS];

    unsigned long totalAborts;
    unsigned long abortedTxs;
    unsigned long totalAtomicBlocks;
    unsigned long totalTSXTxs;
    unsigned long totalAuxLockTxs;
    unsigned long totalSGLTxs;
    unsigned long totalRetries;
    unsigned long totalTSXTxsSuccessfulAcquiredLocks[NUMBER_ATOMIC_BLOCKS + 1]; // index is the number of locks
    unsigned long totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[NUMBER_ATOMIC_BLOCKS + 1]; // index is the number of locks
    unsigned long totalTSXTxsAcquiredLock[NUMBER_ATOMIC_BLOCKS];

    unsigned long conflictAbort;
    unsigned long capacityAbort;
    unsigned long retryAbort; // but not conflict nor capacity
    unsigned long otherAbort;
    unsigned long lockAbort;

    unsigned long cyclesWaiting;

    unsigned long updateStatsCounter;
    unsigned long periodController;
    unsigned long lastConflictTotalAborts;
    unsigned long lastTotalCommits;
    char suffixPadding[CACHE_LINE_SIZE];
} __attribute__((aligned(CACHE_LINE_SIZE))) thread_metadata_t;

typedef struct spin_lock {
    volatile int lock;
    char suffixPadding[CACHE_LINE_SIZE];
} __attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t;

typedef struct global_snapshot {
    unsigned short task_id;
    char suffixPadding[CACHE_LINE_SIZE];
} __attribute__((aligned(CACHE_LINE_SIZE))) global_snapshot_t ;

# define VALUE_SHIFT 0.005

typedef struct global_optimizer {
    unsigned long last_total_txns;
    unsigned long last_cycles;

    float alpha_value;
    float min_value;
    float* value_ptr;
    float current_shift;

    double measurement_0;
    double measurement_1;
    double measurement_2;

    double best_ever_measurement;
    float best_ever_alpha;
    float best_ever_min;
} __attribute__((aligned(CACHE_LINE_SIZE))) global_optimizer_t;

extern __attribute__((aligned(CACHE_LINE_SIZE))) global_snapshot_t globalSnapshot[NUMBER_THREADS];
extern __attribute__((aligned(CACHE_LINE_SIZE))) global_optimizer_t globalOptimizer;
extern __attribute__((aligned(CACHE_LINE_SIZE))) unsigned long totalAbortStats[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
extern __attribute__((aligned(CACHE_LINE_SIZE))) unsigned long totalCommitStats[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
extern __attribute__((aligned(CACHE_LINE_SIZE))) unsigned long previousAborts;
extern __attribute__((aligned(CACHE_LINE_SIZE))) unsigned long previousCommits;
extern __attribute__((aligned(CACHE_LINE_SIZE))) double conjAbortProb[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
extern __attribute__((aligned(CACHE_LINE_SIZE))) short globalLocksToAcquire[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
extern int benchmarkId;
extern int MAX_ATTEMPTS;
extern int APRIORI_ATTEMPTS;

extern __attribute__((aligned(CACHE_LINE_SIZE))) thread_metadata_t statistics[NUMBER_THREADS];
extern __attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t paddedSpinLocks[NUMBER_ATOMIC_BLOCKS];
extern __attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t paddedCpuLocks[CPU_LOCKS];

extern __attribute__((aligned(CACHE_LINE_SIZE))) __thread unsigned short myThreadId;

typedef struct thread_args {
    volatile unsigned long commits;
    volatile unsigned long aborts;
    long threadId;
} thread_args_t;

extern __attribute__((aligned(CACHE_LINE_SIZE))) thread_args_t* threadArgsArr;

typedef struct padded_scalar {
    volatile unsigned long counter;
    char suffixPadding[CACHE_LINE_SIZE];
} __attribute__((aligned(CACHE_LINE_SIZE))) padded_scalar_t;

extern __attribute__((aligned(CACHE_LINE_SIZE))) pthread_mutex_t htm_single_global_lock;

extern __attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t aux_lock;


typedef struct barrier {
    pthread_cond_t complete;
    pthread_mutex_t mutex;
    int count;
    int crossing;
} barrier_t;

unsigned long long tick();

void global_init();

void init_thread(int threadId);

barrier_t *barrier_alloc();

void barrier_free(barrier_t *b);

void barrier_init(barrier_t *b, int n);

void barrier_cross(barrier_t *b);


/* =============================================================================
 * thread_startup
 * -- Create pool of secondary threads
 * -- numThread is total number of threads (primary + secondary)
 * =============================================================================
 */
void
thread_startup (long numThread);


/* =============================================================================
 * thread_start
 * -- Make primary and secondary threads execute work
 * -- Should only be called by primary thread
 * -- funcPtr takes one arguments: argPtr
 * =============================================================================
 */
void
thread_start (void (*funcPtr)(void*), void* argPtr);


/* =============================================================================
 * thread_shutdown
 * -- Primary thread kills pool of secondary threads
 * =============================================================================
 */
void
thread_shutdown ();


/* =============================================================================
 * thread_barrier_wait
 * -- Call after thread_start() to synchronize threads inside parallel region
 * =============================================================================
 */
void
thread_barrier_wait();

/* =============================================================================
 * thread_getId
 * -- Call after thread_start() to get thread ID inside parallel region
 * =============================================================================
 */
long
thread_getId();


/* =============================================================================
 * thread_getNumThread
 * -- Call after thread_start() to get number of threads inside parallel region
 * =============================================================================
 */
long
thread_getNumThread();



#ifdef __cplusplus
}
#endif


#endif /* THREAD_H */


/* =============================================================================
 *
 * End of thread.h
 *
 * =============================================================================
 */
