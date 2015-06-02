#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>
#include "smartpoint.hpp"

namespace cpptool {
namespace placeholder {

class placeholder_ {};
placeholder_ _1;
placeholder_ _2;
}

template<class R>
class FunctionBase0
{
public:
    virtual R Invoke() = 0;
    virtual ~FunctionBase0(){}
};


template<class R, class T>
class MemFunction0: public FunctionBase0<R>
{
public:
    MemFunction0(R(T::*pMemFun)(), T* pObj)
        :pMemFun_(pMemFun), pObj_(pObj)
    {
    }

    ~MemFunction0()
    {
    }

    R Invoke()
    {
        (pObj_->*pMemFun_)();
    }
private:
    R(T::*pMemFun_)();
    T* pObj_;
};

template<class R, class ARG>
class FunctionBase1
{
public:
    virtual R Invoke(ARG arg) = 0;
    virtual ~FunctionBase1(){ 
    }
};

template<class R, class T, class ARG>
class MemFunction1: public FunctionBase1<R, ARG>
{
public:
    MemFunction1(R(T::*pMemFun)(ARG), T*pObj)
        :pMemFun_(pMemFun), pObj_(pObj)
    {

    }

    ~MemFunction1() 
    {
    }

    R Invoke(ARG arg) 
    {
       (pObj_->*pMemFun_)(arg); 
    }
private:
    R(T::*pMemFun_)(ARG);
    T* pObj_;
};


// signature 被特化为R()
template<class Signature>
class Function;
template<class R>
class Function<R()>
{
public:
    Function() {}

    template<class T>
    Function(R(T::*pMemFun)(), T* pObj):pFunBase_(new MemFunction0<R, T>(pMemFun, pObj))
    {
    }

    Function(const Function<R()>& val)
    {
        Function<R()>* pFun = const_cast<Function<R()>*>(&val);
        pFunBase_ = pFun->pFunBase_;
    }

    R operator()()
    {
        if (!pFunBase_.isNULL()) {
            return pFunBase_->Invoke();
        }
        else
            R();
    }

    ~Function()
    {
    }
private:
    SmartPoint<FunctionBase0<R> > pFunBase_;
};

// One parameter partial specialization
template<class R, class ARG>
class Function<R(ARG)>
{
public:
    // default constructor
    Function(){}

    template<class T>
    Function(R(T::*pMemFun)(ARG), T* pObj, placeholder::placeholder_ ph)
        : pFunBase_(new MemFunction1<R, T, ARG>(pMemFun, pObj))
    {
    }

    Function(const Function<R(ARG)>& val)
    {
        Function<R(ARG)>* pFun = const_cast<Function<R(ARG)>*>(&val);
        pFunBase_ = pFun->pFunBase_;
    }

    ~Function()
    {
    }

    R operator()(ARG arg)
    {
        if (!pFunBase_.isNULL())
            return pFunBase_->Invoke(arg);
        else
            return R();
    }

private:
    SmartPoint<FunctionBase1<R, ARG> > pFunBase_;
};

template<class R, class ARG1, class ARG2>
class FunctionBase2
{
public:
    virtual R Invoke(ARG1 arg1, ARG2 arg2) = 0;
    virtual ~FunctionBase2(){ 
    }
};

template<class R, class T, class ARG1, class ARG2>
class MemFunction2: public FunctionBase2<R, ARG1, ARG2>
{
public:
    MemFunction2(R(T::*pMemFun)(ARG1, ARG2), T*pObj)
        :pMemFun_(pMemFun), pObj_(pObj)
    {

    }

    ~MemFunction2()
    {
    }

    R Invoke(ARG1 arg1, ARG2 arg2)
    {
       (pObj_->*pMemFun_)(arg1, arg2);
    }
private:
    R(T::*pMemFun_)(ARG1, ARG2);
    T* pObj_;
};


// two parameter partial specialization
template<class R, class ARG1, class ARG2>
class Function<R(ARG1, ARG2)>
{
public:
    // default constructor
    Function(){}

    template<class T>
    Function(R(T::*pMemFun)(ARG1, ARG2), T* pObj, placeholder::placeholder_ ph1, placeholder::placeholder_ ph2)
        : pFunBase_(new MemFunction2<R, T, ARG1, ARG2>(pMemFun, pObj))
    {
    }

    Function(const Function<R(ARG1, ARG2)>& val)
    {
        Function<R(ARG1, ARG2)>* pFun = const_cast<Function<R(ARG1, ARG2)>*>(&val);
        if (pFun == this)
            return;

        pFunBase_ = pFun->pFunBase_;
    }

    ~Function()
    {
    }

    R operator()(ARG1 arg1, ARG2 arg2)
    {
        if (!pFunBase_.isNULL())
            return pFunBase_->Invoke(arg1, arg2);
        else
            return R();
    }

private:
    SmartPoint<FunctionBase2<R, ARG1, ARG2> > pFunBase_;
};


} // namespace cpptool
#endif
