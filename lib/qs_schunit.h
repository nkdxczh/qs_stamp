#ifndef  QS_SCHUNIT_H
#define  QS_SCHUNIT_H 1

#include <iostream>
#include <mutex>
#include <atomic>
#include <map>
#include <vector>
#include <unordered_map>

class __attribute__((__aligned__(64))) QS_create_lock{
    private:
        std::atomic<bool> inner_lock;
    public:
        QS_lock(){inner_lock = false;}
        void lock(){
            bool expected=false;
            while(!inner_lock.compare_exchange_weak(expected,true) || expected){
                expected=false;
            }
        }
        void unlock(){
            inner_lock.exchange(false);
        }
};

class __attribute__((__aligned__(64))) QS_SchUnit{
    private:
        std::atomic<int> count;
        int queue;

    public:
        QS_SchUnit(int q) : count(0), queue(q){}
        void add();
        void reset();
        void setQueue(int q);

        int getCount(){return count;}
        int getQueue(){return queue;}
};

class __attribute__((__aligned__(64))) QS_SchMap{
    private:
        std::unordered_map<unsigned, QS_SchUnit*> map;
        QS_create_lock creation_lock;

    public:
        QS_SchUnit* get(unsigned key);
        QS_SchUnit* create(unsigned key, int queue);
        std::map<int, std::vector<unsigned>, std::greater<int>>* getOrderedView();
};

#endif
