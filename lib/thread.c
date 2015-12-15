/* =============================================================================
 *
 * thread.c
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


#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include <assert.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include "thread.h"
#include "types.h"

static THREAD_LOCAL_T    global_threadId;
static long              global_numThread       = 1;
static THREAD_BARRIER_T* global_barrierPtr      = NULL;
static long*             global_threadIds       = NULL;
static THREAD_ATTR_T     global_threadAttr;
static THREAD_T*         global_threads         = NULL;
static void            (*global_funcPtr)(void*) = NULL;
static void*             global_argPtr          = NULL;
static volatile bool_t   global_doShutdown      = FALSE;

const float GAUSSIAN_TABLE[31][10] = {
{0.0000,0.0040,0.0080,0.0120,0.0160,0.0199,0.0239,0.0279,0.0319,0.0359},
{0.0398,0.0438,0.0478,0.0517,0.0557,0.0596,0.0636,0.0675,0.0714,0.0753},
{0.0793,0.0832,0.0871,0.0910,0.0948,0.0987,0.1026,0.1064,0.1103,0.1141},
{0.1179,0.1217,0.1255,0.1293,0.1331,0.1368,0.1406,0.1443,0.1480,0.1517},
{0.1554,0.1591,0.1628,0.1664,0.1700,0.1736,0.1772,0.1808,0.1844,0.1879},
{0.1915,0.1950,0.1985,0.2019,0.2054,0.2088,0.2123,0.2157,0.2190,0.2224},
{0.2257,0.2291,0.2324,0.2357,0.2389,0.2422,0.2454,0.2486,0.2517,0.2549},
{0.2580,0.2611,0.2642,0.2673,0.2704,0.2734,0.2764,0.2794,0.2823,0.2852},
{0.2881,0.2910,0.2939,0.2967,0.2995,0.3023,0.3051,0.3078,0.3106,0.3133},
{0.3159,0.3186,0.3212,0.3238,0.3264,0.3289,0.3315,0.3340,0.3365,0.3389},
{0.3413,0.3438,0.3461,0.3485,0.3508,0.3531,0.3554,0.3577,0.3599,0.3621},
{0.3643,0.3665,0.3686,0.3708,0.3729,0.3749,0.3770,0.3790,0.3810,0.3830},
{0.3849,0.3869,0.3888,0.3907,0.3925,0.3944,0.3962,0.3980,0.3997,0.4015},
{0.4032,0.4049,0.4066,0.4082,0.4099,0.4115,0.4131,0.4147,0.4162,0.4177},
{0.4192,0.4207,0.4222,0.4236,0.4251,0.4265,0.4279,0.4292,0.4306,0.4319},
{0.4332,0.4345,0.4357,0.4370,0.4382,0.4394,0.4406,0.4418,0.4429,0.4441},
{0.4452,0.4463,0.4474,0.4484,0.4495,0.4505,0.4515,0.4525,0.4535,0.4545},
{0.4554,0.4564,0.4573,0.4582,0.4591,0.4599,0.4608,0.4616,0.4625,0.4633},
{0.4641,0.4649,0.4656,0.4664,0.4671,0.4678,0.4686,0.4693,0.4699,0.4706},
{0.4713,0.4719,0.4726,0.4732,0.4738,0.4744,0.4750,0.4756,0.4761,0.4767},
{0.4772,0.4778,0.4783,0.4788,0.4793,0.4798,0.4803,0.4808,0.4812,0.4817},
{0.4821,0.4826,0.4830,0.4834,0.4838,0.4842,0.4846,0.4850,0.4854,0.4857},
{0.4861,0.4864,0.4868,0.4871,0.4875,0.4878,0.4881,0.4884,0.4887,0.4890},
{0.4893,0.4896,0.4898,0.4901,0.4904,0.4906,0.4909,0.4911,0.4913,0.4916},
{0.4918,0.4920,0.4922,0.4925,0.4927,0.4929,0.4931,0.4932,0.4934,0.4936},
{0.4938,0.4940,0.4941,0.4943,0.4945,0.4946,0.4948,0.4949,0.4951,0.4952},
{0.4953,0.4955,0.4956,0.4957,0.4959,0.4960,0.4961,0.4962,0.4963,0.4964},
{0.4965,0.4966,0.4967,0.4968,0.4969,0.4970,0.4971,0.4972,0.4973,0.4974},
{0.4974,0.4975,0.4976,0.4977,0.4977,0.4978,0.4979,0.4979,0.4980,0.4981},
{0.4981,0.4982,0.4982,0.4983,0.4984,0.4984,0.4985,0.4985,0.4986,0.4986},
{0.4987,0.4987,0.4987,0.4988,0.4988,0.4989,0.4989,0.4989,0.4990,0.4990},
};

__attribute__((aligned(CACHE_LINE_SIZE))) thread_metadata_t statistics[NUMBER_THREADS];
__attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t paddedSpinLocks[NUMBER_ATOMIC_BLOCKS];
__attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t paddedCpuLocks[CPU_LOCKS];

__attribute__((aligned(CACHE_LINE_SIZE))) global_snapshot_t globalSnapshot[NUMBER_THREADS];
__attribute__((aligned(CACHE_LINE_SIZE))) global_optimizer_t globalOptimizer;
__attribute__((aligned(CACHE_LINE_SIZE))) unsigned long totalAbortStats[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
__attribute__((aligned(CACHE_LINE_SIZE))) unsigned long totalCommitStats[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
__attribute__((aligned(CACHE_LINE_SIZE))) unsigned long previousAborts;
__attribute__((aligned(CACHE_LINE_SIZE))) unsigned long previousCommits;
__attribute__((aligned(CACHE_LINE_SIZE))) double conjAbortProb[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
__attribute__((aligned(CACHE_LINE_SIZE))) short globalLocksToAcquire[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS];
int benchmarkId;
int MAX_ATTEMPTS;
int APRIORI_ATTEMPTS;

thread_args_t* threadArgsArr;

__attribute__((aligned(CACHE_LINE_SIZE))) pthread_mutex_t htm_single_global_lock;

__attribute__((aligned(CACHE_LINE_SIZE))) spin_lock_t aux_lock;

__thread unsigned short myThreadId;


#include "../htm.h"

void global_init() {
    int i;
    int k;
    int l,m,x;

    double uniformProb = 1.0 / (NUMBER_ATOMIC_BLOCKS + 0.0);
    for (i = 0; i < NUMBER_ATOMIC_BLOCKS; i++) {
        paddedSpinLocks[i].lock = 0;
        for (k = 0; k < NUMBER_ATOMIC_BLOCKS; k++) {
            globalLocksToAcquire[i][k] = NO_LOCK;
            conjAbortProb[i][k] = uniformProb;
        }
    }
    for (i = 0; i < CPU_LOCKS; i++) {
        paddedCpuLocks[i].lock = 0;
    }

    previousAborts = 0;
    previousCommits = 0;
    pthread_mutex_init(&htm_single_global_lock, NULL);

    aux_lock.lock = 0;

    for (i = 0; i < NUMBER_THREADS; i++) {
        statistics[i].profile = 0;
        statistics[i].lastConflictTotalAborts = 0;
        statistics[i].lastTotalCommits = 0;
        statistics[i].updateStatsCounter = 0;
        statistics[i].periodController = 10;
        statistics[i].cyclesWaiting = 0;
        for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) {
        statistics[i].totalExecutions[x] = 0;
        for (k = 0; k < NUMBER_ATOMIC_BLOCKS; k++) {
            statistics[i].abortStats[x][k] = 0;
            statistics[i].commitStats[x][k] = 0;
        }
        statistics[i].neighbourghSample = (i + 1) % NUMBER_THREADS;
    }

    }

    int t;
    for (t = 0; t < NUMBER_THREADS; t++) {
        statistics[t].totalAborts = 0;
        statistics[t].abortedTxs = 0;
        statistics[t].totalAtomicBlocks = 0;
        statistics[t].totalAuxLockTxs = 0;
        statistics[t].totalTSXTxs = 0;
        statistics[t].totalSGLTxs = 0;
        statistics[t].totalRetries = 0;
        for (k = 0; k < NUMBER_ATOMIC_BLOCKS + 1; k++) {
            statistics[t].totalTSXTxsSuccessfulAcquiredLocks[k] = 0;
            statistics[t].totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[k] = 0;
            if (k < NUMBER_ATOMIC_BLOCKS) {
                statistics[t].totalTSXTxsAcquiredLock[k] = 0;
            }
        }
        statistics[t].conflictAbort = 0;
        statistics[t].capacityAbort = 0;
        statistics[t].retryAbort = 0;
        statistics[t].otherAbort = 0;
        statistics[t].lockAbort = 0;
        statistics[t].updateStatsCounter = 0;
    }

    TICK(globalOptimizer.last_cycles);
    globalOptimizer.last_total_txns = 0;
    globalOptimizer.alpha_value = 0.78814; // STDEV_SCALE;
    globalOptimizer.min_value = 0.2 - (-(0.2 / (0.05 * NUMBER_ATOMIC_BLOCKS + 1)) + 0.2); // 0.3;
    globalOptimizer.value_ptr = &globalOptimizer.alpha_value;
    globalOptimizer.current_shift = -VALUE_SHIFT;
    globalOptimizer.measurement_0 = -1;
    globalOptimizer.measurement_1 = -1;
    globalOptimizer.measurement_2 = -1;
    globalOptimizer.best_ever_measurement = 0;
    globalOptimizer.best_ever_alpha = globalOptimizer.alpha_value;
    globalOptimizer.best_ever_min = globalOptimizer.min_value;
}

void init_thread(int threadId) {
    myThreadId = threadId;
    THREAD_LOCAL_SET(global_threadId, (long)threadId);

    thread_metadata_t* myStats = &(statistics[myThreadId]);
    myStats->cpuId = sched_getcpu();
    myStats->cpuLockId = myStats->cpuId % CPU_LOCKS;
}

/* =============================================================================
 * threadWait
 * -- Synchronizes all threads to start/stop parallel section
 * =============================================================================
 */
