#ifndef  QS_SCHEDULER_H
#define  QS_SCHEDULER_H 1

#include <boost/lockfree/queue.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <time.h>
#include <atomic>
#include <queue>

#include "qs_schunit.h"

//number of queues
#define num_q 2
//number of dispatchers per queue
#define per_q 1
//lock / try_lock
#define QS_WAIT 1

unsigned QS_hash(void* ptr);

class __attribute__((__aligned__(64))) QS_lock{
    private:
        std::atomic<bool> inner_lock;
        std::mutex mutex_lock;
    public:
        QS_lock(){inner_lock = false;}
        void lock(){
            bool expected=false;
            while(!inner_lock.compare_exchange_weak(expected,true) || expected){
                expected=false;
            }
            //while(!mutex_lock.try_lock());
        }
        void unlock(){
            inner_lock.exchange(false);
            //mutex_lock.unlock();
        }
};

class __attribute__((__aligned__(64))) QS_SchBlock{
    public:
        QS_lock lock;
        int queue;
        //calculated by the input pointer
        unsigned key;

        QS_SchBlock(void* ptr){
            key = QS_hash(ptr);
        }
};

void QS_contention_manage_begin(QS_SchBlock& sb);

void QS_contention_manage_abort(QS_SchBlock& sb, int flag);

void QS_contention_manage_commit(QS_SchBlock& sb);

void QS_dispatch(int id);

void QS_update();

void QS_init();

void QS_end();

#endif
