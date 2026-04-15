#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip> //per std::setw()
#include <cstdlib> //per la macro EXIT_SUCCESS

int main() {
    randfiller rf;
    timecounter tc;

    // Intestazione della tabella
    //std::cout << "n\tbubble\t\tinsertion\tselection\tstd::sort\n"; //visto su claude \t mi sposta di un tab a destra \n è newline
    //versione migliore con lo spazio riservato specificato:
    std::cout << std::setw(8) << "n"
            << std::setw(15) << "bubble"
            << std::setw(15) << "insertion"
            << std::setw(15) << "selection"
            << std::setw(15) << "std::sort"
            << "\n";

    for (int i = 2; i <= 13; i++) {
        std::size_t n = 1 << i; //questa sintassi mi da 2^i
        std::vector<int> v(n);
        rf.fill(v, -100000, 100000);

        auto v_bubble    = v; //creo delle copie, auto copia il tipo a destra   
        auto v_insertion = v;
        auto v_selection = v;
        auto v_std       = v;

        tc.tic();
        bubble_sort(v_bubble);
        double t_bubble = tc.toc();

        tc.tic();
        insertion_sort(v_insertion);
        double t_insertion = tc.toc();

        tc.tic();
        selection_sort(v_selection);
        double t_selection = tc.toc();

        tc.tic();
        std::sort(v_std.begin(), v_std.end());
        double t_std = tc.toc();

        std::cout << std::setw(8) << n
                << std::setw(15) << t_bubble
                << std::setw(15) << t_insertion
                << std::setw(15) << t_selection
                << std::setw(15) << t_std
                << "\n";

    }

    return EXIT_SUCCESS;
}