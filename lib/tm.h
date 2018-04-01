#ifndef TM_H
#define TM_H 1

#  include <stdio.h>

#  define MAIN(argc, argv)              int main (int argc, char** argv)
#  define MAIN_RETURN(val)              return val

#  define GOTO_SIM()                    /* nothing */
#  define GOTO_REAL()                   /* nothing */
#  define IS_IN_SIM()                   (0)

#  define SIM_GET_NUM_CPU(startTime)           

#  define TM_PRINTF                     printf
#  define TM_PRINT0                     printf
#  define TM_PRINT1                     printf
#  define TM_PRINT2                     printf
#  define TM_PRINT3                     printf

#  define P_MEMORY_STARTUP(numThread)   /* nothing */
#  define P_MEMORY_SHUTDOWN()           /* nothing */

#  include <assert.h>
#  include "memory.h"
#  include "thread.h"
#  include "types.h"
#  include "thread.h"
#  include <math.h>

#  include "../htm.h"

#  define TM_ARG                        /* nothing */
#  define TM_ARG_ALONE                  /* nothing */
#  define TM_ARGDECL                    /* nothing */
#  define TM_ARGDECL_ALONE              /* nothing */
#  define TM_CALLABLE                   /* nothing */

#define PRINT_ALL false

#  define TM_STARTUP(numThread, bId){ \
	if(PRINT_ALL)printf("Starting benchmark ID %d\n", bId); \
	benchmarkId = bId; \
	MAX_ATTEMPTS = TOTAL_ATTEMPTS; \
	APRIORI_ATTEMPTS = APRIORI_LOCK_ATTEMPTS; \
	if(PRINT_ALL)printf("AttemptsBeforeGlobalLock = %d\nAPrioriLockAttempts = %d\n",MAX_ATTEMPTS, APRIORI_ATTEMPTS); \
        TM_STARTUP_QS;\
   }

#  define TM_SHUTDOWN() TM_SHUTDOWN_QS

#  define TM_THREAD_ENTER()

#  define TM_THREAD_EXIT()

#  define TM_BEGIN_WAIVER()
#  define TM_END_WAIVER()

#  define P_MALLOC(size)                malloc(size)
#  define P_FREE(ptr)                   free(ptr)
#  define TM_MALLOC(size)               malloc(size)
#  define TM_FREE(ptr)                  free(ptr)

#  define SETUP_NUMBER_TASKS(n)
#  define SETUP_NUMBER_THREADS(n)

