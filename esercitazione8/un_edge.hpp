#pragma once

#include<iostream>

template<typename N> //N stands for node
class un_edge {
    private:
        N from_;
        N to_;
    public:
        //costruttore user defined
        un_edge(const N& a, const N& b) {
            if (a < b) {
                from_ = a;
                to_ = b;
            }
            else { //riordino
                from_ = b;
                to_ = a;
            }
        }

        //metodi per ottenedere i nodi dell'arco
        const N& from() const {return from_; } //prendo un riferimento costante non una copia (meglio per tipi costosi)
        const N& to() const {return to_; }

        //operatore di confronto stretto (lessicografico) tra archi
        bool operator<(const un_edge& other) const { //non serve controllo dei tipi perchè in C++ avviene durante la compilazione, non a runtime (che è quando il controllo scritto qui mi darebbe errore), se i tipi sono diversi già in compilazione me ne accorgo
            if (from_ != other.from()) return from_ < other.from(); //potrei anche usare other.from_ (questo non è possibile nel main perchè le variabili from_ e to_ sono private, ma nella definizione di un metodo della classe posso accedervi) 
            else return to_ < other.to(); //other.from_ è un accesso più diretto mentre other.from() deve andare a trovare il codice della classe dove ho definito il metodo from()
        }

        //operatore di confronto ==
        bool operator==(const un_edge& other) const {
            return (from_ == other.from() && to_ == other.to());
        }
};

//funzione libera ossia operatore definito con membro di sinistra non this ma qualche membro di una classe non mia (in questo caso classe della libreria standard: std::ostream) dunque non posso tenerlo dentro alla mia classe dove i membri di sinistra sono sempre automaticamente  this
//qua quindi devo esplicitare due parametri
template<typename N>
std::ostream& operator<<(std::ostream& os, const un_edge<N>& e) { // prendo un riferimento non costante a os, modifico os e lo returno; invece il riferimento a un_edge deve essere istanziato con <N> perchè non essendo più all'interno della classe siamo fuori dallo scope
    os << "(" << e.from() << ", " << e.to() << ")"; //qua mi darebbe errore se usassi e.from_ perchè non vi ho accesso 
    return os;
}
