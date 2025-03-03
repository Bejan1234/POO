#include <iostream>
#include <string>
#pragma warning(disable:4996)

using namespace std;
bool fisierDeschis = true;

enum tipAplicatie { aplicatieWeb = 5, aplicatieMobila = 10, aplicatieDesktop = 15 };

class Autoturism
{
public:
	string marca;
	string model;
	int putere;
	double pret;
	char numarInmatriculare[9];

	//3.
	Autoturism() {
		marca = "Necunoscuta";
		model = "Necunoscut";
	    putere = 0;
	    pret = 5000;
}
	//4.
	Autoturism(string marca, string model, int putere) : marca(marca), model(model), putere(putere), pret(5000) {
	}
	//5.
	void discount(int procent) {
		if (procent >= 1 && procent <= 50) {
			pret -= pret * procent / 100.0;
		}
	}
	//6.
	~Autoturism() {
		fisierDeschis = false;
	}
	//7.

	void seteazaNumarInmatriculare(char numar[]) {
		strncpy(numarInmatriculare, numar, 8);
		numarInmatriculare[8] = '\0';
	}

	char* obtineNumarInmatriculare() {
		return numarInmatriculare;
	}
};

//ATENTIE!!!
//Sunt punctate doar solutiile originale si individuale
//Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//Signatura functiilor nu se poate modifica, doar continului lor

//1. Functia de mai jos primeste drept parametri doua variabile de tip int
//modificati modalitatea de transmitere a parametrilor astfel incat
//cele doua valori sa fie interschimbate la iesirea din functie
//apelul se va face de forma: inerschimbare(x, y)
//unde x si y sunt 2 intregi
//Observatie: signatura acestei functii poate fi modificata
void interschimbare(int &val1, int &val2) 
{
	int temp = val1;
    val1 = val2; 
	val2 = temp;

}

//2. Functia de mai jos returneaza o variabila de tipul enumeratie
//(tipAplicatie, enum definit mai sus)
//modificati enumul astfel incat acesta sa aiba trei valori posibile
//Acestea sunt: 5 - aplicatieWeb, 10 - aplicatieMobila, 15 - aplicatieDesktop
//functia primeste drept parametru un string dintre cele de mai sus
//("aplicatieWeb", "aplicatieMobila", etc) si returneaza valoarea din enum
//corespunzatoare ei
tipAplicatie modificare_enum(string tip) {
	if (tip == "aplicatieWeb") return aplicatieWeb;
	if (tip == "aplicatieMobila") return aplicatieMobila;
	if (tip == "aplicatieDesktop") return aplicatieDesktop;
	return (tipAplicatie)0;
}

//3. Modificati constructorul implicit din clasa Autoturism de mai sus
//acesta va initializa marca cu "Necunoscuta", modelul cu "Necunoscut"
//puterea cu 0 si pretul cu 5000

//------------------------------------

//4. Modificati constructorul cu 3 parametri: marca, model, putere
//acesta va initializa cele 3 atribute cu valorile primite
//pretul va fi setat la fel ca in celalalt constructor ca fiind 5000

//------------------------------------

//5. Modificati metoda discount pentru a acorda un discount din pret
//discountul este in procente si poate fi intre 1% si 50%
//functia modifica pretul cu valoarea sa dupa aplicarea discountului

//------------------------------------

//6. Adaugati un destructor in clasa care seteaza variabila globala
//fisierDeschis pe false

//------------------------------------

//7. Adaugati clasei un atribut nou numit numarInmatriculare
//acesta este un sir de caractere alocat static de lungime maxima 9
//Modificati metodele seteazaNumarInmatriculare si obtineNumarInmatriculare
//astfel incat sa modifice respectiv sa returneze valoarea acestui nou camp

//------------------------------------

//8. Functia de mai jos primeste drept parametru un vector static de masini
//reprezentand o flota de autoturisme si numarul sau de elemente
//calculati si returnati valoarea totala a flotei de autoturisme
//prin adunarea preturilor masinilor din flota

double calcul_valoare_flota(Autoturism masini[], int nr_masini) {
	double valoareTotala = 0;
	for (int i = 0; i < nr_masini; i++) {
		valoareTotala += masini[i].pret;
	}
	return valoareTotala;
}

//9. Functia de mai jos primeste drept parametri un vector alocat dinamic 
//de pointeri la Autoturism impreuna cu numarul de elemente.
//Returnati valoarea celei mai scumpe masini din acel vector
double cea_mai_tare_din_parcare(Autoturism** vector, int nr_masini) {
	double pretMaxim = 0;
	for (int i = 0; i < nr_masini; i++) {
		if (vector[i] && vector[i]->pret > pretMaxim) {
			pretMaxim = vector[i]->pret;
		}
	}
	return pretMaxim;
}

//10. Functia de mai jos primeste drept parametri o matrice
//de pointeri la Autoturism impreuna cu numarul de linii si de coloane
//Matricea reprezinta cum sunt dispuse masinile intr-o parcare
//Un element null inseamna ca pe acel loc de parcare nu este nicio masina
//Functia va returna o matrice a locurilor de parcare astfel
//100 90 60
//0 160 75
//0 90 0
//Explicatii: Parcarea are 3 linii si cate 3 locuri de parcare pe fiecare linie
//Pe prima linie sunt parcate 3 masini cu putere de 100, 90 si respectiv 60 cai putere
//pe a doua linie primul loc este neocupat, iar urmatoarele doua locuri
//sunt ocupate de doua masini cu 160, respectiv 75 de cai putere, s.a.m.d.
int** locuri_libere(Autoturism*** matrice, int nrLinii, int nrColoane) {
	int** parcare = new int* [nrLinii];
	for (int i = 0; i < nrLinii; i++) {
		parcare[i] = new int[nrColoane];
		for (int j = 0; j < nrColoane; j++) {
			if (matrice[i][j] != nullptr) {
				parcare[i][j] = matrice[i][j]->putere;
			}
			else {
				parcare[i][j] = 0; // Loc neocupat
			}
		}
	}
	return parcare;
}


int main() 
{
	
	//Playgroud
	//Testati aici functiile dorite si folositi debugger-ul pentru eventualele probleme
	//Test here the functions that you need and use the debugger to identify the problems
}