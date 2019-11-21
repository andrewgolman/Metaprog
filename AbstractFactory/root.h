#ifndef SHAD_ROOT_H
#define SHAD_ROOT_H

#include <iostream>

// Базовый класс для всех типов. Его нужно знать и типам, и фабрике (для возвращаемого типа).
struct Root {
    Root() {
        std::cout << "ROOT" << std::endl;
    }
};

#endif //SHAD_ROOT_H
