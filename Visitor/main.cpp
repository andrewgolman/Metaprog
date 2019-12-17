#include <iostream>
#include "visitFactory.h"

using std::cout;
using std::endl;
using std::string;

int sum(int a, int b) {
    return a + b;
}

int main() {
    Functor<int, int, int> f(sum);
    cout << f(1, 1.2) << endl;

    auto v1 = FirstVisitor<FunctorTable>();
    auto v2 = SecondVisitor<FunctorTable>();
    auto a2 = SecondAcceptor();
    auto a3 = ThirdAcceptor();

    cout << VisitFactory<
            TypeList<FirstVisitor<FunctorTable>, SecondVisitor<FunctorTable>>,
            TypeList<FirstAcceptor, SecondAcceptor, ThirdAcceptor>,
            int, int, string
    >::Go(&v1, &a2, 1, string("a")) << endl;
    cout << VisitFactory<
            TypeList<FirstVisitor<FunctorTable>, SecondVisitor<FunctorTable>>,
            TypeList<FirstAcceptor, SecondAcceptor, ThirdAcceptor>,
            string, int, string
    >::Go(&v2, &a3, 2, string("b")) << endl;
}
