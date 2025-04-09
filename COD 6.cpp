
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Asigurare {
private:
    char* numeAsigurat;
    double sumaAsigurata;
    char* tipAsigurare;
    int durataAni;
    const int idAsigurare;
    static int contorAsigurari;

public:

    Asigurare() : idAsigurare(contorAsigurari++) {
        numeAsigurat = nullptr;
        tipAsigurare = nullptr;
        sumaAsigurata = 0.0;
        durataAni = 0;
    }

    Asigurare(const char* nume, double suma, const char* tip, int durata) : idAsigurare(contorAsigurari++) {
        numeAsigurat = new char[strlen(nume) + 1];
        strcpy(numeAsigurat, nume);
        tipAsigurare = new char[strlen(tip) + 1];
        strcpy(tipAsigurare, tip);
        sumaAsigurata = suma;
        durataAni = durata;
    }


    Asigurare(const Asigurare& a) : idAsigurare(contorAsigurari++) {
        numeAsigurat = new char[strlen(a.numeAsigurat) + 1];
        strcpy(numeAsigurat, a.numeAsigurat);
        tipAsigurare = new char[strlen(a.tipAsigurare) + 1];
        strcpy(tipAsigurare, a.tipAsigurare);
        sumaAsigurata = a.sumaAsigurata;
        durataAni = a.durataAni;
    }


    Asigurare& operator=(const Asigurare& a) {
        if (this != &a) {
            delete[] numeAsigurat;
            delete[] tipAsigurare;

            numeAsigurat = new char[strlen(a.numeAsigurat) + 1];
            strcpy(numeAsigurat, a.numeAsigurat);
            tipAsigurare = new char[strlen(a.tipAsigurare) + 1];
            strcpy(tipAsigurare, a.tipAsigurare);
            sumaAsigurata = a.sumaAsigurata;
            durataAni = a.durataAni;
        }
        return *this;
    }


    ~Asigurare() {
        delete[] numeAsigurat;
        delete[] tipAsigurare;
    }


    double operator()(double cursSchimb) const {
        return sumaAsigurata / cursSchimb;
    }

    // Operator de conversie la double
    operator double() const {
        return sumaAsigurata;
    }

    // Metode de acces
    const char* getNumeAsigurat() const {
        return numeAsigurat;
    }

    double getSumaAsigurata() const {
        return sumaAsigurata;
    }

    const char* getTipAsigurare() const {
        return tipAsigurare;
    }

    int getDurataAni() const {
        return durataAni;
    }

    // Afișare
    friend ostream& operator<<(ostream& out, const Asigurare& a) {
        out << "ID Asigurare: " << a.idAsigurare << "\n";
        out << "Nume Asigurat: " << (a.numeAsigurat ? a.numeAsigurat : "N/A") << "\n";
        out << "Tip Asigurare: " << (a.tipAsigurare ? a.tipAsigurare : "N/A") << "\n";
        out << "Suma Asigurata: " << a.sumaAsigurata << "\n";
        out << "Durata (ani): " << a.durataAni << "\n";
        return out;
    }
};

int Asigurare::contorAsigurari = 0;

class Portofoliu {
private:
    Asigurare* listaAsigurari;
    int nrAsigurari;

public:

    Portofoliu() {
        listaAsigurari = nullptr;
        nrAsigurari = 0;
    }

    Portofoliu(Asigurare* asigurari, int nrAsigurari) {
        this->nrAsigurari = nrAsigurari;
        this->listaAsigurari = new Asigurare[nrAsigurari];
        for (int i = 0; i < nrAsigurari; i++) {
            this->listaAsigurari[i] = asigurari[i];
        }
    }

    // Constructor de copiere
    Portofoliu(const Portofoliu& p) {
        this->nrAsigurari = p.nrAsigurari;
        this->listaAsigurari = new Asigurare[p.nrAsigurari];
        for (int i = 0; i < p.nrAsigurari; i++) {
            this->listaAsigurari[i] = p.listaAsigurari[i];
        }
    }

    // Operator de atribuire
    Portofoliu& operator=(const Portofoliu& p) {
        if (this != &p) {
            delete[] listaAsigurari;
            this->nrAsigurari = p.nrAsigurari;
            this->listaAsigurari = new Asigurare[p.nrAsigurari];
            for (int i = 0; i < p.nrAsigurari; i++) {
                this->listaAsigurari[i] = p.listaAsigurari[i];
            }
        }
        return *this;
    }

    // Destructor
    ~Portofoliu() {
        delete[] listaAsigurari;
    }

    // Afișare portofoliu
    friend ostream& operator<<(ostream& out, const Portofoliu& p) {
        out << "Portofoliu cu " << p.nrAsigurari << "\n";
        for (int i = 0; i < p.nrAsigurari; i++) {
            out << p.listaAsigurari[i] << "\n";
        }
        return out;
    }

    // Adaugare asigurare in portofoliu
    void adaugaAsigurare(const Asigurare& asigurarenoua) {
        Asigurare* temp = new Asigurare[nrAsigurari + 1];
        for (int i = 0; i < nrAsigurari; i++) {
            temp[i] = listaAsigurari[i];
        }
        temp[nrAsigurari] = asigurarenoua;
        delete[] listaAsigurari;
        listaAsigurari = temp;
        nrAsigurari++;
    }

    // Calcul valoare medie
    double calculeazaValoareMedie() const {
        if (nrAsigurari == 0) {
            return 0.0;
        }
        double sumaTotala = 0;
        for (int i = 0; i < nrAsigurari; i++) {
            sumaTotala += listaAsigurari[i].getSumaAsigurata();
        }
        return sumaTotala / nrAsigurari;
    }
};

int main() {

    Asigurare a1("Ion Popescu", 10000, "Auto", 5);
    Asigurare a2("Maria Ionescu", 15000, "Locuinta", 10);
    Asigurare a3("Andrei Vasilescu", 20000, "Sanatate", 3);
    Asigurare a4(a3);

    cout << a1;
    cout << a2;

    cout << "=========================" << endl;
    double cursEuro = 4.95;
    cout << "Valoarea asigurarii lui Ion Popescu in euro: " << a1(cursEuro) << "\n";

    Portofoliu p;
    p.adaugaAsigurare(a1);
    p.adaugaAsigurare(a2);
    p.adaugaAsigurare(a3);

    cout << "=========================" << endl;

    cout << p;
    cout << "Valoarea medie a unei asigurari: " << p.calculeazaValoareMedie() << "\n";

    return 0;
}

