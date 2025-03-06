#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#pragma warning(disable : 4996)
using namespace std;

class Autoturism
{
private:
	string marca;
	string model;
	int putere;
	double pret;
	float* distanteParcurse;
	//the number of elements for the array above
	int nrDrumuri; //nr de elemente al vectorului de mai sus
	char* taraDeProductie;

public:
	Autoturism()
	{
		marca = "Necunoscuta";
		model = "Necunoscut";
		putere = 0;
		pret = 5000;
		distanteParcurse = nullptr;
		nrDrumuri = 0;
		taraDeProductie = nullptr;
	}

	Autoturism(string marca, string model, int putere) : Autoturism()
	{
		this->marca = marca;
		this->model = model;
		this->putere = putere;
	}

	Autoturism(string marca, string model, float* distante, int nrDrumuri)
	{
		this->marca = marca;
		this->model = model;
		this->putere = 0;
		this->pret = 5000;

		if (distante != nullptr && nrDrumuri > 0) {
			this->nrDrumuri = nrDrumuri;
			distanteParcurse = new float[nrDrumuri];
			for (int i = 0; i < nrDrumuri; i++) {
				distanteParcurse[i] = distante[i];
			}
		}
		taraDeProductie = nullptr;
	}

	Autoturism(const Autoturism& m) {
		this->marca = m.marca;
		this->model = m.model;
		this->putere = m.putere;
		this->pret = m.pret;

		if (m.distanteParcurse != nullptr && m.nrDrumuri > 0) {
			this->nrDrumuri = m.nrDrumuri;
			distanteParcurse = new float[m.nrDrumuri];
			for (int i = 0; i < nrDrumuri; i++) {
				distanteParcurse[i] = m.distanteParcurse[i];
			}
		}

		if (m.taraDeProductie != nullptr) {
			taraDeProductie = new char[strlen(m.taraDeProductie) + 1];
			strcpy(taraDeProductie, m.taraDeProductie);
		}
		else {
			taraDeProductie = nullptr;
		}
	}

	string getMarca()
	{
		return marca;
	}

	void setMarca(string marca) {
		if (marca.length() >= 3) {
			this->marca = marca;
		}
	}

	int getNrDrumuri() {
		return nrDrumuri;
	}

	float* getDistanteParcurse() {
		if (distanteParcurse != nullptr) {
			float* copieDistante = new float[nrDrumuri];
			for (int i = 0; i < nrDrumuri; i++) {
				copieDistante[i] = distanteParcurse[i];
			}
			return copieDistante;
		}
		return nullptr;
	}

	void setDistante(float* distanteParcurse, int nrDrumuri) {
		if (distanteParcurse != nullptr && nrDrumuri > 0) {
			delete[] this->distanteParcurse;
			this->nrDrumuri = nrDrumuri;
			this->distanteParcurse = new float[nrDrumuri];
			for (int i = 0; i < nrDrumuri; i++) {
				this->distanteParcurse[i] = distanteParcurse[i];
			}
		}
	}

	char* getTaraDeProductie() {
		if (taraDeProductie != nullptr) {
			char* copieTara = new char[strlen(taraDeProductie) + 1];
			strcpy(copieTara, taraDeProductie);
			return copieTara;
		}
		return nullptr;
	}

	void setTaraDeProductie(const char* tara) {
		delete[] taraDeProductie;
		if (tara != nullptr) {
			taraDeProductie = new char[strlen(tara) + 1];
			strcpy(taraDeProductie, tara);
		}
		else {
			taraDeProductie = nullptr;
		}
	}

	char* AdresaInceputTaraDeProductie() {
		return taraDeProductie;
	}

	~Autoturism() {
		delete[] distanteParcurse;
		distanteParcurse = nullptr;
		delete[] taraDeProductie;
		taraDeProductie = nullptr;
	}
};
//ATENTIE!!!
//Sunt punctate doar solutiile originale si individuale
//Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//Signatura functiilor nu se poate modifica, doar continului lor

//---------------------------------------------------------------

//1. Modificati constructorul implicit din clasa Autoturism de mai sus
//acesta va initializa marca cu "Necunoscuta", modelul cu "Necunoscut"
//puterea cu 0, pretul cu 5000, vectorul de distante cu NULL si nrDrumuri cu 0

//-----facut----------------------------------------------------------

//2. Modificati constructorul cu 3 parametri: marca, model, putere
//acesta va initializa cele 3 atribute cu valorile primite
//restul de atribute nu trebuie sa ramana neinitializate si vor folosi aceleasi valori implicite ca mai sus

//------facut--------------------------------------------------------

//3. Modificati constructorul cu 4 parametri pentru a copia valorile
//primite drept parametri in atributele clasei
//constructorul nu va lasa atribute neinitializate

//------facut-------------------------------------------------------

//4. Adaugati un destructor in clasa care sterge zonele de memorie anterior alocate
//acesta va seta pointerii pe NULL dupa ce face stergerea

//--------facut----------------------------------------------------

//5. Adaugati clasei un constructor de copiere astfel incat
//sa se realizeze o copie in profunzime (deep copy) a obiectelor

//--------facut----------------------------------------------------

//6. Modificati metodele de acces (getteri si setteri) pentru atributul marca
//Setterul va accepta denumiri de marci cu o lungime
//mai mare sau egala de 3 caractere
//in caz contrar marca ramane cea existenta

//----------facut-----------------------------------------------------

//7. Modificati getter-ul pentru vectorul de distante parcurse
//Getter-ul va returna o copie a vectorului din clasa
//Modificati getter-ul si pentru numarul de drumuri

//------------facut---------------------------------------------------

//8. Modificati setter-ul pentru vectorul de distante
//acesta va modifica simultan vectorul si numarul de elemente
//si nu va accepta decat vectori nenuli si numar de elemente mai mare decat 0

//---------facut------------------------------------------------------

//9. Adaugati un camp de tip char* in clasa numit taraDeProductie
//modificati getter-ul si setter-ul din clasa pentru a returna,
//respectiv a modifica valoarea acestui camp
//Metoda AdresaInceputTaraDeProductie intoarce adresa primului element din tara de productie
//(da, nu e neaparat safe, dar e necesar pentru test)

//-----------facut----------------------------------------------------

//10. Modificati constructorii, destructorul si alte metode necesare
//astfel incat clasa sa gestioneze corect noul camp


int main()
{
	float distante[] = { 100.5, 200.7, 300.8 };
	Autoturism m1("Skoda", "Octavia", 150);
	m1.setDistante(distante, 3);
	m1.setMarca("BMW");

	cout << "Marca: " << m1.getMarca() << endl;
	cout << "Numar drumuri: " << m1.getNrDrumuri() << endl;

	char tara[] = "Romania";
	m1.setTaraDeProductie(tara);
	cout << "Tara de productie: " << m1.getTaraDeProductie() << endl;

	return 0;
	//Playgroud
	//Testati aici functiile dorite si folositi debugger-ul pentru eventualele probleme
	//Test here the functions that you need and use the debugger to identify the problems
}
