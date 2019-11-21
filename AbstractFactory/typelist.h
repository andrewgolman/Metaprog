#ifndef SHAD_TYPELIST_H
#define SHAD_TYPELIST_H
struct Void {};

// Реализация TypeAt, Find, IsEmpty, Length, Contains на основе https://habr.com/ru/post/220217/

template<typename ...Args>
struct TypeList{
    using Head = Void;
    using Tail = Void;
};

using EmptyTypeList = TypeList<>;

template<typename H, typename ...T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};

template<unsigned int N, typename TL>
struct TypeAt {
    using type = Void;
};

template<typename ...Args>
struct TypeAt<0, TypeList<Args...>> {
    using type = typename TypeList<Args...>::Head;
};


template<unsigned int N, typename ...Args>
struct TypeAt<N, TypeList<Args...>> {
    using type = typename TypeAt<N - 1, typename TypeList<Args...>::Tail>::type;
};

template<unsigned int N, typename Def, typename TL>
struct TryTypeAt {
    using type = Def;
};

// Если вышли за границу массива, вернуть тип Def
template<typename Def, typename H, typename ...Args>
struct TryTypeAt<0, Def, TypeList<H, Args...>> {
    using type = typename TypeList<H, Args...>::Head;
};

template<unsigned int N, typename Def, typename ...Args>
struct TryTypeAt<N, Def, TypeList<Args...>> {
    using type = typename TryTypeAt<N - 1, Def, typename TypeList<Args...>::Tail>::type;
};

template<unsigned int N, typename Def>
struct TryTypeAt<N, Def, EmptyTypeList> {
    using type = Def;
};

template<typename T, typename TL>
struct Contains :
        std::false_type {};

template<typename ...Args>
struct Contains<Void, Args...> : std::false_type {};

template<typename T, typename ...Args>
struct Contains<T, TypeList<Args...>> :
        std::integral_constant<bool,
                std::is_same<typename TypeList<Args...>::Head, T>::value ||
                Contains<T, typename TypeList<Args...>::Tail>::value
        > {};

template<typename T, unsigned int IndexFrom, typename TL>
struct FindHelper :
        std::integral_constant<unsigned int, 0> {};

template<typename T, unsigned int IndexFrom>
struct FindHelper<T, IndexFrom, EmptyTypeList> :
        std::integral_constant<unsigned int, 0> {};

template<typename T, unsigned int IndexFrom, typename ...Args>
struct FindHelper<T, IndexFrom, TypeList<Args...>> :
        std::integral_constant<unsigned int,
                std::is_same<typename TypeList<Args...>::Head, T>::value
                ? IndexFrom
                : IndexFrom + 1 + FindHelper<T, IndexFrom, typename TypeList<Args...>::Tail>::value> {};

template<typename T, typename TL>
struct Find;

template<typename T>
struct Find<T, EmptyTypeList> {
    static constexpr int n = -1;
};

template<typename ...Args>
struct Find<Void, TypeList<Args...>> {
    static constexpr int n = -1;
};

template<typename T, typename ...Args>
struct Find<T, TypeList<Args...>> {
    static constexpr int n =
            Contains<T, TypeList<Args...>>::value
            ? FindHelper<T, 0, TypeList<Args...>>::value
            : -1;
};

template<typename TL>
struct Length : std::integral_constant<unsigned int, 0> {};

template<typename TL>
struct IsEmpty : std::true_type {};

template<>
struct IsEmpty<TypeList<Void, Void>> : std::true_type {};

template<typename ...Args>
struct IsEmpty<TypeList<Args...>> :
        std::integral_constant<bool,
        std::is_same<typename TypeList<Args...>::Head, Void>::value &&
        IsEmpty<typename TypeList<Args...>::Tail>::value> {};

template<typename ...Args>
struct Length<TypeList<Args...>> :
        std::integral_constant<unsigned int,
        IsEmpty<TypeList<Args...>>::value ? 0 : 1 + Length<typename TypeList<Args...>::Tail>::value> {};

#endif //SHAD_TYPELIST_H