#  define PRINT_STATS() { \
     long totalAborts = 0;\
     long abortedTxs = 0; \
     long totalAtomicBlocks = 0; \
     long totalTSXTxs = 0; \
     long totalSGLTxs = 0; \
     long totalRetries = 0; \
     long totalAuxLockTxs = 0; \
     long totalTSXTxsSuccessfulAcquiredLocks[NUMBER_ATOMIC_BLOCKS + 1];  \
     long totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[NUMBER_ATOMIC_BLOCKS + 1]; \
     long totalTSXTxsAcquiredLock[NUMBER_ATOMIC_BLOCKS]; \
     long conflictAbort = 0; \
     long capacityAbort = 0; \
     long retryAbort = 0; \
     long otherAbort = 0; \
     long lockAbort = 0; \
     long updateStatsCounter = 0; \
     unsigned long cyclesWaiting = 0; \
     int t; \
     int k; \
     for (k = 0; k < NUMBER_ATOMIC_BLOCKS + 1; k++) { \
       totalTSXTxsSuccessfulAcquiredLocks[k] = 0; \
       totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[k] = 0; \
       if (k < NUMBER_ATOMIC_BLOCKS) { \
         totalTSXTxsAcquiredLock[k] = 0; \
       } \
     } \
     for (t = 0; t < NUMBER_THREADS; t++) { \
       totalAborts += statistics[t].totalAborts; \
       abortedTxs += statistics[t].abortedTxs; \
       totalAtomicBlocks += statistics[t].totalAtomicBlocks; \
       totalTSXTxs += statistics[t].totalTSXTxs; \
       totalSGLTxs += statistics[t].totalSGLTxs; \
       totalRetries += statistics[t].totalRetries; \
       for (k = 0; k < NUMBER_ATOMIC_BLOCKS + 1; k++) { \
         totalTSXTxsSuccessfulAcquiredLocks[k] += statistics[t].totalTSXTxsSuccessfulAcquiredLocks[k]; \
         totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[k] += statistics[t].totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[k]; \
         if (k < NUMBER_ATOMIC_BLOCKS) { \
           totalTSXTxsAcquiredLock[k] += statistics[t].totalTSXTxsAcquiredLock[k]; \
         } \
       } \
       totalAuxLockTxs += statistics[t].totalAuxLockTxs; \
       conflictAbort += statistics[t].conflictAbort; \
       capacityAbort += statistics[t].capacityAbort; \
       retryAbort += statistics[t].retryAbort; \
       otherAbort += statistics[t].otherAbort; \
       lockAbort += statistics[t].lockAbort; \
       updateStatsCounter += statistics[t].updateStatsCounter; \
       cyclesWaiting += statistics[t].cyclesWaiting; \
     } \
     if(PRINT_ALL){\
     printf("cyclesWaiting %lu\n", cyclesWaiting); \
     printf("totalAborts %ld\n", totalAborts); \
     printf("abortedTxs %ld\n", abortedTxs); \
     printf("totalAtomicBlocks %ld\n", totalAtomicBlocks); \
     printf("totalTSXTxs %ld\n", totalTSXTxs); \
     printf("totalAuxLockTxs %ld\n", totalAuxLockTxs); \
     printf("totalSGLTxs %ld\n", totalSGLTxs); \
     printf("totalRetries %ld\n", totalRetries); \
     printf("conflictAbort %ld\n", conflictAbort); \
     printf("capacityAbort %ld\n", capacityAbort); \
     printf("retryAbort %ld\n", retryAbort); \
     printf("otherAbort %ld\n", otherAbort); \
     printf("lockAbort %ld\n", lockAbort); \
     printf("updateStatsCounter %ld\n", statistics[0].updateStatsCounter); \
     printf("totalTSXTxsSuccessfulAcquiredLocks %d", NUMBER_ATOMIC_BLOCKS + 1); \
     for (k = 0; k < NUMBER_ATOMIC_BLOCKS + 1; k++) { \
       printf(" %ld", totalTSXTxsSuccessfulAcquiredLocks[k]); \
     } \
     printf("\n"); \
     printf("totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks %d", NUMBER_ATOMIC_BLOCKS + 1); \
     for (k = 0; k < NUMBER_ATOMIC_BLOCKS + 1; k++) { \
       printf(" %ld", totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[k]); \
     } \
     printf("\n"); \
     printf("totalTSXTxsAcquiredLock %d", NUMBER_ATOMIC_BLOCKS); \
     for (k = 0; k < NUMBER_ATOMIC_BLOCKS; k++) { \
       printf(" %ld", totalTSXTxsAcquiredLock[k]); \
     } \
     printf("\n"); \
     }\
     else{\
     float rate = (float)totalTSXTxs / totalAtomicBlocks;\
     printf("%f\n", rate);\
     printf("%ld\n", conflictAbort); \
     }\
     PRINT_SEER_STATISTICS; \
   }

#  define IS_LOCKED(lock)        *((volatile int*)(&lock)) != 0

#  define TASK_LOCKS 0

#  define AL_LOCK(idx)

#  define TM_BEGIN(b) { \
    int tx = 0; \
    TM_BEGIN_EXT(b,tx);

#  ifdef USE_CPU_LOCKS

#    define WAIT_FOR_CPU_LOCKS \
       while (!acquiredCpuLock && IS_LOCKED(paddedCpuLocks[myStats->cpuLockId].lock)) { \
         PAUSE_INSTR; \
       } \

#    define CHECK_ACQUIRE_CPU_LOCKS \
       if (capacity > 0 && tries <= APRIORI_ATTEMPTS && acquiredCpuLock == 0 && tries > 0) { \
         TM_ACQUIRE_CPU_LOCKS(b); \
         acquiredCpuLock = 1; \
       }  \

#    define CHECK_RELEASE_CPU_LOCKS \
       if (acquiredCpuLock) { \
         paddedCpuLocks[myStats->cpuLockId].lock = 0; \
       } \

#  else /*!USE_CPU_LOCKS*/

#    define WAIT_FOR_CPU_LOCKS
#    define CHECK_ACQUIRE_CPU_LOCKS
#    define CHECK_RELEASE_CPU_LOCKS

#  endif /*!USE_CPU_LOCKS*/


#  ifdef USE_TX_LOCKS

#    define WAIT_FOR_TX_LOCKS(b) \
       while (!acquiredLocks && IS_LOCKED(paddedSpinLocks[b].lock)) { \
         PAUSE_INSTR; \
       } \

