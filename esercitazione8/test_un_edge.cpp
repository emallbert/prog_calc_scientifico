#include "un_edge.hpp"

#include <cassert> 


int main() {
    un_edge<int> e1(3, 7);
    un_edge<int> e2(7, 3);  // ordine invertito

    assert(e1.from() == 3 && e1.to() == 7);
    assert(e2.from() == 3 && e2.to() == 7);  // l'invariante li ha riordinati
    assert(e1 == e2);                         // sono lo stesso arco

    un_edge<int> e3(1, 5);
    assert(e3 < e1);                          // (1,5) < (3,7) lessicograficamente

    std::cout << e1 << "\n";                  // stampa "(3, 7)"
    return 0;
}