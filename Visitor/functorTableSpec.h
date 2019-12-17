//
// Набор спецификаций класса Functor под пары Visitor-Acceptor. Для тестирования.
//

#ifndef SHAD_FUNCTORTABLESPEC_H
#define SHAD_FUNCTORTABLESPEC_H

using std::string;

template <class Vis, class Acc>
struct FunctorTable {};

int f11(int i, int j, const string& s) {cout << "V1, A1: " << i << " " << j << " " << s << endl; return 11;}
int f12(int i, int j, const string& s) {cout << "V1, A2: " << i << " " << j << " " << s << endl; return 12;}
int f13(int i, int j, const string& s) {cout << "V1, A3: " << i << " " << j << " " << s << endl; return 13;}
string f21(int i, int j, const string& s) {cout << "V2, A1: " << i << " " << j << " " << s << endl; return "s21";}
string f22(int i, int j, const string& s) {cout << "V2, A2: " << i << " " << j << " " << s << endl; return "s22";}
string f23(int i, int j, const string& s) {cout << "V2, A3: " << i << " " << j << " " << s << endl; return "s23";}

template <>
struct FunctorTable<FirstVisitor<FunctorTable>, FirstAcceptor> { static Functor<int, int, int, string> f; };
Functor<int, int, int, string> FunctorTable<FirstVisitor<FunctorTable>, FirstAcceptor>::f =
        Functor<int, int, int, string>(&f11);

template <>
struct FunctorTable<FirstVisitor<FunctorTable>, SecondAcceptor> { static Functor<int, int, int, string> f; };
Functor<int, int, int, string> FunctorTable<FirstVisitor<FunctorTable>, SecondAcceptor>::f =
        Functor<int, int, int, string>(&f12);

template <>
struct FunctorTable<FirstVisitor<FunctorTable>, ThirdAcceptor> { static Functor<int, int, int, string> f; };
Functor<int, int, int, string> FunctorTable<FirstVisitor<FunctorTable>, ThirdAcceptor>::f =
        Functor<int, int, int, string>(&f13);

template <>
struct FunctorTable<SecondVisitor<FunctorTable>, FirstAcceptor> { static Functor<string, int, int, string> f; };
Functor<string, int, int, string> FunctorTable<SecondVisitor<FunctorTable>, FirstAcceptor>::f =
        Functor<string, int, int, string>(&f21);

template <>
struct FunctorTable<SecondVisitor<FunctorTable>, SecondAcceptor> { static Functor<string, int, int, string> f; };
Functor<string, int, int, string> FunctorTable<SecondVisitor<FunctorTable>, SecondAcceptor>::f =
        Functor<string, int, int, string>(&f22);

template <>
struct FunctorTable<SecondVisitor<FunctorTable>, ThirdAcceptor> { static Functor<string, int, int, string> f; };
Functor<string, int, int, string> FunctorTable<SecondVisitor<FunctorTable>, ThirdAcceptor>::f =
        Functor<string, int, int, string>(&f23);


#endif //SHAD_FUNCTORTABLESPEC_H