#    define CHECK_ACQUIRE_TX_LOCKS(b) \
       if (tries <= APRIORI_ATTEMPTS && tries > 0 && acquiredLocks == 0) { \
       TM_ACQUIRE_LOCKS(b, number_of_locks); \
       acquiredLocks = 1; \
     } \

#    define CHECK_RELEASE_TX_LOCKS \
       if (acquiredLocks){ \
       TM_RELEASE_LOCKS(block_id); \
     } \

#  else /*!USE_TX_LOCKS*/

#    define WAIT_FOR_TX_LOCKS(b)
#    define CHECK_ACQUIRE_TX_LOCKS(b)
#    define CHECK_RELEASE_TX_LOCKS

#  endif /*!USE_TX_LOCKS*/


#  ifdef USE_GRADIENT_DESCENT

#    define CALL_GRADIENT_DESCENT GRADIENT_DESCENT()

#  else /*!USE_GRADIENT_DESCENT*/

#    define CALL_GRADIENT_DESCENT

#  endif /*!USE_GRADIENT_DESCENT*/


#  ifdef USE_SEER

#  define INIT_SEER_TX \
     unsigned short spinLocksAcquired[NUMBER_ATOMIC_BLOCKS] = { 0 }; \

#  define INIT_SEER_TX_SNAPSHOT  globalSnapshot[thread_id].task_id = block_id;

#  define CALL_UPDATE_LOCKS(print) UPDATE_LOCKS_TO_ACQUIRE(print)

#  define REGISTER_TM_CONFLICT(b) TM_CONFLICT(b)

#  define REGISTER_TM_COMMIT(b) TM_COMMIT(block_id)

#  define PRINT_SEER_STATISTICS \
     long matrix_aborts[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS]; \
     long matrix_commits[NUMBER_ATOMIC_BLOCKS][NUMBER_ATOMIC_BLOCKS]; \
     unsigned int x,y; \
     unsigned int threadId; \
     for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
       for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
         matrix_aborts[x][y] = 0; \
         matrix_commits[x][y] = 0; \
       } \
     } \
     for (t = 0; t < NUMBER_THREADS; t++) { \
       for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
         for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
           matrix_aborts[x][y] += statistics[t].abortStats[x][y]; \
           matrix_commits[x][y] += statistics[t].commitStats[x][y]; \
         } \
       } \
     } \
     printf("Commits:\n"); \
     for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
       for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
         printf("%ld\t", matrix_commits[x][y]); \
       } \
       printf("\n"); \
     } \
     printf("\n"); \
     printf("Aborts:\n"); \
     for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
       for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
         printf("%ld\t", matrix_aborts[x][y]); \
       } \
       printf("\n"); \
     } \
     printf("\n"); \
     CALL_UPDATE_LOCKS(1); \
     printf("Conjunctive Probs:\n"); \
     for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
       for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
         printf("%0.2lf ", conjAbortProb[x][y]); \
       } \
       printf("\n"); \
     } \
     printf("Locks: \n"); \
     for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
       for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
         printf("%d ", globalLocksToAcquire[x][y]); \
       } \
       printf("\n"); \
     } \

#  else /*!USE_SEER*/

#    define INIT_SEER_TX
#    define INIT_SEER_TX_SNAPSHOT
#    define CALL_UPDATE_LOCKS(print)
#    define REGISTER_TM_CONFLICT(b)
#    define REGISTER_TM_COMMIT(b)
#    define PRINT_SEER_STATISTICS

#  endif /*!USE_SEER*/

#  ifdef USE_HLE

#    define GET_MAX_ATTEMPTS 1

#  else

#    define GET_MAX_ATTEMPTS MAX_ATTEMPTS

#  endif


#  ifdef USE_SCM

#    define ACQUIRE_AUX_LOCK \
	if (tries == MAX_ATTEMPTS) { \
	    { \
        unsigned long start_tick, end_tick; \
        TICK(start_tick); \
	    while (__sync_val_compare_and_swap(&aux_lock.lock, 0, 1) == 1) { \
            PAUSE_INSTR; \
        } \
        TICK(end_tick); \
        myStats->cyclesWaiting += end_tick - start_tick; \
        } \
	} \

#    define RELEASE_AUX_LOCK if (tries != MAX_ATTEMPTS) { aux_lock.lock = 0; myStats->totalAuxLockTxs++; }

#  else /*!USE_SCM*/

#    define ACQUIRE_AUX_LOCK

