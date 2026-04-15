#include <vector>
#include <string>
#include <cstdlib> //serve per EXIT_SUCCESS e EXIT_FAILURE
#include "randfiller.h"
#include "sorts.hpp"

int main() {
    randfiller rf; // instantiate a randfiller

    //test 0: casi limite
    std::vector<int> empty;
    insertion_sort(empty);
    if (!is_sorted(empty)) {return EXIT_FAILURE;}

    //lunghezze dei 100 vettori
    std::vector<int> lengths; //vettore delle lunghezze dei miei vettori
    lengths.resize(100);
    rf.fill(lengths, 0, 1000);

    //test 1 su 100 vettori di interi casuali
    for (int i=0; i<100; i++) {
        std::vector<int> vi;
        vi.resize(lengths[i]);
        rf.fill(vi, -100000, 100000);
        insertion_sort(vi);
        if (!is_sorted(vi)) {
            return EXIT_FAILURE;
        }
    }

    //test 2 su 100 vettori di float casuali
    for (int i=0; i<100; i++) {
        std::vector<float> vf;
        vf.resize(lengths[i]);
        rf.fill(vf, -100000.0f, 100000.0f);
        insertion_sort(vf);
        if (!is_sorted(vf)) {
            return EXIT_FAILURE;
        }
    }

    //test 3 vettore di stringhe scelte a piacere
    std::vector<std::string> parole = {
        "pera", "mela", "banana", "kiwi", "uva",
        "fragola", "ananas", "pesca", "ciliegia", "arancia"
    };
    insertion_sort(parole);
    if (!is_sorted(parole)) {
        return EXIT_FAILURE;
    }

    //se ancora nessun errore
    return EXIT_SUCCESS;
}