static void
threadWait (void* argPtr)
{
    thread_args_t* args = (thread_args_t*) argPtr;
    long threadId = args->threadId;

    BIND_THREAD(threadId);

    init_thread(threadId);


    while (1) {
        THREAD_BARRIER(global_barrierPtr, threadId); /* wait for start parallel */
        if (global_doShutdown) {
            break;
        }
        global_funcPtr(global_argPtr);
        THREAD_BARRIER(global_barrierPtr, threadId); /* wait for end parallel */
        if (threadId == 0) {
            break;
        }
    }
}

/* =============================================================================
 * thread_startup
 * -- Create pool of secondary threads
 * -- numThread is total number of threads (primary + secondaries)
 * =============================================================================
 */
void
thread_startup (long numThread)
{
	int i;

	global_init();

    global_numThread = numThread;
    global_doShutdown = FALSE;

    /* Set up barrier */
    assert(global_barrierPtr == NULL);
    global_barrierPtr = THREAD_BARRIER_ALLOC(numThread);
    assert(global_barrierPtr);
    THREAD_BARRIER_INIT(global_barrierPtr, numThread);

    /* Set up ids */
    THREAD_LOCAL_INIT(global_threadId);
    assert(global_threadIds == NULL);
    global_threadIds = (long*)malloc(numThread * sizeof(long));
    assert(global_threadIds);
    for (i = 0; i < numThread; i++) {
        global_threadIds[i] = i;
    }

    /* Set up thread list */
    assert(global_threads == NULL);
    global_threads = (THREAD_T*)malloc(numThread * sizeof(THREAD_T));
    assert(global_threads);

    threadArgsArr = (thread_args_t*) malloc(numThread * sizeof(thread_args_t));
    threadArgsArr[0].aborts = 0;
    threadArgsArr[0].commits = 0;
    threadArgsArr[0].threadId = global_threadIds[0];

    /* Set up pool */
    THREAD_ATTR_INIT(global_threadAttr);
    for (i = 1; i < numThread; i++) {
        threadArgsArr[i].aborts = 0;
        threadArgsArr[i].commits = 0;
        threadArgsArr[i].threadId = global_threadIds[i];
        THREAD_CREATE(global_threads[i],
                      global_threadAttr,
                      &threadWait,
                      &(threadArgsArr[i]));
    }
}

