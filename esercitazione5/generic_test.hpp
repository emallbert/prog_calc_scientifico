#pragma once

#include <vector>
#include <string>
#include <cstdlib>
#include "randfiller.h"
#include "sorts.hpp"

template<typename SortFn> //può prendere in argomento funzioni istanziate, functors cioè lambda, e altri oggetti chiamabili
int run_sort_tests(SortFn sort) { 
    randfiller rf; // instantiate a randfiller

    // test 0: caso limite (vettore vuoto)
    std::vector<int> empty;
    sort(empty);
    if (!is_sorted(empty)) return EXIT_FAILURE; // se ho solo una istruzione nel corpo dell'if posso omettere le graffe

    // lunghezze dei 100 vettori
    std::vector<int> lengths(100);
    rf.fill(lengths, 0, 1000);

    // test 1: 100 vettori di int casuali
    for (int i = 0; i < 100; i++) {
        std::vector<int> vi(lengths[i]);
        rf.fill(vi, -100000, 100000);
        sort(vi);
        if (!is_sorted(vi)) return EXIT_FAILURE;
    }

    // test 2: 100 vettori di float casuali
    for (int i = 0; i < 100; i++) {
        std::vector<float> vf(lengths[i]);
        rf.fill(vf, -100000.0f, 100000.0f);
        sort(vf);
        if (!is_sorted(vf)) return EXIT_FAILURE;
    }

    // test 3: vettore di stringhe
    std::vector<std::string> parole = {
        "pera", "mela", "banana", "kiwi", "uva",
        "fragola", "ananas", "pesca", "ciliegia", "arancia"
    };
    sort(parole);
    if (!is_sorted(parole)) return EXIT_FAILURE;

    // se ancora nessun errore
    return EXIT_SUCCESS;
}