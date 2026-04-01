#include <iostream>
#include <concepts>
#include <cmath> // Necessario per std::abs
//#include <numeric> Necessario per std::gcd, poi al limite non lo uso
template<typename I> requires std::integral<I> 
class rational { 
    private:
        I num_;
        I den_;
    public:
        //costruttore di default
        rational() : num_(I{0}), den_(I{1}) {}

        //funzioone simpify
        void simplify() {
            // Se è NaN (0/0), non c'è nulla da semplificare
            if (num_ == 0 && den_ == 0) return;
            // Se è Inf (X/0), lo normalizzo a 1/0
            if (den_ == 0) { 
                num_ = 1; 
                return; 
            }
            if (num_ == 0) {
                den_ = 1; // Normalizzo lo zero a 0/1
                return;
            }
            // Calcolo il Massimo Comune Divisore
            //I comune_divisore = std::gcd(num_, den_); non usato
            //Uso i valori assoluti per l'algoritmo di Euclide! ho usato gemini qua
            I A = std::abs(num_);
            I B = std::abs(den_);
            //Algoritmo di Euclide
            while (B != 0) {
                I r = A % B;
                A = B;
                B = r;
            }
            // Al termine del ciclo, 'A' contiene l'MCD assoluto
            num_ = num_ / A;
            den_ = den_ / A;   
            //aggiusto i segni (lo voglio al numeratore)
            if (den_ < 0) {
            num_ = -num_;
            den_ = -den_;
            }
        }

        //costruttore user defined
        rational(const I& px, const I& py) {
            num_ = px;
            den_ = py;
            simplify();
        } //eliminato i casi uguali

        //metodo per restituire il razionale
        I num() const { return num_; } 
        I den() const { return den_; }

        //operazioni (ci sono molti casi particolari in cui l'algebra funzionerebbe da sola, ma li aggiungo per chiarezza)
        //somma +=
        rational& operator+= (const rational& other) {
            if((num_ == 0 && den_ == 0) || (other.num()== 0 && other.den() == 0))
            {
                num_ = 0; den_ = 0;
            }
            else if((num_ != 0 && den_ == 0) || (other.num() !=0 && other.den() ==0))
            {
                num_ = 1; den_ = 0;
            }
            else {
            num_ = (num_ * other.den()) + (other.num() * den_);
            den_ = den_ * other.den();
            simplify();
            }
            return *this; //this è un puntatore creato in automatico dal metodo che punta all'output, io ne voglio il valore quindi uso l'asterisco
        }

        //somma
        rational operator+(const rational& other) const {
            rational ret = *this;
            ret += other; 
            return ret;
        }

        // sottrazione -=
        rational& operator-=(const rational& other) {
            if ((num_ == 0 && den_ == 0) || (other.num() == 0 && other.den() == 0)) {
                num_ = 0; den_ = 0;
            }
            // Se sono entrambi Inf, Inf - Inf = NaN
            else if (den_ == 0 && other.den() == 0) {
                num_ = 0; den_ = 0;
            }
            else if (den_ == 0 || other.den() == 0) {
                num_ = 1; den_ = 0; // Uno solo dei due è Inf
            }
            else {
                num_ = (num_ * other.den()) - (other.num() * den_);
                den_ = den_ * other.den();
                simplify();
            }
            return *this;
        }

        // sottrazione
        rational operator-(const rational& other) const {
            rational ret = *this;
            ret -= other;
            return ret;
        }

        // moltiplicazione *=
        rational& operator*=(const rational& other) {
            if ((num_ == 0 && den_ == 0) || (other.num() == 0 && other.den() == 0)) {
                num_ = 0; den_ = 0;
            }
            //non aggiungo casi particolari per l'inf perchè si correggono da soli (anche 0*inf=Nan funziona)
            else {
                num_ = num_ * other.num();
                den_ = den_ * other.den();
                simplify();
            }
            return *this;
        }

        // moltiplicazione
        rational operator*(const rational& other) const {
            rational ret = *this;
            ret *= other;
            return ret;
        }

        // divisione /=
        rational& operator/=(const rational& other) {
            if ((num_ == 0 && den_ == 0) || (other.num() == 0 && other.den() == 0)) {
                num_ = 0; den_ = 0;
            }
            //tutti i casi particolari con l'inf o con la divisione per zero sono coperti dal seguente
            else {
                num_ = num_ * other.den();
                den_ = den_ * other.num();
                simplify();
            }
            return *this;
        }

        // divisione
        rational operator/(const rational& other) const {
            rational ret = *this;
            ret /= other;
            return ret;
        }

};

//ostream operator
template<typename I> requires std::integral<I>
std::ostream& operator<<(std::ostream& os, const rational<I>& r) {
    if (r.den() == 0) {
        if(r.num() == 0) {
            os << "NaN";
        }
        else {
            os << "Inf";                 
        }
    }
    else if (r.den() == 1) { 
        os << r.num(); //stampo di un intero se den == 1
    }
    else {
        os << r.num() << "/" << r.den();    
    }
    return os;
};