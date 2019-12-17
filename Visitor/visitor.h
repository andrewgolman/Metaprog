#ifndef SHAD_VISITOR_H
#define SHAD_VISITOR_H

#pragma once

#include <iostream>
#include "typelist.h"
#include "root.h"
#include "functor.h"
#include "acceptor.h"
#include "utils.h"

using std::cout;
using std::endl;
using std::string;


template <template <typename, typename> typename FuncTable>
class FirstVisitor : public Visitor {
    // Результат выполнения функтора сохраняется в визиторе и далее извлекается внутри Go.
    int res;
public:
    using ReturnType = int;
    void Visit(FirstAcceptor*, int a, int b, const string& c) override {
        res = FuncTable<FirstVisitor, FirstAcceptor>::f(a, b, c);
    }
    void Visit(SecondAcceptor*, int a, int b, const string& c) override {
        res = FuncTable<FirstVisitor, SecondAcceptor>::f(a, b, c);
    }
    void Visit(ThirdAcceptor*, int a, int b, const string& c) override {
        res = FuncTable<FirstVisitor, ThirdAcceptor>::f(a, b, c);
    }
    int Res() {
        return res;
    };
};

template <template <typename, typename> typename FuncTable>
class SecondVisitor : public Visitor {
    string res;
public:
    using ReturnType = string;
    void Visit(FirstAcceptor*, int a, int b, const string& c) override {
        res = FuncTable<SecondVisitor, FirstAcceptor>::f(a, b, c);
    }
    void Visit(SecondAcceptor*, int a, int b, const string& c) override {
        res = FuncTable<SecondVisitor, SecondAcceptor>::f(a, b, c);
    }
    void Visit(ThirdAcceptor*, int a, int b, const string& c) override {
        res = FuncTable<SecondVisitor, ThirdAcceptor>::f(a, b, c);
    }
    string Res() {
        return res;
    };
};


#endif //SHAD_VISITOR_H