#    define RELEASE_AUX_LOCK

#  endif /*!USE_SCM*/

#  ifdef USE_QS

#    include "qs_scheduler.h"

#    define TM_STARTUP_QS QS_init()

#    define TM_SHUTDOWN_QS QS_end()

#    define TM_INIT_QS(ptr) QS_SchBlock* sb = new QS_SchBlock(ptr)

#    define TM_COMMIT_QS QS_contention_manage_commit(*sb)

#    define TM_ENQUEUE_QS QS_contention_manage_begin(*sb)

#  else /*!USE_QS*/

#    define TM_STARTUP_QS

#    define TM_SHUTDOWN_QS

#    define TM_INIT_QS(ptr)

#    define TM_COMMIT_QS

#    define TM_ENQUEUE_QS

#  endif /*!USE_QS*/

#  define TM_BEGIN_EXT(b,tx)  \
TM_INIT_QS(b);\
TM_ENQUEUE_QS;\
{\
        unsigned short acquiredLocks = 0; \
        unsigned short acquiredCpuLock = 0; \
        unsigned short thread_id = myThreadId; \
        thread_metadata_t* myStats = &(statistics[thread_id]); \
        int block_id = b; \
        INIT_SEER_TX; \
        INIT_SEER_TX_SNAPSHOT; \
        int tries = GET_MAX_ATTEMPTS; \
        int capacity = 0; \
        int number_of_locks = 0; \
        while (1) { \
            tx = 1; \
            if (IS_LOCKED(htm_single_global_lock)) { \
            	if (thread_id == 0) { \
                    myStats->updateStatsCounter++; \
                    if (myStats->updateStatsCounter % myStats->periodController == 0) { \
                    	CALL_GRADIENT_DESCENT; \
                        CALL_UPDATE_LOCKS(0); \
                        if (myStats->periodController < 50000) { \
                            myStats->periodController *= 2; \
                        } \
                    } \
                } \
            	unsigned long start_tick, end_tick; \
            	TICK(start_tick); \
            	while (IS_LOCKED(htm_single_global_lock)) { \
                    PAUSE_INSTR; \
            	} \
            	TICK(end_tick); \
            	myStats->cyclesWaiting += end_tick - start_tick; \
            } \
            WAIT_FOR_CPU_LOCKS; \
            WAIT_FOR_TX_LOCKS(b); \
            CHECK_ACQUIRE_TX_LOCKS(b); \
            CHECK_ACQUIRE_CPU_LOCKS; \
            ARG_TYPE TM_buff; \
            STATUS_TYPE status = HTM_BEGIN(TM_buff); \
            if (status == IS_STARTED) { if (IS_LOCKED(htm_single_global_lock)) { HTM_ABORT(30); }  break; } \
            PREPARE_CHECK_EXPLICIT(TM_buff, status, 0x31); \
            if (IS_EXPLICIT_ABORT(0x31)) { \
                tx = 0; \
                CHECK_RELEASE_TX_LOCKS; \
                CHECK_RELEASE_CPU_LOCKS; \
                RELEASE_AUX_LOCK; \
                break; \
            } \
            ACQUIRE_AUX_LOCK; \
            if (tries == MAX_ATTEMPTS) myStats->abortedTxs++; \
            tries--; \
            capacity = IS_CAPACITY(status, TM_buff); \
            if (IS_CONFLICT(status, TM_buff)) { \
              REGISTER_TM_CONFLICT(b); \
            } \
            myStats->totalAborts++; \
            if (IS_CONFLICT(status, TM_buff)) { \
                myStats->conflictAbort++; \
            } \
            else if (IS_CAPACITY(status, TM_buff)) { \
                myStats->capacityAbort++; \
            } \
            else if (SHOULD_RETRY(status, TM_buff)) { \
                myStats->retryAbort++; \
            } else if (IS_EXPLICIT_ABORT_NO_CODE(TM_buff)) { \
                myStats->lockAbort++; \
            } else { \
                myStats->otherAbort++; \
            } \
            if (tries <= 0) {   \
            	number_of_locks = 0; \
                unsigned long start_tick, end_tick; \
                TICK(start_tick); \
                pthread_mutex_lock(&htm_single_global_lock); \
                TICK(end_tick); \
                myStats->cyclesWaiting += end_tick - start_tick; \
                break; \
            } \
        }


# define TM_END_EXT(tx) \
  if (tx == 1) { \
    if (tries > 0) { \
        HTM_COMMIT; \
        REGISTER_TM_COMMIT(block_id); \
        myStats->totalTSXTxs++; \
    } else {    \
        pthread_mutex_unlock(&htm_single_global_lock); \
        myStats->totalSGLTxs++; \
    } \
    RELEASE_AUX_LOCK; \
    CHECK_RELEASE_TX_LOCKS; \
    CHECK_RELEASE_CPU_LOCKS; \
    if (acquiredCpuLock) { \
        myStats->totalTSXTxsSuccessfulAcquiredTaskAndCoreLocks[number_of_locks]++; \
    } else { \
        myStats->totalTSXTxsSuccessfulAcquiredLocks[number_of_locks]++; \
    } \
    myStats->totalRetries += MAX_ATTEMPTS - tries; \
    myStats->totalAtomicBlocks++; \
  }\
};\
TM_COMMIT_QS;

