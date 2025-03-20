#include <iostream>
#include <cstring>
enum tipasigurare { VIATA, CASA, SANATATE, AUTO };
using namespace std;

class Asigurare {
private:
    char* numeAsigurat;
    double sumaAsigurata;
    tipasigurare tipAsigurare;
    int durataAsigurare; // în luni
    double cursSchimb;

    static double taxa; // membru static 

public:
    // Constructor fără parametri
    Asigurare() {
        numeAsigurat = new char[20];
        strcpy_s(numeAsigurat, 20, "Melnic Ionut");
        sumaAsigurata = 1500;
        tipAsigurare = SANATATE;
        durataAsigurare = 6;
        cursSchimb = 4.9;
    }


    // Constructor cu parametri
    Asigurare(const char* numeAsigurat, double sumaAsigurata, tipasigurare tipAsigurare, int durataAsigurare, double cursSchimb) {
        this->numeAsigurat = new char[strlen(numeAsigurat) + 1];
        strcpy_s(this->numeAsigurat, strlen(numeAsigurat) + 1, numeAsigurat);
        this->sumaAsigurata = sumaAsigurata;
        this->tipAsigurare = tipAsigurare;
        this->durataAsigurare = durataAsigurare;
        this->cursSchimb = cursSchimb;
    }

    // Constructor de copiere
    Asigurare(const Asigurare& a) {
        numeAsigurat = new char[strlen(a.numeAsigurat) + 1];
        strcpy_s(numeAsigurat, strlen(a.numeAsigurat) + 1, a.numeAsigurat);
        sumaAsigurata = a.sumaAsigurata;
        tipAsigurare = a.tipAsigurare;
        durataAsigurare = a.durataAsigurare;
        cursSchimb = a.cursSchimb;
    }

    // Destructor
    ~Asigurare() {
        delete[] numeAsigurat;
    }

    // Getteri
    char* getNumeAsigurat() {
        return numeAsigurat;
    }
    double getSumaAsigurata() {
        return sumaAsigurata;
    }
    tipasigurare gettipAsigurare() {
        return tipAsigurare;
    }
    int getDurataAsigurare() {
        return durataAsigurare;
    }
    double getCursSchimb() {
        return cursSchimb;
    }

    // Setteri
    void setNumeAsigurat(const char* numenou) {
        delete[] numeAsigurat;
        numeAsigurat = new char[strlen(numenou) + 1];
        strcpy_s(numeAsigurat, strlen(numenou) + 1, numenou);
    }

    void setSumaAsigurata(double sumanoua) {
        sumaAsigurata = sumanoua;
    }
    void setTipAsigurare(tipasigurare tipnou) {
        tipAsigurare = tipnou;
    }
    void setDurataAsigurare(int duratanoua) { durataAsigurare = duratanoua; }
    void setCursSchimb(double cursnou) { cursSchimb = cursnou; }

    // Setter pentru static
    static void setTaxa(double taxanoua) {
        taxa = taxanoua;
    }

    // Funcție de afișare
    void afisare() {
        if (numeAsigurat != nullptr) {
            cout << "Nume Asigurat: " << numeAsigurat << endl;
        }
        cout << "Suma Asigurata(euro): " << sumaAsigurata << endl;
        cout << "Tip Asigurare: " << tipAsigurare << endl;
        cout << "Durata Asigurare: " << durataAsigurare << " luni" << endl;
        cout << "Taxa aplicata: " << taxa << endl;
    }

    // Funcție pentru calcul valoare asigurare într-o altă valută
    double operatorulfunctie() {
        return sumaAsigurata * cursSchimb;
    }
};

// Inițializare camp static static
double Asigurare::taxa = 0.03; // exemplul pe care l-am ales 

int main() {
    Asigurare a1;
    a1.afisare();
    cout << a1.getNumeAsigurat() << endl;

    cout << "=====================" << endl;

    Asigurare a2("Ion Popescu", 10000, AUTO, 24, 4.6);
    a2.afisare();
    cout << "Valoare in RON: " << a2.operatorulfunctie() << endl;

    cout << "=======================" << endl;

    Asigurare a3(a2);
    a3.setCursSchimb(20.2);
    cout << "Valoare in LEI MD: " << a3.operatorulfunctie() << endl;


    return 0;
}

