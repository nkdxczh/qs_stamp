#ifndef  QS_SCHEDULER_H
#define  QS_SCHEDULER_H 1

#include <boost/lockfree/queue.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <time.h>

#include "qs_schunit.h"

#define num_q 3
#define per_q 4

unsigned QS_hash(void* ptr);

class QS_SchBlock{
    public:
        void* obj;
        std::mutex lock;
        int next;
        unsigned key;

        QS_SchBlock(void* ptr){
            obj = ptr;
            key = QS_hash(ptr);
        }
};

void QS_contention_manage_begin(QS_SchBlock& sb);

void QS_contention_manage_abort(QS_SchBlock& sb, int flag);

void QS_dispatch(int id);

void QS_update();

void QS_init();

void QS_end();

#endif
