#pragma once

#include "un_edge.hpp"

#include<map>
#include<set>
#include<vector>
#include<algorithm> //per lower_bound
#include<stdexcept> //per out_of_range
#include<iterator> //per back_inserter

//grafo semplice: non più di 1 arco per stessi nodi, archi non pesati

template<typename N>
class un_graph {
    private:
        std::map<N, std::set<N>> adj_; //potrei anche come secondo argomento passare gli archi, ma sarebbe ridondante perchè il nodo from_ è sempre lo stesso cioè la chiave, quindi scelgo di rappresentare qualcosa di simile a una matrice di adiacenza
        std::vector<un_edge<N>> edges_;   //contenitore per la numerazione degli archi secondo la relazione < definita su un_edge, il vector è veloce per le query ma meno veloce di un set per gli insert
        //inoltre sarebbe ancora più veloce usare una numerazione per ordine di inserimento
    public:
        //costruttore di default: inizializza tutti i membri con a loro volta il costruttore di default di ciascuno, in particolare li inizializza vuoti
        un_graph() = default; //altrimenti posso esplicitare i membri con un_graph() : adj_(), edges_() {} (utile se volessi inizializzare ciasuno in modo particolare)

        //costruttore copia
        un_graph(const un_graph& other) //qua uso l'altra sintassi perchè è più chiaro cosa viene fatto, ma potrei anche qua usare = default;
            : adj_(other.adj_),  //posso usare l'accesso diretto ai membri di other 
            edges_(other.edges_)
        {}
        
        //metodo neighbours
        std::set<N> neighbours(const N& n) const {
            auto it = adj_.find(n); //find è un metodo di map che mi restituisce un iteratore che può puntare o a un pair (chiave=n, valore) oppure a adj_.end(); a differenza di altri metodi su map se gli passo un nodo non esistente non mi da errori 
            if (it == adj_.end()) { //verifico se l'iteratore it punta al valore sentinella
                return {}; //mi ritorna un oggetto del tipo dichiarato all'inizio ma vuoto
            }
            else return it->second; //equivalente a (*it).second
        }   

        //metodo add_edge
        bool add_edge(const N& a, const N& b) {
            un_edge<N> e(a, b);
            //aggiungo l'arco al vector che li enumera: uso il metodo lower_bound che mi da l'iteratore i al primo elemento t.c. *i < e is false (ovviamente il vettore deve già essere ordinato)
            auto it = std::lower_bound(edges_.begin(), edges_.end(), e);
            if (it != edges_.end() && *it == e) return false; //già presente 
            else edges_.insert(it, e); //inserisce e nella posizione precedente a it

            //aggiungo i nodi alla "matrice di adiacenza"
            //uso l'operatore [] sulla mappa che mi da il valore associato alla chiave oppure se la chiave è nuova crea la chiave con un valore vuoto
            //e il metodo insert() che aggiunge a set (se non esistente) un valore e mi restituisce un pair di iteratore che punta al valore e di bool se il valore esisteva già
            adj_[a].insert(b);
            adj_[b].insert(a);
            return true;
        }

        //add_edge se passi direttamente un arco
        bool add_edge(const un_edge<N>& e) {
            auto a = e.from();
            auto b = e.to();
            return add_edge(a, b);
        }

        //metodo all_edges
        const std::vector<un_edge<N>>& all_edges() const { //ritorno un riferimento costante, una copia sarebbe costosa
            return edges_; //già ordinato
        }

        //metodo all_nodes 
        std::vector<N> all_nodes() const {
            std::vector<N> result;
            result.reserve(adj_.size()); //questo mi risparmia il dover riallocare memoria ogni volta che aggiungo qualcosa 
            for (const auto& [node, neighbours] : adj_) { //prendo da adj_ nell'ordine che ha automaticamente imposto sulle chiavi 
                result.push_back(node);
            }
            return result;
        }

        //metodo edge_number
        int edge_number(const un_edge<N>& e) const {
            auto it = std::lower_bound(edges_.begin(), edges_.end(), e);
            if (it == edges_.end() || !(*it == e)) {
                throw std::out_of_range("edge not in graph"); //errore se l'arco non esiste
            }
            else return std::distance(edges_.begin(), it);
        }

        //edge_number se passi una coppia di nodi
        int edge_number(const N& a, const N& b) const {
            return edge_number(un_edge<N>(a, b));
        }

        //metodo edge_at
        un_edge<N> edge_at(int n) const {
            return edges_.at(n); //il metodo at mi da errore se n è aut of range come per edge_number
        }

};

//ho usato Claude
//funzione libera per simmetria dell'operatore ma si poteva scrivere anche dentro alla classe
template<typename N>
un_graph<N> operator-(const un_graph<N>& g1, const un_graph<N>& g2) {
    const auto& edges_1 = g1.all_edges();
    const auto& edges_2 = g2.all_edges();

    std::vector<un_edge<N>> diff;
    std::set_difference( //dati due range ordinati calcola la differenza insiemistica e fornisce un output iterator
        edges_1.begin(), edges_1.end(),
        edges_2.begin(), edges_2.end(),
        std::back_inserter(diff) //a ogni dereferenziazione dell'output iterator dentro set_difference esegue un push_back su diff
    );

    un_graph<N> result;
    for (const auto& e : diff) {
        result.add_edge(e);
    }
    return result;
};