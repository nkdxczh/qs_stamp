#include "qs_scheduler.h"
#include "qs_schunit.h"

#include <thread>

QS_SchMap sch_map;

bool QS_terminate = false;
int QS_size_q = 100;
int QS_usage_q = num_q;

#ifdef USE_STD
std::queue<QS_SchBlock*> **QS_queues;
#else
boost::lockfree::queue<QS_SchBlock*> **QS_queues;
#endif
QS_lock *QS_push_locks;

QS_lock *QS_locks;

unsigned QS_hash(void* ptr){
    unsigned res = (long) ptr * 11 % 46591;
    return res;
}

void QS_contention_manage_begin(QS_SchBlock& sb){
    QS_SchUnit* unit = sch_map.get(sb.key);

    if(unit == NULL)unit = sch_map.create(sb.key, sb.key % num_q);

    sb.queue = unit->getQueue();

    sb.lock.lock();

#ifdef USE_STD
    QS_push_locks[sb.queue].lock();
    QS_queues[sb.queue]->push(&sb);
    QS_push_locks[sb.queue].unlock();
#else
    QS_queues[sb.queue]->push(&sb);
#endif

    sb.lock.lock();

    sb.lock.unlock();

}

void QS_contention_manage_abort(QS_SchBlock& sb, int flag){
}

void QS_dispatch(int id){
    QS_SchBlock* block;
    QS_locks[id].lock();

    while(!QS_terminate){
#ifdef USE_STD
        if(!QS_queues[id]->empty()){

            //QS_push_locks[id].lock();
            block = QS_queues[id]->front();
            QS_queues[id]->pop();
            //QS_push_locks[id].unlock();
#else
        if(QS_queues[id]->pop(block)){
#endif
            
            if(block->key % 100 == 0){
            	QS_SchUnit* unit = sch_map.get(block->key);

            	unit->add();
            }


            block->lock.unlock();

            QS_locks[id].lock();

        }

    }
}

void QS_update(){
    int interval = 1e6;

    while(!QS_terminate){
        usleep(interval);
	//if(interval == 1e5)interval = 1e8;

        std::map<int, std::vector<unsigned>, std::greater<int>>* view = sch_map.getOrderedView();

        bool forward =  true;
        int idx = 0;

        for(const auto& it : *view){
            int count = it.first;
            for(const auto& vit : it.second){
                auto item = sch_map.get(vit);
                if(item == NULL)continue;
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
#ifdef USE_STD
    QS_queues = (std::queue<QS_SchBlock*> **) malloc(sizeof(void*) * num_q);
#else
    QS_queues = (boost::lockfree::queue<QS_SchBlock*> **) malloc(sizeof(void*) * num_q);
#endif
    QS_push_locks = new QS_lock[num_q];

    QS_locks = new QS_lock[num_q];

    QS_terminate = false;

    std::thread* dispatchers[num_q][per_q];

    std::thread* updater;

    for(int i = 0; i < num_q; ++i){
#ifdef USE_STD
        QS_queues[i] = new std::queue<QS_SchBlock*>();
#else
        QS_queues[i] = new boost::lockfree::queue<QS_SchBlock*>(QS_size_q);
#endif
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
    delete [] QS_locks;
    delete [] QS_push_locks;
}
