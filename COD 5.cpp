
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class Produs {
private:

    char* nume;
    float pret;
    int cantitate;
    const int idProdus;
    static int contorProduse;

public:
    Produs() : idProdus(contorProduse++) {
        nume = nullptr;
        pret = 0.0;
        cantitate = 0;
    }


    Produs(const char* nume, float pret, int cantitate) : idProdus(contorProduse++) {
        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);
        this->pret = pret;
        this->cantitate = cantitate;
    }


    Produs(const Produs& p) : idProdus(contorProduse++) {
        this->nume = new char[strlen(p.nume) + 1];
        strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
        this->pret = p.pret;
        this->cantitate = p.cantitate;
    }


    Produs& operator=(const Produs& p) {
        if (this != &p) {
            delete[] this->nume;
            this->nume = new char[strlen(p.nume) + 1];
            strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
            this->pret = p.pret;
            this->cantitate = p.cantitate;
        }
        return *this;
    }


    ~Produs() {
        delete[] nume;
    }

    char* getNume() const {
        return nume;
    }
    void setNume(const char* nume) {
        delete[] this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);
    }

    float getPret() const {
        return pret;
    }
    void setPret(float pret) {
        this->pret = pret;
    }

    int getCantitate() const {
        return cantitate;
    }
    void setCantitate(int cantitate) {
        this->cantitate = cantitate;
    }

    int getIdProdus() const {
        return idProdus;
    }
    static int getContorProduse() {
        return contorProduse;
    }


    friend ostream& operator<<(ostream& out, const Produs& p) {
        out << "ID Produs: " << p.idProdus << "\n";
        out << "Produs: " << p.nume << "\n";
        out << "Pret: " << p.pret << "\n";
        out << "Cantitate: " << p.cantitate << "\n";
        out << "Contor:" << p.contorProduse << "\n";
        return out;
    }


    friend istream& operator>>(istream& in, Produs& p) {
        char buffer[100];
        cout << "Nume produs: ";
        in >> ws;
        in.getline(buffer, 100);
        delete[]p.nume;
        p.nume = new char[strlen(buffer) + 1];
        strcpy_s(p.nume, strlen(buffer) + 1, buffer);
        cout << "Pret: ";
        in >> p.pret;
        cout << "Cantitate: ";
        in >> p.cantitate;
        return in;
    }

    bool operator==(const Produs& p) {
        return strcmp(this->nume, p.nume) == 0 && this->pret == p.pret;
    }

    operator int() {
        return this->pret * this->cantitate;
    }

    Produs operator+(const Produs& p) const {

        Produs rezultat(this->nume, this->pret, this->cantitate + p.cantitate);
        return rezultat;
    }



};

int Produs::contorProduse = 0;

class CosCumparaturi {
private:
    string* produse;
    int nrProduse;

public:

    CosCumparaturi() {
        produse = nullptr;
        nrProduse = 0;
    }


    CosCumparaturi(string* produse, int nrProduse) {
        this->nrProduse = nrProduse;
        this->produse = new string[nrProduse];
        for (int i = 0; i < nrProduse; i++) {
            this->produse[i] = produse[i];
        }
    }


    CosCumparaturi(const CosCumparaturi& cos) {
        this->nrProduse = cos.nrProduse;
        this->produse = new string[cos.nrProduse];
        for (int i = 0; i < cos.nrProduse; i++) {
            this->produse[i] = cos.produse[i];
        }
    }


    CosCumparaturi& operator=(const CosCumparaturi& cos) {
        if (this != &cos) {
            delete[] produse;
            this->nrProduse = cos.nrProduse;
            this->produse = new string[cos.nrProduse];
            for (int i = 0; i < cos.nrProduse; i++) {
                this->produse[i] = cos.produse[i];
            }
        }
        return *this;
    }

    ~CosCumparaturi() {
        delete[] produse;
    }


    friend ostream& operator<<(ostream& out, const CosCumparaturi& cos) {
        out << "Cosul de cumparaturi contine :" << cos.nrProduse << "\n";
        for (int i = 0; i < cos.nrProduse; i++) {
            out << cos.produse[i] << " ";
        }
        return out;
    }


    friend istream& operator>>(istream& in, CosCumparaturi& cos) {
        cout << "Numar produse in cos: ";
        in >> cos.nrProduse;
        delete[] cos.produse;
        cos.produse = new string[cos.nrProduse];
        for (int i = 0; i < cos.nrProduse; i++) {
            cout << "Introduceti detalii pentru produsul: " << i + 1 << ":\n";
            in >> cos.produse[i];
        }
        return in;
    }


    string& operator[](int index) {
        if (index >= 0 && index < nrProduse) {
            return produse[index];
        }
        else {
            cout << "Index invalid" << endl;
        }
    }


};

int main() {

    Produs p1;
    cin >> p1;
    cout << p1;

    cout << "=============" << endl;
    Produs p2(p1);
    cout << p2;
    cout << "=============" << endl;
    Produs p3 = p2;
    cout << p3;
    cout << "=============" << endl;

    cout << (int)p1 << endl; // operator cast
    cout << "=============" << endl;
    Produs p4("Laptop", 1500.0, 2);
    Produs p5("Laptop", 1500.0, 3);
    Produs p6 = p4 + p5; //  operator +
    cout << "Produs combinat:\n" << p6;

    cout << "=============" << endl;
    CosCumparaturi cos1;
    cin >> cos1;
    cout << cos1;

    cout << "====================" << endl;
    //operator index
    cout << cos1[0] << ": este valoarea primului vector" << endl;

    cout << "====================" << endl;
    //operator ==

    if (p3 == p2) {
        cout << "Podusele sunt egale" << endl;
    }
    else {
        cout << "Produsele nu sunt egale" << endl;
    }
    cout << "====================" << endl;
    // Afișare contor produse
    cout << "Numarul total de produse create in clasa principala: " << Produs::getContorProduse() << endl;


    return 0;
}



