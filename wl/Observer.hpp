#ifndef WL_OBSERVER_HPP
#define WL_OBSERVER_HPP 


namespace wl {
namespace details {




template<
    class ArgsT>        // Argument types
    struct BaseWrapper{
    virtual void notify(ArgsT) = 0;
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
        obvr_(obvr), fun_(fun)
    {}


    virtual ~ObserverWrapper() {}


    virtual void notify(ArgsT args) {
        (obvr_->*fun_)(args);
    }

private:
    ObserverWrapper(const ObserverWrapper&);
    ObserverWrapper& operator=(const ObserverWrapper&);

private:
    ObvrT* obvr_;
    Memfun fun_;
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
