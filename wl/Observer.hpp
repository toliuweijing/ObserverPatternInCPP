#ifndef WL_OBSERVER_HPP
#define WL_OBSERVER_HPP 

#include<map>  // map
// currently one observer can only register for the same subject once.

namespace wl {
namespace details {



template<
    class ArgsT>        // Argument types
    struct BaseWrapper{
    virtual void notify(ArgsT) = 0;
    virtual bool contains(void*) const = 0;
};




template<
    class RetT,         // return type
    class ObvrT,        // observer type
    class ArgsT>        // Argument types
    class ObserverWrapper;

template<
    class RetT,         // return type
    class ObvrT,       // observer pointer type specification
    class ArgsT>        // Argument types
    class ObserverWrapper<RetT, ObvrT*, ArgsT> : public BaseWrapper<ArgsT>{

    typedef RetT (ObvrT::*Memfun) (ArgsT);

public:
    ObserverWrapper(ObvrT* obvr, Memfun fun) :
        obvr_(obvr), fun_(fun), expired_(false)
    {}


    virtual ~ObserverWrapper() {}


    virtual void notify(ArgsT args) {
        (obvr_->*fun_)(args);
    }

    virtual bool contains(void* obj) const {
        return (void*)obvr_ == obj;
    }

private:
    ObserverWrapper(const ObserverWrapper&);
    ObserverWrapper& operator=(const ObserverWrapper&);

private:
    ObvrT* obvr_;
    Memfun fun_;
    bool expired_;
};


}


template<
    class RetT,         // return type
    class ObvrT,       // observer pointer type specification
    class ArgsT>        // Argument types
    details::ObserverWrapper<RetT, ObvrT*, ArgsT>* bind(ObvrT* obvr, RetT (ObvrT::*fun)(ArgsT)) {
        return new details::ObserverWrapper<RetT, ObvrT*, ArgsT>(obvr, fun);
    }
 

}

#endif  //WL_OBSERVER_HPP
