#ifndef SHAD_ACCEPTOR_H
#define SHAD_ACCEPTOR_H

#pragma once

#include <iostream>
#include "root.h"
#include "visitor.h"

using std::cout;
using std::endl;

class FirstAcceptor : public Acceptor {
    void Accept(Visitor* v, int a, const string& b) override {
        cout << "Accept 1" << endl;
        v->Visit(this, 1, a, b);
    }
};

class SecondAcceptor : public Acceptor {
    void Accept(Visitor* v, int a, const string& b) override {
        cout << "Accept 2" << endl;
        v->Visit(this, 2, a, b);
    }
};

class ThirdAcceptor : public Acceptor {
    void Accept(Visitor* v, int a, const string& b) override {
        cout << "Accept 3" << endl;
        v->Visit(this, 3, a, b);
    }
};


#endif //SHAD_ACCEPTOR_H