# define TM_END() \
    TM_END_EXT(tx); \
}

# define GRADIENT_DESCENT() { \
    int k; \
    unsigned long txns_processed = 0; \
    for (k = 0; k < NUMBER_THREADS; k++) {   \
        txns_processed += statistics[k].totalAtomicBlocks; \
    } \
    double diff_txns = txns_processed - globalOptimizer.last_total_txns; \
    if (diff_txns > 10000) { \
        unsigned long current_cycles; \
    TICK(current_cycles); \
    double current_throughput = (diff_txns * 50000.0) / (current_cycles - globalOptimizer.last_cycles); \
    globalOptimizer.last_total_txns = txns_processed; \
    globalOptimizer.last_cycles = current_cycles; \
    if (globalOptimizer.measurement_0 < 0) { \
        globalOptimizer.measurement_0 = current_throughput; \
        globalOptimizer.current_shift = 0; \
    } else if (globalOptimizer.measurement_1 < 0) { \
        globalOptimizer.measurement_1 = current_throughput; \
        globalOptimizer.current_shift = VALUE_SHIFT; \
    } else { \
        globalOptimizer.measurement_2 = current_throughput; \
        if (globalOptimizer.measurement_0 > globalOptimizer.measurement_1 && globalOptimizer.measurement_0 > globalOptimizer.measurement_2) { \
            (*globalOptimizer.value_ptr) -= VALUE_SHIFT; \
            if (globalOptimizer.best_ever_measurement/globalOptimizer.measurement_0 > 1.40) { \
                globalOptimizer.alpha_value = globalOptimizer.best_ever_alpha; \
                globalOptimizer.min_value = globalOptimizer.best_ever_min; \
            } \
        } else if (globalOptimizer.measurement_2 > globalOptimizer.measurement_0 && globalOptimizer.measurement_2 > globalOptimizer.measurement_1) { \
            (*globalOptimizer.value_ptr) += VALUE_SHIFT; \
             if (globalOptimizer.best_ever_measurement/globalOptimizer.measurement_2 > 1.40) { \
                globalOptimizer.alpha_value = globalOptimizer.best_ever_alpha; \
                globalOptimizer.min_value = globalOptimizer.best_ever_min; \
            } \
        } else if (globalOptimizer.best_ever_measurement/globalOptimizer.measurement_1 > 1.40) { \
            globalOptimizer.alpha_value = globalOptimizer.best_ever_alpha; \
            globalOptimizer.min_value = globalOptimizer.best_ever_min; \
        } \
        if (*globalOptimizer.value_ptr > (1.0 - 2*VALUE_SHIFT)) { *globalOptimizer.value_ptr = 1.0 - 2*VALUE_SHIFT; } \
        else { \
            if (globalOptimizer.value_ptr == &globalOptimizer.alpha_value) { \
                if (*globalOptimizer.value_ptr < (0.5 + 2*VALUE_SHIFT)) { *globalOptimizer.value_ptr = 0.5 + 2*VALUE_SHIFT; } \
            } else { \
                if (*globalOptimizer.value_ptr < (0.0 + 2*VALUE_SHIFT)) { *globalOptimizer.value_ptr = 0.0 + 2*VALUE_SHIFT; } \
            } \
        } \
        if (globalOptimizer.measurement_0 > globalOptimizer.best_ever_measurement) { \
            globalOptimizer.best_ever_measurement = globalOptimizer.measurement_0; \
            globalOptimizer.best_ever_alpha = globalOptimizer.alpha_value; \
            globalOptimizer.best_ever_min = globalOptimizer.min_value; \
        } else if (globalOptimizer.measurement_1 > globalOptimizer.best_ever_measurement) { \
            globalOptimizer.best_ever_measurement = globalOptimizer.measurement_1; \
            globalOptimizer.best_ever_alpha = globalOptimizer.alpha_value; \
            globalOptimizer.best_ever_min = globalOptimizer.min_value; \
        } else if (globalOptimizer.measurement_2 > globalOptimizer.best_ever_measurement) { \
            globalOptimizer.best_ever_measurement = globalOptimizer.measurement_2; \
            globalOptimizer.best_ever_alpha = globalOptimizer.alpha_value; \
            globalOptimizer.best_ever_min = globalOptimizer.min_value; \
        } \
        if (globalOptimizer.value_ptr == &globalOptimizer.alpha_value) { globalOptimizer.value_ptr = &globalOptimizer.min_value; } \
        else { globalOptimizer.value_ptr = &globalOptimizer.alpha_value; } \
        globalOptimizer.measurement_0 = -1; \
        globalOptimizer.measurement_1 = -1; \
        globalOptimizer.measurement_2 = -1; \
        globalOptimizer.current_shift = -VALUE_SHIFT; \
    } \
    } \
}

