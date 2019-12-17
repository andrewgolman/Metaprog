//
// Functor и связанные с ним структуры.
//

#ifndef SHAD_FUNCTOR_H
#define SHAD_FUNCTOR_H

#include <iostream>
#include "utils.h"
#include "typelist.h"

using std::cout;
using std::endl;

// Обертка для функции. Указатель на функцию имеет конкретный тип, поэтому хранится в наследнике.
template <typename ReturnType, class ...Args>
class FuncWrapper {
public:
    virtual ReturnType operator () (Args&&... args) = 0;
    virtual ~FuncWrapper() = default;
};

template <typename Func, typename ReturnType, class ...Args>
class FuncWrapperSpec : public FuncWrapper<ReturnType, Args...> {
public:
    Func* func;
    explicit FuncWrapperSpec(Func* f) : func(f) {}
    ReturnType operator () (Args&&... args) override {
        return (*func)(std::forward<Args>(args)...);
    }
};

// Проверка, можно ли скастовать аргументы из тайплиста GotTL в ArgsTL.
template <class GotTL, class ArgsTL>
struct CheckArgs : Conditional<
        IsCastable<typename ArgsTL::Head, typename GotTL::Head>::value,
        typename CheckArgs<typename ArgsTL::Tail, typename GotTL::Tail>::type,
        std::false_type
>::Res {};

template <class ArgsTL>
struct CheckArgs<EmptyTypeList, ArgsTL> : std::false_type {};

template <class GotTL>
struct CheckArgs<GotTL, EmptyTypeList> : std::false_type {};

template <>
struct CheckArgs<EmptyTypeList, EmptyTypeList> : std::true_type {};


template <typename ReturnType, class ...Args>
class Functor {
    FuncWrapper<ReturnType, Args...>* fPtr;
public:
    template <typename F>
    explicit Functor(F* fPtr) : fPtr(new FuncWrapperSpec<F, ReturnType, Args...>(fPtr)) {}

    ReturnType operator() (Args... args) {
        return (*fPtr)(std::forward<Args>(args)...);
    }

    template <class... OtherArgs>
    ReturnType operator() (OtherArgs&&... args) {
        if (!check<OtherArgs...>(std::forward<Args>(args)...)) {
            cout << "Expected args: " << ExpectedArgs() << endl;
            cout << "Got args ";
            PrintArgs(std::forward<Args>(args)...);
            cout << "instead" << endl;
            throw std::invalid_argument("Expected args:" + ExpectedArgs());
        }
        return (*fPtr)(std::forward<Args>(args)...);
    }

    template <class... OtherArgs>
    bool check(OtherArgs&&... args) {
        return CheckArgs<TypeList<OtherArgs...>, TypeList<Args...>>::value;
    }

    virtual string ExpectedArgs() {
        // строка, описывающая ожидаемые аргументы
        // это надо заимплементить для базового класса функторов из FuncTable
        return "";
    }

    ~Functor() {
        delete fPtr;
    }
};

#endif //SHAD_FUNCTOR_H
