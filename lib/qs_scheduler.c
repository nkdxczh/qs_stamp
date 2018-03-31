#include "qs_scheduler.h"
#include "qs_schunit.h"

#include <thread>

QS_SchMap sch_map;

bool QS_terminate = false;
int QS_size_q = 100;
int QS_usage_q = num_q;

bool* QS_block;

boost::lockfree::queue<QS_SchBlock*> **QS_queues;
std::mutex *QS_locks;

unsigned QS_hash(void* ptr){
    unsigned res = (long) ptr * 11 % 46591;
    return res;
}

void QS_contention_manage_begin(QS_SchBlock& sb){
    QS_SchUnit* unit = sch_map.get(sb.key);

    if(unit == NULL)unit = sch_map.create(sb.key, sb.key % num_q);

    sb.queue = unit->getQueue();

    sb.lock.lock();

    QS_queues[sb.queue]->push(&sb);

    if(QS_WAIT == 0){
        while(!sb.lock.try_lock());
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

            if(block->key % 10 == 0){
            	QS_SchUnit* unit = sch_map.get(block->key);
            	if(unit == NULL)unit = sch_map.create(block->key, block->key % num_q);

            	unit->add();
            }

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

void QS_update(){
    int interval = 1000;

    while(!QS_terminate){
        usleep(interval);
	if(interval == 1000)interval = 10000;

        std::map<int, std::vector<unsigned>, std::greater<int>>* view = sch_map.getOrderedView();

        bool forward =  true;
        int idx = 0;

        for(const auto& it : *view){
            int count = it.first;
            for(const auto& vit : it.second){
                auto item = sch_map.get(vit);
                item->setQueue(idx);
                item->reset();
                if(forward){
                    idx++;
                    if(idx == num_q){
                        idx--;
                        forward = false;
                    }
                }
                else{
                    idx--;
                    if(idx < 0){
                        idx = 0;
                        forward = true;
                    }
                }
            }
        }

        delete view;
    }
}

void QS_contention_manage_commit(QS_SchBlock& sb){
    QS_locks[sb.queue].unlock();
}

void QS_init(){
    QS_queues = (boost::lockfree::queue<QS_SchBlock*> **) malloc(sizeof(void*) * num_q);
    QS_block = (bool*) malloc(sizeof(bool) * num_q);
    QS_locks = new std::mutex[num_q];

    QS_terminate = false;

    std::thread* dispatchers[num_q][per_q];

    std::thread* updater;

    for(int i = 0; i < num_q; ++i){
        QS_queues[i] = new boost::lockfree::queue<QS_SchBlock*>(QS_size_q);
        QS_block[i] = false;
    }

    updater = new std::thread(QS_update);
    updater->detach();

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