void
thread_start (void (*funcPtr)(void*), void* argPtr)
{
    global_funcPtr = funcPtr;
    global_argPtr = argPtr;

    threadWait((void*)&(threadArgsArr[0]));
}


void
thread_shutdown ()
{
    /* Make secondary threads exit wait() */
    global_doShutdown = TRUE;
    THREAD_BARRIER(global_barrierPtr, 0);

    long numThread = global_numThread;

    long i;
    for (i = 1; i < numThread; i++) {
        THREAD_JOIN(global_threads[i]);
    }

    THREAD_BARRIER_FREE(global_barrierPtr);
    global_barrierPtr = NULL;

    free(global_threadIds);
    global_threadIds = NULL;

    free(global_threads);
    global_threads = NULL;

    global_numThread = 1;
}

barrier_t *barrier_alloc() {
    return (barrier_t *)malloc(sizeof(barrier_t));
}

void barrier_free(barrier_t *b) {
    free(b);
}

void barrier_init(barrier_t *b, int n) {
    pthread_cond_init(&b->complete, NULL);
    pthread_mutex_init(&b->mutex, NULL);
    b->count = n;
    b->crossing = 0;
}

void barrier_cross(barrier_t *b) {
    pthread_mutex_lock(&b->mutex);
    /* One more thread through */
    b->crossing++;
    /* If not all here, wait */
    if (b->crossing < b->count) {
        pthread_cond_wait(&b->complete, &b->mutex);
    } else {
        /* Reset for next time */
        b->crossing = 0;
        pthread_cond_broadcast(&b->complete);
    }
    pthread_mutex_unlock(&b->mutex);
}

void
thread_barrier_wait()
{
    long threadId = thread_getId();
    THREAD_BARRIER(global_barrierPtr, threadId);
}

long
thread_getId()
{
    return (long)THREAD_LOCAL_GET(global_threadId);
}

long
thread_getNumThread()
{
    return global_numThread;
}