#  if (NUMBER_THREADS == 1)

#    define TM_CONFLICT(taskId)

#    define TM_COMMIT(taskId)

#  else // Threads != 1

#    ifdef defined(USE_STATIC_SAMPLING)

#      define TM_CONFLICT(taskId) {  \
         myStats->abortStats[taskId][globalSnapshot[neighbourghSample].task_id]++;  \
       }

#      define TM_COMMIT(taskId) {    \
         myStats->commitStats[taskId][globalSnapshot[neighbourghSample].task_id]++;  \
       }

#    elif defined(USE_LINEAR_SCAN)

#      define TM_CONFLICT(taskId) {  \
         int y = 0; \
         for (; y < NUMBER_THREADS; y++) { \
           if (y == myThreadId) continue; \
             myStats->abortStats[taskId][globalSnapshot[y].task_id]++;  \
           } \
         }

#      define TM_COMMIT(taskId) {    \
         int y = 0; \
         for (; y < NUMBER_THREADS; y++) { \
           if (y == myThreadId) continue; \
             myStats->commitStats[taskId][globalSnapshot[y].task_id]++;  \
           } \
         }

#    else /*!USE_LINEAR_SCAN && !USE_STATIC_SAMPLING*/

#      define TM_CONFLICT(taskId) {  \
         unsigned short b = myStats->totalAtomicBlocks % NUMBER_THREADS; \
         if (b == thread_id) { \
           b = (b + 1) % NUMBER_THREADS; \
         } \
         myStats->abortStats[taskId][globalSnapshot[b].task_id]++;  \
       }

#      define TM_COMMIT(taskId) {    \
         unsigned short b = myStats->totalAtomicBlocks % NUMBER_THREADS; \
         if (b == thread_id) { \
           b = (b + 1) % NUMBER_THREADS; \
         } \
         myStats->commitStats[taskId][globalSnapshot[b].task_id]++;  \
       }

#    endif /*!USE_LINEAR_SCAN && !USE_STATIC_SAMPLING*/

#  endif // Threads > 1


#  ifdef USE_HTM_LOCKS

#    define TM_ACQUIRE_LOCKS(taskId, number_of_locks) { \
       int i; \
       short last_locked = -1; \
       unsigned budget = 3; \
       while (1) { \
         ARG_TYPE TM_buff; \
         STATUS_TYPE status = HTM_BEGIN(TM_buff); \
         if (status == IS_STARTED) { \
           for (i = 0; i < NUMBER_ATOMIC_BLOCKS; i++) { \
             unsigned short current = globalLocksToAcquire[taskId][i]; \
               if (current <= last_locked || current == NO_LOCK) { \
                 spinLocksAcquired[i] = NO_LOCK; \
                 break; \
               } \
               last_locked = current; \
               spinLocksAcquired[i] = current; \
               if (paddedSpinLocks[current].lock == 1) { \
                 HTM_ABORT(0xaa); \
               } \
               paddedSpinLocks[current].lock = 1; \
               number_of_locks++; \
               myStats->totalTSXTxsAcquiredLock[current]++; \
             } \
             HTM_COMMIT; \
             break; \
           } else { \
           --budget; \
           PREPARE_CHECK_EXPLICIT(TM_buff, status, 0xaa); \
           if (budget <= 0 || IS_EXPLICIT_ABORT(0xaa)) { \
             for (i = 0; i < NUMBER_ATOMIC_BLOCKS; i++) { \
               unsigned short current = globalLocksToAcquire[taskId][i]; \
                 if (current <= last_locked || current == NO_LOCK) { \
                   spinLocksAcquired[i] = NO_LOCK; \
                   break; \
                 } \
                 last_locked = current; \
                 spinLocksAcquired[i] = current; \
                 while (__sync_val_compare_and_swap(&paddedSpinLocks[current].lock, 0, 1) == 1) { \
                   PAUSE_INSTR; \
                 } \
                 number_of_locks++; \
                 myStats->totalTSXTxsAcquiredLock[current]++; \
               } \
               break; \
             } \
           } \
         } \
       } \

