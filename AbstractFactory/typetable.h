#ifndef SHAD_TYPETABLE_H
#define SHAD_TYPETABLE_H

/*
 * Интерфейсы для поиска индекса типа в таблице == списке списков типов.
 */

#include "typelist.h"

template <typename U, typename TList>
struct TTRow;

template <typename U, typename TList>
struct TTCol;

template <typename U>
struct TTCol<U, EmptyTypeList> {
    static constexpr int Res = -1;
};

template <typename U, typename H, typename ...T>
struct TTCol<U, TypeList<H, T...>> {
static constexpr int Res = std::max(Find<U, H>::n, TTCol<U, TypeList<T...>>::Res);
};

template <typename U>
struct TTRow<U, EmptyTypeList> {
    static constexpr int Res = 0;
};

template <typename U, typename H, typename ...T>
struct TTRow<U, TypeList<H, T...>> {
static constexpr int Res = Contains<U, H>::value ? 0 : 1 + TTRow<U, TypeList<T...>>::Res;
};

#endif //SHAD_TYPETABLE_H
