#include "root.h"

struct Chair : public Root {
    Chair() {
        std::cout << "Chair" << std::endl;
    }
};

struct Table : public Root {
    Table() {
        std::cout << "Table" << std::endl;
    }
};

struct Sofa : public Root {
    Sofa() {
        std::cout << "Sofa" << std::endl;
    }
};

struct WoodenChair : public Chair {
    WoodenChair() {
        std::cout << "WoodenChair" << std::endl;
    }
};
struct WoodenTable : public Table {
    WoodenTable() {
        std::cout << "WoodenTable" << std::endl;
    }
};
struct WoodenSofa : public Sofa {
    WoodenSofa() {
        std::cout << "WoodenSofa" << std::endl;
    }
};

struct MetalChair : public Chair {
    MetalChair() {
        std::cout << "MetalChair" << std::endl;
    }
};

struct MetalTable : public Table {
    MetalTable() {
        std::cout << "MetalTable" << std::endl;
    }
};
struct MetalSofa : public Sofa {
    MetalSofa() {
        std::cout << "MetalSofa" << std::endl;
    }
};
struct MetalRichChair : public Chair {
    MetalRichChair() {
        std::cout << "MetalRichChair" << std::endl;
    }
};
struct MetalRichTable : public Table {
    MetalRichTable() {
        std::cout << "MetalRichTable" << std::endl;
    }
};
struct MetalRichSofa : public Sofa {
    MetalRichSofa() {
        std::cout << "MetalRichSofa" << std::endl;
    }
};
