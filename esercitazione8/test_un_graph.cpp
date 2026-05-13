#include "un_graph.hpp"

#include <iostream>
#include <cstdlib>
#include <stdexcept>

void stampa_grafo(const un_graph<int>& grafo) {
    std::cout << "nodi: ";
    for (const auto& nodo : grafo.all_nodes()) {
        std::cout << nodo << " ";
    }
    std::cout << "\nnumero archi: " << grafo.all_edges().size() << "\n";
    for (const auto& arco : grafo.all_edges()) {
        std::cout << "  " << arco.from() << " --- " << arco.to() << "\n";
    }
    std::cout << "\n";
}

int main() {
    try {
        // Costruisco il grafo aggiungendo gli archi uno per uno
        un_graph<int> grafo;
        grafo.add_edge(1, 3);
        grafo.add_edge(1, 4);
        grafo.add_edge(1, 5);
        grafo.add_edge(3, 5);
        grafo.add_edge(4, 6);
        grafo.add_edge(4, 7);
        grafo.add_edge(5, 11);
        grafo.add_edge(6, 11);

        stampa_grafo(grafo);

        // Test di neighbours
        std::cout << "Vicini del nodo 4: ";
        for (const auto& vicino : grafo.neighbours(4)) {
            std::cout << vicino << " ";
        }
        std::cout << "\n";

        // Test su un nodo non presente (dovrebbe stampare vuoto, non lanciare)
        std::cout << "Vicini del nodo 99 (inesistente): ";
        for (const auto& vicino : grafo.neighbours(99)) {
            std::cout << vicino << " ";
        }
        std::cout << "[fine]\n\n";

        // Aggiunta di un arco
        bool aggiunto = grafo.add_edge(11, 3);
        std::cout << "Aggiunto arco 3-11? " << std::boolalpha << aggiunto << "\n";

        // Riprovo ad aggiungerlo: deve restituire false
        bool riaggiunto = grafo.add_edge(3, 11);
        std::cout << "Riaggiunto arco 3-11? " << riaggiunto << " (atteso false)\n\n";

        stampa_grafo(grafo);

        // Test di edge_number / edge_at
        un_edge<int> arco_35(3, 5);
        std::cout << "Posizione dell'arco 3-5: " << grafo.edge_number(arco_35) << "\n";
        std::cout << "Arco in posizione 6: " << grafo.edge_at(6) << "\n\n";

        // Test del costruttore di copia
        un_graph<int> copia(grafo);
        copia.add_edge(100, 200);
        std::cout << "Archi nell'originale dopo modifica della copia: "
                  << grafo.all_edges().size() << "\n";
        std::cout << "Archi nella copia: "
                  << copia.all_edges().size() << "\n\n";

        // Test di operator-
        un_graph<int> piccolo;
        piccolo.add_edge(1, 3);
        piccolo.add_edge(1, 5);
        un_graph<int> diff = grafo - piccolo;
        std::cout << "Differenza grafo - piccolo:\n";
        stampa_grafo(diff);

        // Test che edge_number su un arco assente lanci eccezione
        try {
            grafo.edge_number(un_edge<int>(99, 100));
            std::cout << "ERRORE: avrebbe dovuto lanciare\n";
        } catch (const std::out_of_range& ex) {
            std::cout << "Eccezione attesa per edge_number su arco assente: "
                      << ex.what() << "\n";
        }

        // Test che edge_at su indice out-of-range lanci eccezione
        try {
            grafo.edge_at(999);
            std::cout << "ERRORE: avrebbe dovuto lanciare\n";
        } catch (const std::out_of_range& ex) {
            std::cout << "Eccezione attesa per edge_at fuori range: "
                      << ex.what() << "\n";
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex) {
        std::cerr << "Errore non atteso: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Errore sconosciuto\n";
        return EXIT_FAILURE;
    }
}