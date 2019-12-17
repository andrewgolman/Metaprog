//
// Базовые классы для визиторов и аксепторов, а также конкретные аксепторы (нужны визиторам).
//

#ifndef SHAD_ROOT_H
#define SHAD_ROOT_H
#pragma once

using std::string;

class Visitor;

class Acceptor {
public:
    virtual void Accept(Visitor* v, int a, const string& b) = 0;
};

class FirstAcceptor;
class SecondAcceptor;
class ThirdAcceptor;

class Visitor {
public:
    virtual void Visit (FirstAcceptor* acceptor, int a, int b, const string& c) {}
    virtual void Visit (SecondAcceptor* acceptor, int a, int b, const string& c) {}
    virtual void Visit (ThirdAcceptor* acceptor, int a, int b, const string& c) {}
};

#endif //SHAD_ROOT_H
