#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>  //per std::setw() 
#include <fstream> // per std::ofstream 
#include <cstdlib> //per la macro EXIT_SUCCESS 

int main() {
    randfiller rf;
    timecounter tc;

    // Apro file CSV per output 
    std::ofstream csv("times.csv");
    csv << "n,bubble,insertion,selection,merge,quick,std_sort,hybrid\n";

    // Intestazione tabella su stdout
    std::cout << std::scientific << std::setprecision(3);
    std::cout << std::setw(6) << "n"
              << std::setw(14) << "bubble"
              << std::setw(14) << "insertion"
              << std::setw(14) << "selection"
              << std::setw(14) << "merge"
              << std::setw(14) << "quick"
              << std::setw(14) << "std::sort"
              << std::setw(14) << "hybrid" << "\n";

    for (int n = 2; n <= 100; n++) {
        // creo 100 vettori di dimensione n, riempiti casualmente
        std::vector<std::vector<int>> vecs(100, std::vector<int>(n));
        for (auto& v : vecs) {   //ciclo for senza indici, che prende elementi v del contenitore vecs 
            rf.fill(v, -1000, 1000);
        }

        // Copie indipendenti per ogni algoritmo
        auto v_bubble    = vecs;
        auto v_insertion = vecs;
        auto v_selection = vecs;
        auto v_merge     = vecs;
        auto v_quick     = vecs;
        auto v_std       = vecs;
        auto v_hybrid    = vecs;

        tc.tic();
        for (auto& v : v_bubble) bubble_sort(v);
        double t_bubble = tc.toc() / 100.0;

        tc.tic();
        for (auto& v : v_insertion) insertion_sort(v);
        double t_insertion = tc.toc() / 100.0;

        tc.tic();
        for (auto& v : v_selection) selection_sort(v);
        double t_selection = tc.toc() / 100.0;

        tc.tic();
        for (auto& v : v_merge) merge_sort(v);
        double t_merge = tc.toc() / 100.0;

        tc.tic();
        for (auto& v : v_quick) quick_sort(v);
        double t_quick = tc.toc() / 100.0;

        tc.tic();
        for (auto& v : v_std) std::sort(v.begin(), v.end());
        double t_std = tc.toc() / 100.0;

        tc.tic();
        for (auto& v : v_hybrid) quick_sort_hybrid(v);
        double t_hybrid = tc.toc() / 100.0;

        // Output a terminale
        std::cout << std::setw(6) << n
                  << std::setw(14) << t_bubble
                  << std::setw(14) << t_insertion
                  << std::setw(14) << t_selection
                  << std::setw(14) << t_merge
                  << std::setw(14) << t_quick
                  << std::setw(14) << t_std 
                  << std::setw(14) << t_hybrid << "\n";

        // Output su file CSV
        csv << n << ","
            << t_bubble << ","
            << t_insertion << ","
            << t_selection << ","
            << t_merge << ","
            << t_quick << ","
            << t_std << ","
            << t_hybrid << "\n";
    }

    csv.close();
    std::cout << "\nRisultati salvati in times.csv\n";
    return EXIT_SUCCESS;
}