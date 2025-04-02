#define CRT_SECURE_NO_WARINGS
#include <iostream>
using namespace std;

class Plantatie {
private:
	const int Id;
	string adresa;
	int NrPomi;
	int* varsta;
	static int VarstaMinimaRod;
	static int NrPlantatie;
	float suprafata;

public:

	Plantatie() :Id(NrPlantatie++) {
		adresa = "Necunoscuta";
		NrPomi = 0;
		varsta = nullptr;
		suprafata = 0;
	}

	Plantatie(string adresa, int Nrpomi, int varsta[], float suprafata) :Id(NrPlantatie++) {
		this->adresa = adresa;
		this->NrPomi = NrPomi;
		this->varsta = new int[NrPomi];
		for (int i = 0; i < NrPomi; i++) {
			this->varsta[1] = varsta[i];
		}
		this->suprafata = suprafata;

	}


	//c.de copiere

	Plantatie(const Plantatie& p) :Id(NrPlantatie++) {
		this->adresa = p.adresa;
		this->NrPomi = p.NrPomi;
		this->varsta = new int[NrPomi];
		for (int i = 0; i < NrPomi; i++) {
			this->varsta[1] = p.varsta[i];
		}
		this->suprafata = p.suprafata;

	}

	string getadresa() {
		return this->adresa;
	}
	void setadresa(string adresanoua) {
		if (adresanoua != this->adresa) {
			this->adresa = adresanoua;
		}
		else
		{
			cout << "adresa este identica" << endl;
		}
	}

	int getNrPomi() {
		return this->NrPomi;
	}

	void setNrPomi(int NrnouPomi) {
		if (NrnouPomi >= 0) {
			this->NrPomi = NrnouPomi;
		}
		else {
			cout << "Nr de pomi nu poate fi negativ" << endl;
		}
	}
	//validarea este un mod pin care ne asiguram ca indroducem date valide care coespund unor valori din viata reala
//destructor
	~Plantatie() {
		delete[]this->varsta;
	}

	Plantatie& operator=(const Plantatie& p) {
		if (this != &p) {//evitam auto asignare
			this->adresa = p.adresa;
			this->NrPomi = p.NrPomi;
			this->varsta = new int[NrPomi];
			for (int i = 0; i < NrPomi; i++) {
				this->varsta[1] = p.varsta[i];
			}
			this->suprafata = p.suprafata;
		}
		return *this;

	}

	friend ostream& operator<<(ostream& out, Plantatie& p) {
		out << "Id-ul este: " << p.Id << "\n";
		out << "adresa este:" << p.adresa << "\n";
		out << "numarul de pomi:" << p.NrPomi << "\n";
		out << "varstele sunt:" << "\n";
		for (int i = 0; i < p.NrPomi; i++) {
			out << p.varsta[i] << " ";
		}
		out << "\n";

		out << "suprafata este: " << p.suprafata << "\n";
		return out;
	}

	friend istream& operator>>(istream& in, Plantatie& p) {
		in >> p.adresa;
		in >> p.NrPomi;
		delete[]p.varsta;
		p.varsta = new int[p.NrPomi];
		for (int i = 0; i < p.NrPomi; i++) {
			in >> p.varsta[i];
		}
		in >> p.suprafata;
		return in;

	}

	operator int() {
		int contor = 0;
		for (int i = 0; i < NrPomi; i++) {
			if (varsta[i] >= VarstaMinimaRod) {
				contor++;
			}
		}

		return contor;
	}

	bool operator ==(const Plantatie& p) {
		return adresa == p.adresa && this->NrPomi == p.NrPomi && this->suprafata == p.suprafata;

	}

	//operator (+)- de inserare

	friend Plantatie operator+(int NrPomi, Plantatie& p) {
		Plantatie Plantatienoua = p;
		int* varstanoua = new int[Plantatienoua.NrPomi + NrPomi];
		for (int i = 0; i < Plantatienoua.NrPomi; i++) {
			varstanoua[i] = Plantatienoua.varsta[i];
		}
		for (int i = 0; i < NrPomi; i++) {
			varstanoua[Plantatienoua.NrPomi + i] = 0;
		}
		delete[]Plantatienoua.varsta;
		Plantatienoua.varsta = varstanoua;
		Plantatienoua.NrPomi += NrPomi;
		return Plantatienoua;
	}

	int getNrPomiVarstaMinima(int varstaminima) {
		int contor = 0;
		for (int i = 0; i < NrPomi; i++) {
			if (varsta[i] >= varstaminima) {
				contor++;
			}
		}
		return contor;
	}

};

int Plantatie::VarstaMinimaRod = 8;
int Plantatie::NrPlantatie = 0;

int main() {

	Plantatie p1;
	cin >> p1;

	cout << p1;

	cout << "================" << endl;
	cout << (int)p1 << endl;

	cout << "================" << endl;
	Plantatie p2 = p1;

	cout << p2 << endl;
	if (p1 == p2) {
		cout << "p1 si p2 sunt egale!" << endl;;
	}
	else
	{
		cout << "p1 si p2 nu sunt egale!" << endl;;
	}

	cout << "================" << endl;
	//apel operator +
	Plantatie p3 = 3 + p1;
	cout << p3 << endl;
	cout << "================" << endl;
	//apelam metoda de getvarstaminima

	cout << p1.getNrPomiVarstaMinima(5) << endl;


	return 0;
}
