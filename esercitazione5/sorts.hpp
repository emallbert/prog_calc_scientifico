#pragma once //altrimenti #ifndef SORTS_HPP, #define SORTS_HPP, #endif
             //serve a non includere più volte lo stesso file .hpp nel main cosa che darebbe problemi
#include <vector>
#include <utility> // std::swap
#include <cstddef> // std::size_t (in realtà già disponibie grazie a vector che lo usa intenramente, ma buona pratica includere tutte le librerie originali)
#include<cmath> 

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
    for (std::size_t i = 0; i + 1 < vec.size(); i++) { //uso std::size_t perchè è il tipo che mi viene restituito dal metodo size() e non int, poi confrontandoli mi darebbe un flag
        for (std::size_t j = vec.size() - 1; j > i; j--) { //attenzione a sottrarre a vec.size() che non ha i negativi essendo std::size_t
            if (vec[j] < vec[j-1]) {
                std::swap(vec[j], vec[j-1]);
            }
        }
    }
}

//insertionsort (due nuovi invarianti uno esterno uno interno un po' più complicati)
template<typename T> //non uso swap perche sono 3*k operazioni invece che k+1, e poi sennò sarebbe tipo bubblesort ma con un ordine di scansione diverso
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

//merge (dichiarata prima di mergesort altrimenti il compilatore mi dice che non è definita)
template<typename T>
void merge(std::vector<T>& vec, int p, int q, int r) {
    int n1 = q-p+1;
    int n2 = r-q;
    std::vector<T> L(n1); //evito di mettere +inf come sentinella perchè per i tipi stringa è complicato
    std::vector<T> R(n2);
    for (int i = 0; i < n1 ; i++) {
        L[i] = vec[p+i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = vec[q+1+j];
    }
    int i = 0, j = 0, k = p; //se dichiaro oggetti dello stesso tipo lo posso fare sulla stessa riga
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { //svuoto L se restano elementi
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) { //svuoto R se restano elementi
        vec[k] = R[j];
        j++;
        k++;
    }
}

//mergesort funzionamento alberi sinistro e destro (vedere dim e tempo)
template<typename T>
void merge_sort(std::vector<T>& vec, int p, int r) { //casino sui tipi int confrontati con type T, produce dei warning
    if (p < r) {
        int q = (p + r) / 2; //non serve usare floor perche richiedere che q sia int mi fa arrotondare per troncamento automaticamente 
        merge_sort(vec, p, q);
        merge_sort(vec, q + 1, r);
        merge(vec, p, q, r);
    }
}

//chiamo questa quando non aggiungo parametri 
template<typename T>
void merge_sort(std::vector<T>& vec) {
    if (!vec.empty())
        merge_sort(vec, 0, static_cast<int>(vec.size()) - 1);
}

//partition dimostrare funzionamento e tempi
template<typename T>
int partition(std::vector<T>& vec, int p, int r) {
    T x = vec[r];
    int i = p-1;
    for (int j = p; j < r; j++) {
        if (vec[j] <= x) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i+1], vec[r]);
    return i+1;
}

//quicksort dimostrare funzionamento e tempi
template<typename T>
void quick_sort(std::vector<T>& vec, int p, int r) {
    if (p < r) {
        int q = partition(vec, p, r);
        quick_sort(vec, p, q-1);
        quick_sort(vec, q+1, r);
    }
}

//senza parametri
template<typename T>
void quick_sort(std::vector<T>& vec) {
    if (!vec.empty())
        quick_sort(vec, 0, static_cast<int>(vec.size()) - 1);
}

//insertionsort modificato per il quicksort ibrido
template<typename T>
void insertion_sort(std::vector<T>& vec, int p, int r) { //parametri in più per usarlo su porzioni ridotte dell'array
    for (int j = p + 1; j <= r; j++) { //uso degli interi come in quicksort
        T key = vec[j];
        int i = j;
        while (i > p && vec[i-1] > key) {
            vec[i] = vec[i-1];
            i--;
        }
        vec[i] = key;
    }
}

//quicksort ibrido
template<typename T>
void quick_sort_hybrid(std::vector<T>& vec, int p, int r, int soglia) {
    if (p < r) {
        if (r - p + 1 < soglia) { //ogni volta che la finestra è minore della soglia uso insertionsort
            insertion_sort(vec, p, r);
        } else {
            int q = partition(vec, p, r);
            quick_sort_hybrid(vec, p, q - 1, soglia);
            quick_sort_hybrid(vec, q + 1, r, soglia);
        }
    }
}

template<typename T>
void quick_sort_hybrid(std::vector<T>& vec, int soglia = 40) {
    if (!vec.empty())
        quick_sort_hybrid(vec, 0, static_cast<int>(vec.size()) - 1, soglia);
}