#ifndef SHAD_UTILS_H
#define SHAD_UTILS_H

template <bool b, typename A, typename B>
struct Conditional;

template <typename A, typename B>
struct Conditional<true, A, B> {
    using Res = A;
};

template <typename A, typename B>
struct Conditional<false, A, B> {
    using Res = B;
};

template <typename A, typename B>
struct IsSame : std::false_type {};

template <typename A>
struct IsSame<A, A> : std::true_type {};


template <class...>
using VoidType = void;

template <class, class A, class B>
struct IsCastable_ : std::false_type {};

template <class A, class B>
struct IsCastable_<VoidType<decltype(A(std::declval<B>()))>, A, B> : std::true_type {};

template <class A, class B>
using IsCastable = IsCastable_<VoidType<>, A, B>;


void PrintArgs() {}

template<class T, class... Args>
void PrintArgs(T v, Args&&... args) {
    std::cout << v << " ";
    PrintArgs(std::forward<Args>(args)...);
}


#endif //SHAD_UTILS_H
