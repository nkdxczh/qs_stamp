#include "qs_schunit.h"

void QS_SchUnit::add(){

    count++;

}

void QS_SchUnit::reset(){

    count = 0;

}

void QS_SchUnit::setQueue(int q){

    queue = q;

}

QS_SchUnit* QS_SchMap::get(unsigned key){
    std::unordered_map<unsigned,QS_SchUnit*>::const_iterator it;
    try{
        it = map.find(key);
    }catch(const std::exception& e){
        return NULL;
    }

    if(it == map.end()){
        return NULL;
    }

    else return it->second;
}

QS_SchUnit* QS_SchMap::create(unsigned key, int queue){
    creation_lock.lock();

    auto it = map.find(key);
    if(it != map.end()){
        creation_lock.unlock();
        return it->second;
    }

    QS_SchUnit* unit = new QS_SchUnit(key);
    unit->setQueue(queue);

    map.insert({key,unit});

    creation_lock.unlock();

    return unit;
}

std::map<int, std::vector<unsigned>, std::greater<int>>* QS_SchMap::getOrderedView(){
    std::map<int, std::vector<unsigned>, std::greater<int>>* res = new std::map<int, std::vector<unsigned>, std::greater<int>>();

    for(auto it = map.begin(); it != map.end(); ++it )
    {
        int key = it->second->getCount();
        unsigned val = it->first;
        auto target = res->find(key);
        if(target == res->end()){
            std::vector<unsigned> newv;
            newv.push_back(val);
            res->insert({key, newv});
        }
        else{
            target->second.push_back(val);
        }
    }

    return res;
}