#  else /*!USE_HTM_LOCKS*/

#    define TM_ACQUIRE_LOCKS(taskId, number_of_locks) { \
       int i; \
       short last_locked = -1; \
       for (i = 0; i < NUMBER_ATOMIC_BLOCKS; i++) { \
         unsigned short current = globalLocksToAcquire[taskId][i]; \
         if (current <= last_locked || current == NO_LOCK) { \
           spinLocksAcquired[i] = NO_LOCK; \
       	   break; \
         } \
         last_locked = current; \
         spinLocksAcquired[i] = current; \
         while (__sync_val_compare_and_swap(&paddedSpinLocks[current].lock, 0, 1) == 1) { \
       	   PAUSE_INSTR; \
         } \
         number_of_locks++; \
         myStats->totalTSXTxsAcquiredLock[current]++; \
       } \
     } \

#  endif /*!USE_HTM_LOCKS*/

#  define TM_ACQUIRE_CPU_LOCKS(taskId) { \
     while (__sync_val_compare_and_swap(&paddedCpuLocks[myStats->cpuLockId].lock, 0, 1) == 1) { \
       PAUSE_INSTR; \
     } \
   } \

#  define TM_RELEASE_LOCKS(taskId) { \
     int i; \
     for (i = 0; i < NUMBER_ATOMIC_BLOCKS; i++) { \
       unsigned short current = spinLocksAcquired[i]; \
       if (current == NO_LOCK) { \
         break; \
       } \
       paddedSpinLocks[current].lock = 0; \
       spinLocksAcquired[i] = NO_LOCK; \
     }   \
   }   \

#  define TM_RELEASE_CPU_LOCKS(taskId) { \
     paddedCpuLocks[myStats->cpuLockId].lock = 0; \
   } \

#  define OBTAIN_GAUSSIAN_VALUE(maxThreshold, searchedValue) { \
     searchedValue = searchedValue - 0.5; \
     int row = 0; \
     int foundRow = 0; \
     int column = 0; \
        int foundColumn = 0; \
        for (; row < TABLE_ROW_INDEXES; row++) { \
            if (GAUSSIAN_TABLE[row][0] > searchedValue) { \
                foundRow = 1; \
                row--; \
                for (; column < TABLE_COLUMN_INDEXES; column++) { \
                    if (GAUSSIAN_TABLE[row][column] > searchedValue) { \
                        foundColumn = 1; \
                        column--; \
                        break; \
                    }\
                }\
                if (!foundColumn) { column--; } \
                break; \
            } \
        } \
        if (!foundRow) { row--; column = TABLE_COLUMN_INDEXES - 1; } \
        maxThreshold = row * 0.1 + column * 0.01; \
   }

#  define CONDITION_TO_LOCK conjAbortProb[x][y] > prob && conjAbortProb[x][y] > min_val

