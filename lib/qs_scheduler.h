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

#define num_q 1
#define per_q 1
#define QS_TRIES 1
#define QS_WAIT 1
#define QS_DELAY 10000

unsigned QS_hash(void* ptr);

class QS_SchBlock{
    public:
        std::mutex lock;
        int next;
        unsigned key;
        int tries;

        QS_SchBlock(void* ptr){
            key = QS_hash(ptr);
            tries = 0;
        }
};

void QS_contention_manage_begin(QS_SchBlock& sb);

void QS_contention_manage_abort(QS_SchBlock& sb, int flag);

void QS_dispatch(int id);

void QS_update();

void QS_init();

void QS_end();

#endif
