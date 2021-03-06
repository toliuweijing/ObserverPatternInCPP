#ifndef WL_SUBJECT_HPP
#define WL_SUBJECT_HPP 

#include <vector>
#include <memory>
#include <algorithm>
#include "Observer.hpp"


namespace wl{

template<class ArgsT> class Subject {
    typedef details::BaseWrapper<ArgsT> ObserverT;
    typedef std::unique_ptr<ObserverT> ObserverPtr; 
public:
    void operator()(ArgsT args) {
        for (ObserverPtr& o : obvrs_) {
            o->notify(args);
        }
    }
    void operator+=(ObserverT* observer) {
        obvrs_.push_back(ObserverPtr(observer));
    }
    void operator-=(void* observer) {
        auto it = remove_if(obvrs_.begin(), obvrs_.end(), [&](ObserverPtr& o) {
            return o->contains(observer);     
        });
        obvrs_.erase(it, obvrs_.end());
    }
private:
    std::vector<ObserverPtr> obvrs_;
};



}

#endif  //WL_SUBJECT_HPP
