#ifndef  QS_SCHUNIT_H
#define  QS_SCHUNIT_H 1

#include <iostream>
#include <mutex>
#include <atomic>
#include <map>
#include <vector>

class QS_SchUnit{
    private:
        std::mutex lock;
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

class QS_SchMap{
    private:
        std::unordered_map<unsigned, QS_SchUnit*> map;
        std::mutex creation_lock;

    public:
        QS_SchUnit* get(unsigned key);
        QS_SchUnit* create(unsigned key, int queue);
        std::map<int, std::vector<unsigned>, std::greater<int>>* getOrderedView();
};

#endif
