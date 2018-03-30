#ifndef  SCHEDULER_H
#define  SCHEDULER_H

#include <boost/lockfree/queue.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <time.h>

#define num_q 1
#define per_q 1
#define QS_WAIT 0
#define QS_DELAY 10000

#include <thread>

using namespace std;

bool QS_terminate = false;
int QS_size_q = 100;
int QS_usage_q = num_q;

bool* QS_block;

std::mutex *QS_locks;

unsigned QS_hash(void* ptr);

class  __attribute__((__aligned__(64))) QS_SchBlock{
    public:
        std::mutex lock;
        int queue;
        unsigned key;

        QS_SchBlock(void* ptr){
            key = QS_hash(ptr);
        }
};

boost::lockfree::queue<QS_SchBlock*> **QS_queues;

unsigned QS_hash(void* ptr){
    unsigned res = (long) ptr * 11 % 46591;
    return res;
}

void QS_contention_manage_begin(QS_SchBlock& sb){

    printf("size:%d\n", sizeof(QS_SchBlock));

    sb.queue = sb.key % num_q;

    sb.lock.lock();

    QS_queues[sb.queue]->push(&sb);

    if(QS_WAIT == 0){
        while(!sb.lock.try_lock())std::this_thread::yield();
    }
    else{
        sb.lock.lock();
    }
    sb.lock.unlock();

}

void QS_contention_manage_abort(QS_SchBlock& sb, int flag){
}



void QS_dispatch(int id){
    QS_SchBlock* block;

    while(!QS_terminate){
        if(QS_queues[id]->pop(block)){

            /*QS_SchUnit* unit = sch_map.get(block->key);
            if(unit == NULL)unit = sch_map.create(block->key, block->key % num_q);

            unit->add();*/

            QS_locks[id].lock();

            block->lock.unlock();

            if(QS_WAIT == 0){
                while(!QS_locks[id].try_lock());
            }
            else{
                QS_locks[id].lock();
            }
            QS_locks[id].unlock();

        }

    }
}

void QS_contention_manage_commit(QS_SchBlock& sb){
    QS_locks[sb.queue].unlock();
}

void QS_init(){
    QS_queues = (boost::lockfree::queue<QS_SchBlock*> **) malloc(sizeof(void*) * num_q);
    QS_locks = new std::mutex[num_q];
    QS_block = (bool*) malloc(sizeof(bool) * num_q);

    QS_terminate = false;

    std::thread* dispatchers[num_q][per_q];

    for(int i = 0; i < num_q; ++i){
        QS_queues[i] = new boost::lockfree::queue<QS_SchBlock*>(QS_size_q);
        QS_block[i] = false;
    }

    for(int i = 0; i < num_q; ++i){
        for(int j = 0; j < per_q; ++j){
            dispatchers[i][j] = new std::thread(QS_dispatch, i);
        }
    }

    for(int i = 0; i < num_q; ++i){
        for(int j = 0; j < per_q; ++j){
            dispatchers[i][j]->detach();
        }
    }

}

void QS_end(){
    QS_terminate = true;

    delete [] QS_queues;
}

#endif
