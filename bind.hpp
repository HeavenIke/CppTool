#ifndef BIND_HPP
#define BIND_HPP

#include "function.hpp"

namespace cpptool {

template<class R, class T>
Function<R()> bind(R(T::*pMemFun)(), T* pObj)
{
    return Function<R()>(pMemFun, pObj);
}

template<class R, class T, class ARG>
Function<R(ARG)> bind(R(T::*pMemFun)(ARG), T* pObj, placeholder::placeholder_& ph )
{
    return Function<R(ARG)>(pMemFun, pObj, ph);
}

template<class R, class T, class ARG1, class ARG2>
Function<R(ARG1, ARG2)> bind(R(T::*pMemFun)(ARG1, ARG2), T* pObj, placeholder::placeholder_& ph1, 
            placeholder::placeholder_& ph2)
{
    return Function<R(ARG1, ARG2)>(pMemFun, pObj, ph1, ph2);
}
} // namespace cpptool
#endif
