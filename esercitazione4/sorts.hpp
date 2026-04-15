#pragma once //altrimenti #ifndef SORTS_HPP, #define SORTS_HPP, #endif
             //serve a non includere più volte lo stesso file .hpp nel main cosa che darebbe problemi
#include <vector>
#include <utility> // std::swap
#include <cstddef> // std::size_t (in realtà già disponibie grazie a vector che lo usa intenramente, ma buona pratica includere tutte le librerie originali)

//is sorted
template<typename T>
bool is_sorted(const std::vector<T>& vec) {
    for (std::size_t i = 0; i + 1 < vec.size(); i++) {
        if (vec[i+1] < vec[i]) return false;
    }
    return true;
}

//bubblesort (dimostrazione funzionamento per induzione su 2 invarianti dei due cicli for)
template<typename T>
void bubble_sort(std::vector<T>& vec) {
    if (vec.size() < 2) return;  // niente da ordinare
    for (std::size_t i = 0; i + 1 < vec.size(); i++) { //uso std::size_t perchè è il tpo che mi viene restituito dal metodo size() e non int, poi confrontandoli mi darebbe un flag
        for (std::size_t j = vec.size() - 1; j > i; j--) { //attenzione a sottrarre a vec.size() che non ha i negativi essendo std::size_t
            if (vec[j] < vec[j-1]) {
                std::swap(vec[j], vec[j-1]);
            }
        }
    }
}

//insertionsort (due nuovi invarianti uno esterno uno interno un po' più complicati)
template<typename T> //non uso swap perche sono 3*k operazioni ivece che k+1, e poi sennò sarebbe tipo bubblesort ma con un ordine di scansione diverso
void insertion_sort(std::vector<T>& vec) {
    if (vec.size() < 2) return;
    for (std::size_t j = 1; j < vec.size(); j++) {
        T key = vec[j];
        std::size_t i = j; //cambio l'indicizzazione di 1 così posso usare per i std::size_t (che è sempre >= 0) usando un > 0, ed evitare altri tipi diversi da j
        while (i > 0 && vec[i-1] > key) {
            vec[i] = vec[i-1];
            i = i - 1;
        }
        vec[i] = key;
    }
}

//selectionsort (più o meno gli stessi 2 invarianti di bubblesort)
template<typename T> //
void selection_sort(std::vector<T>& vec) {
    if (vec.size() < 2) return;
    for (std::size_t i = 0; i + 1 < vec.size(); i++) {
        std::size_t min = i;
        for (std::size_t j = i + 1; j < vec.size(); j++) {
            if (vec[j] < vec[min]) {
                min = j;
            }
        }
        std::swap(vec[i], vec[min]);
    }
}