#  define UPDATE_LOCKS_TO_ACQUIRE(print) { \
    double alpha = globalOptimizer.alpha_value; \
    double min_val = globalOptimizer.min_value; \
    if (globalOptimizer.value_ptr == &globalOptimizer.alpha_value) { \
        alpha += globalOptimizer.current_shift; \
    } else { \
        min_val += globalOptimizer.current_shift; \
    } \
    if (print) printf("\nMin Value: %.04lf\n", min_val); \
    unsigned int x,y; \
    unsigned int threadId; \
    for (x = 0; x < NUMBER_ATOMIC_BLOCKS; x++) { \
        CALL_UPDATE_LOCKS_SCHEME(print); /* The magic happens here */ \
        double stdev = sqrt(sumOfSquaredDelta / NUMBER_ATOMIC_BLOCKS); \
        float searchedValue = alpha; \
        double maxThreshold; \
        OBTAIN_GAUSSIAN_VALUE(maxThreshold, searchedValue); \
        double prob = maxThreshold * stdev + mean; \
        if (print) { \
            printf("Row: %hu\t %.04lf = %.04lf (taken from percentile => %.04lf * %.04lf + %.04lf)\n", x, prob, searchedValue, maxThreshold, stdev, mean); \
        } \
        for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
            if (CONDITION_TO_LOCK) { \
                globalLocksToAcquire[x][y] = y; \
                globalLocksToAcquire[y][x] = x; \
            } else { \
                if (globalLocksToAcquire[x][y] != y) { \
                    globalLocksToAcquire[x][y] = NO_LOCK; \
                    globalLocksToAcquire[y][x] = NO_LOCK; \
                } \
            } \
        } \
        int tmp; \
        for(t = 0; t < NUMBER_ATOMIC_BLOCKS; t++) { \
            for(y = 0; y < NUMBER_ATOMIC_BLOCKS-t-1; y++) { \
                if(globalLocksToAcquire[x][y] > globalLocksToAcquire[x][y+1]) { \
                    tmp = globalLocksToAcquire[x][y+1]; \
                    globalLocksToAcquire[x][y+1] = globalLocksToAcquire[x][y]; \
                    globalLocksToAcquire[x][y] = tmp; \
                } \
            } \
        } \
    } \
   }


#  define CALL_UPDATE_LOCKS_SCHEME(print) \
    /* Notice that we are doing this for each x transaction */ \
        unsigned long totalExecutions = 0; \
        int t; \
        double aux = 0; \
        for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
            totalAbortStats[x][y] = 0; \
            totalCommitStats[x][y] = 0; \
            for (t = 0; t < NUMBER_THREADS; t++) { \
                totalAbortStats[x][y] += statistics[t].abortStats[x][y]; \
                totalCommitStats[x][y] += statistics[t].commitStats[x][y]; \
                totalExecutions += statistics[t].abortStats[x][y] + statistics[t].commitStats[x][y]; \
            } \
        } \
        for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
            double total = (double)(totalAbortStats[x][y] + totalCommitStats[x][y]); \
            conjAbortProb[x][y] = totalExecutions == 0 ? 0.0 : totalAbortStats[x][y] / ((double)totalExecutions); \
            aux += conjAbortProb[x][y]; \
        } \
        double mean = aux / NUMBER_ATOMIC_BLOCKS; \
        double sumOfSquaredDelta = 0; \
        for (y = 0; y < NUMBER_ATOMIC_BLOCKS; y++) { \
            aux = mean - conjAbortProb[x][y]; \
            sumOfSquaredDelta += aux * aux; \
        } \



#  define TM_BEGIN_RO()                 TM_BEGIN(0)
#  define TM_RESTART()                  HTM_ABORT(0x29);
#  define TM_RESTART_EXT(code)    \
    if (tries > 0) { \
        HTM_ABORT(code); \
    } else {    \
        pthread_mutex_unlock(&htm_single_global_lock); \
        CHECK_RELEASE_TX_LOCKS; \
        CHECK_RELEASE_CPU_LOCKS; \
        tx = 0; \
    } \
    RELEASE_AUX_LOCK; \


#  define TM_EARLY_RELEASE(var)

#  define TM_SHARED_READ(var)         (var)
#  define TM_SHARED_WRITE(var, val)   ({var = val; var;})
#  define TM_LOCAL_WRITE(var, val)    ({var = val; var;})


#  define TM_SHARED_READ(var)         (var)
#  define TM_SHARED_WRITE(var, val)   ({var = val; var;})

#  define TM_SHARED_READ_I(var)         (var)
#  define TM_SHARED_READ_L(var)         (var)
#  define TM_SHARED_READ_P(var)         (var)
#  define TM_SHARED_READ_F(var)         (var)

#  define TM_SHARED_WRITE_I(var, val)   ({var = val; var;})
#  define TM_SHARED_WRITE_L(var, val)   ({var = val; var;})
#  define TM_SHARED_WRITE_P(var, val)   ({var = val; var;})
#  define TM_SHARED_WRITE_F(var, val)   ({var = val; var;})

#  define TM_LOCAL_WRITE_I(var, val)    ({var = val; var;})
#  define TM_LOCAL_WRITE_L(var, val)    ({var = val; var;})
#  define TM_LOCAL_WRITE_P(var, val)    ({var = val; var;})
#  define TM_LOCAL_WRITE_F(var, val)    ({var = val; var;})

#endif /*TM_H*/
