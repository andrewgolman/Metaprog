#ifndef SHAD_VISITFACTORY_H
#define SHAD_VISITFACTORY_H

#pragma once

#include <iostream>
#include "typelist.h"
#include "root.h"
#include "functor.h"
#include "acceptor.h"
#include "utils.h"
#include "functorTableSpec.h"

using std::cout;
using std::endl;
using std::string;

// В этом решении доступы разные функторы с разными ReturnType для разных Visitor'ов.
// Эта структура хранит визиторы с нужным типом.
// Можно пойти дальше и реализовать такое же для аргументов функтора.
template <class TLVisitors, class TLAcceptors, class ReturnType, class ...Args>
struct VisitFactoryValidated {
    static ReturnType Go(Visitor* v, Acceptor* a, Args&& ...args) {
        if (auto vx = dynamic_cast<typename TLVisitors::Head*>(v)) {
            a->Accept(vx, std::forward<Args>(args)...);
            // Результат выполнения функтора сохраняется в визиторе
            return vx->Res();
        } else {
            return VisitFactoryValidated<typename TLVisitors::Tail, TLAcceptors, ReturnType, Args...>::Go(
                    v, a, std::forward<Args>(args)...);
        }
    }
};

// Просмотрели все визиторы и не нашли нужный.
template <class TLAcceptors, class ReturnType, class ...Args>
struct VisitFactoryValidated<EmptyTypeList, TLAcceptors, ReturnType, Args...> {
    static ReturnType Go(Visitor* v, Acceptor* a, Args&& ...args) {
        throw std::runtime_error("Valid visitor not found");
    }
};

// Отбираем нужные визиторы.
template <typename ReturnType, typename TLVisitors>
struct SelectVisitors {
    using Same = typename IsSame<typename TLVisitors::Head::ReturnType, ReturnType>::type;
    using Res = typename Conditional<
            Same::value,
            typename PushFront<typename TLVisitors::Head, typename SelectVisitors<ReturnType, typename TLVisitors::Tail>::Res>::Res,
            typename TLVisitors::Tail>::Res;
};

template <typename ReturnType>
struct SelectVisitors<ReturnType, EmptyTypeList> {
    using Res = EmptyTypeList;
};

// Функторы определены для всех пар Visitor-Acceptor, аргументы валидируем внутри функтора, поэтому сразу
// запускаем диспатчеризацию.
template <class TLVisitors, class TLAcceptors, class ReturnType, class ...Args>
struct VisitFactory {
    static ReturnType Go(Visitor* v, Acceptor* a, Args&& ...args) {
        return VisitFactoryValidated<typename SelectVisitors<ReturnType, TLVisitors>::Res, TLAcceptors, ReturnType, Args...>::Go(
                v, a, std::forward<Args>(args)...
        );
    }
};


#endif //SHAD_VISITFACTORY_H
