#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Marker {
private:
    char* culoare;
    int greutatemarker;
    string producator;
    float pret;
    static int nrmarker;
    int nrmodele;
    string* modele;

public:
    Marker() {
        culoare = nullptr;
        greutatemarker = 0;
        producator = "necunoscut";
        pret = 0;
        nrmodele = 0;
        modele = nullptr;
        nrmarker++;
    }

    Marker(const char* culoare, int greutatemarker, const string& producator, float pret, int nrmodele, string* modele)
    {
        this->culoare = new char[strlen(culoare) + 1];
        strcpy(this->culoare, culoare);
        this->modele = new string[nrmodele];
        for (int i = 0; i < nrmodele; i++) {
            this->modele[i] = modele[i];
        }
        nrmarker++;
    }

    Marker(const Marker& m) {
        this->culoare = new char[strlen(m.culoare) + 1];
        strcpy(this->culoare, m.culoare);
        this->modele = new string[m.nrmodele];
        for (int i = 0; i < m.nrmodele; i++) {
            this->modele[i] = m.modele[i];
        }
    }

    Marker& operator=(const Marker& m) {
        if (this != &m) {
            delete[] this->culoare;
            delete[] this->modele;

            this->culoare = new char[strlen(m.culoare) + 1];
            strcpy(this->culoare, m.culoare);
            this->greutatemarker = m.greutatemarker;
            this->producator = m.producator;
            this->pret = m.pret;
            this->nrmodele = m.nrmodele;
            this->modele = new string[m.nrmodele];
            for (int i = 0; i < m.nrmodele; i++) {
                this->modele[i] = m.modele[i];
            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Marker& m) {
        out << "Culoare: " << m.culoare << endl;
        out << "Greutate: " << m.greutatemarker << endl;
        out << "Producator: " << m.producator << endl;
        out << "Pret: " << m.pret << endl;
        out << "Numar Modele: " << m.nrmodele << endl;
        out << "Modele: ";
        for (int i = 0; i < m.nrmodele; i++) {
            out << m.modele[i] << " ";
        }
        out << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Marker& m) {
        char buffer[100];
        cout << "Culoare: ";
        in.ignore();
        in.getline(buffer, 100);
        delete[] m.culoare;
        m.culoare = new char[strlen(buffer) + 1];
        strcpy(m.culoare, buffer);

        cout << "Greutate: ";
        in >> m.greutatemarker;

        cout << "Producator: ";
        in >> m.producator;

        cout << "Pret: ";
        in >> m.pret;

        cout << "Numar Modele: ";
        in >> m.nrmodele;

        delete[] m.modele;
        m.modele = new string[m.nrmodele];
        for (int i = 0; i < m.nrmodele; i++) {
            cout << "Model[" << i + 1 << "]: ";
            in >> m.modele[i];
        }

        return in;
    }

    ~Marker() {
        delete[] this->culoare;
        delete[] this->modele;
    }

    //scriere in fiser binar
    friend ofstream& operator<<(ofstream& out, const Marker& m) {
        int culoareLength = m.culoare ? strlen(m.culoare) : 0;
        out.write((char*)&culoareLength, sizeof(culoareLength));
        if (m.culoare) {
            out.write(m.culoare, culoareLength);
        }

        out.write((char*)&m.greutatemarker, sizeof(m.greutatemarker));
        int producatorLength = m.producator.size();
        out.write((char*)&producatorLength, sizeof(producatorLength));
        out.write(m.producator.c_str(), producatorLength);

        out.write((char*)&m.pret, sizeof(m.pret));
        out.write((char*)&m.nrmodele, sizeof(m.nrmodele));
        for (int i = 0; i < m.nrmodele; i++) {
            int modelLength = m.modele[i].size();
            out.write((char*)&modelLength, sizeof(modelLength));
            out.write(m.modele[i].c_str(), modelLength);
        }

        return out;
    }
    //citire din fisier binar
    friend ifstream& operator>>(ifstream& in, Marker& m) {
        int culoareLength;
        in.read((char*)&culoareLength, sizeof(culoareLength));

        delete[] m.culoare;
        if (culoareLength > 0) {
            m.culoare = new char[culoareLength + 1];
            in.read(m.culoare, culoareLength);
            m.culoare[culoareLength] = '\0';
        }
        else {
            m.culoare = nullptr;
        }

        in.read((char*)&m.greutatemarker, sizeof(m.greutatemarker));
        int producatorLength;
        in.read((char*)&producatorLength, sizeof(producatorLength));

        char* producatorBuffer = new char[producatorLength + 1];
        in.read(producatorBuffer, producatorLength);
        producatorBuffer[producatorLength] = '\0';
        m.producator = string(producatorBuffer);
        delete[] producatorBuffer;

        in.read((char*)&m.pret, sizeof(m.pret));
        in.read((char*)&m.nrmodele, sizeof(m.nrmodele));

        delete[] m.modele;
        if (m.nrmodele > 0) {
            m.modele = new string[m.nrmodele];
            for (int i = 0; i < m.nrmodele; i++) {
                int modelLength;
                in.read((char*)&modelLength, sizeof(modelLength));
                char* modelBuffer = new char[modelLength + 1];
                in.read(modelBuffer, modelLength);
                modelBuffer[modelLength] = '\0';
                m.modele[i] = string(modelBuffer);
                delete[] modelBuffer;
            }
        }
        else {
            m.modele = nullptr;
        }

        return in;
    }
};

int Marker::nrmarker = 0;

int main() {
    Marker m1;
    cin >> m1;
    cout << m1;

    ofstream fout("Marker.bin", ios::binary);
    fout << m1;
    fout.close();

    ifstream fin("Marker.bin", ios::binary);
    Marker m2;
    fin >> m2;
    fin.close();

    cout << "Deserialized Marker:" << endl;
    cout << m2;

    return 0;
}

