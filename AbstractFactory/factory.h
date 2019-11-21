#include "typelist.h"
#include "typetable.h"
#include "root.h"

/*
 * Шаблонные виртуальные методы запрещены языком.
 * Наследник не знает шаблонного параметра функции Get,
 * поэтому базовому классу нужно что-то узнать про типы.
 * Вместо передачи хитрых структур просто добавим шаблонный параметр.
*/
template<typename TTable>
struct Factory {
    template <typename U>
    Root* Get() {
        constexpr int n = TTCol<U, TTable>::Res;
        return GetNth(n);

    };
    virtual Root* GetNth(int n) = 0;
};


template <typename TList, typename TTable>
struct FactoryController : Factory<TTable> {
    // TryTypeAt - см. typelist.h. Если такого типа нет, нужно возвращать Root*.
    // По условию - не больше 4 типов в списке.
    using t1 = typename TryTypeAt<0, Root, TList>::type;
    using t2 = typename TryTypeAt<1, Root, TList>::type;
    using t3 = typename TryTypeAt<2, Root, TList>::type;
    using t4 = typename TryTypeAt<3, Root, TList>::type;
    Root* GetNth(int n) {
        if (n == 0) {
            return new t1;
        }
        if (n == 1) {
            return new t2;
        }
        if (n == 2) {
            return new t3;
        }
        if (n == 3) {
            return new t4;
        }
    }
};

template <typename TList, typename TTable>
struct ConcreteFactory {
public:
    using result = FactoryController<TList, TTable>;
};

template <int C, int N, typename ...T>
struct GetAbstractFactory {
    using TTable = TypeList<T...>;

    template <typename U>
    using GetConcreteFactory = ConcreteFactory<typename TypeAt<TTRow<U, TypeList<T...>>::Res, TTable>::type, TTable>;
};
