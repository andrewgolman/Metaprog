#include <iostream>
#include <cassert>
#include "factory.h"
#include "typelist.h"
#include "typetable.h"
#include "types.h"

using std::cout;
using std::endl;

int main() {
    using tt = TypeList<
            TypeList<Chair, Table, Sofa>,
            TypeList<WoodenChair, WoodenTable, WoodenSofa>,
            TypeList<MetalChair, MetalTable, MetalSofa>,
            TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>
    >;
    assert((TTRow<Chair, tt>::Res == 0));
    assert((TTRow<Table, tt>::Res == 0));
    assert((TTRow<Sofa, tt>::Res == 0));
    assert((TTRow<WoodenChair, tt>::Res == 1));
    assert((TTRow<MetalRichTable, tt>::Res == 3));
    assert((TTCol<Chair, tt>::Res == 0));
    assert((TTCol<Table, tt>::Res == 1));
    assert((TTCol<Sofa, tt>::Res == 2));
    assert((TTCol<WoodenChair, tt>::Res == 0));
    assert((TTCol<MetalRichTable, tt>::Res == 1));

    using MyFactoryHierarchy = GetAbstractFactory<
        3,
        4,
        TypeList<Chair, Table, Sofa>,
        TypeList<WoodenChair, WoodenTable, WoodenSofa>,
        TypeList<MetalChair, MetalTable, MetalSofa>,
        TypeList<MetalRichChair, MetalRichTable, MetalRichSofa>
    >;
    Factory<MyFactoryHierarchy::TTable>* MyFactory = new MyFactoryHierarchy::GetConcreteFactory<Sofa>::result;
    Root* a = MyFactory->Get<MetalTable>();
}
