#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class GestiuneFirme {
public:
	virtual float calculprofit() = 0;
	virtual void afisareinformatiisuplimentare() = 0;

};

class FirmaDistributie : public GestiuneFirme {
private:
	const int idfirma;
	static int nrfirma;
	char* client;
	float pret;
	int nrproduse;
	string* produse;
	vector<string> produseExpirate; //container STL
protected:
	bool starecomanda;
	double rating;
public:
	FirmaDistributie() :idfirma(nrfirma++) {
		client = nullptr;
		pret = 0;
		nrproduse = 0;
		produse = nullptr;
		starecomanda = false;
		rating = 0;

	}
	FirmaDistributie(const char* client, float pret, int nrproduse, string* produse, bool starecomanda, double rating) :idfirma(nrfirma++) {
		this->client = new char[strlen(client) + 1];
		strcpy_s(this->client, strlen(client) + 1, client);
		this->pret = pret;
		this->nrproduse = nrproduse;
		this->produse = new string[nrproduse];
		for (int i = 0; i < nrproduse; i++) {
			this->produse[i] = produse[i];
		}
		this->starecomanda = starecomanda;
		this->rating = rating;
	}
	FirmaDistributie(const FirmaDistributie& f) :idfirma(nrfirma++) {
		this->client = new char[strlen(f.client) + 1];
		strcpy_s(this->client, strlen(f.client) + 1, f.client);
		this->pret = f.pret;
		this->nrproduse = f.nrproduse;
		this->produse = new string[nrproduse];
		for (int i = 0; i < nrproduse; i++) {
			this->produse[i] = f.produse[i];
		}
		this->starecomanda = f.starecomanda;
		this->rating = f.rating;
	}
	FirmaDistributie operator=(const FirmaDistributie& f) {
		if (this != &f) {
			this->client = new char[strlen(f.client) + 1];
			strcpy_s(this->client, strlen(f.client) + 1, f.client);
			this->pret = f.pret;
			this->nrproduse = f.nrproduse;
			this->produse = new string[nrproduse];
			for (int i = 0; i < nrproduse; i++) {
				this->produse[i] = f.produse[i];
			}
			this->starecomanda = f.starecomanda;
			this->rating = f.rating;

		}
		return *this;
	}
	~FirmaDistributie() {
		delete[]client;
		delete[]produse;
	}


	// Getteri si setteri cu validari(validarile sunt la setteri)
	char* getclient() {
		return this->client;
	}
	void setclient(const char* clientnou) {
		if (strcmp(this->client, clientnou) == 0) {
			throw new exception("Clientul nou trebuie sa aiba alt nume fata de clientul initial");

		}
		else {
			delete[]this->client;
			this->client = new char[strlen(clientnou) + 1];
			strcpy_s(this->client, strlen(clientnou) + 1, clientnou);
		}

	}
	float getpret() {
		return this->pret;
	}
	void setpret(float pretnou) {
		if (pretnou <= 0 || pret == pretnou) {
			throw new exception("Pretul nou trebuie sa fie strict pozitiv si diferit de cel initial");
		}
		else {
			this->pret = pretnou;
		}
	}
	friend ostream& operator<<(ostream& out, FirmaDistributie& f) {
		out << f.idfirma << endl;
		out << f.nrfirma << endl;
		out << f.client << endl;
		out << f.pret << endl;
		out << f.nrproduse << endl;
		for (int i = 0; i < f.nrproduse; i++) {
			out << f.produse[i] << " ";
		}
		out << endl;
		out << f.starecomanda << endl;
		out << f.rating << endl;
		return out;
	}
	friend istream& operator>>(istream& in, FirmaDistributie& f) {
		char buffer[100];
		cout << "introduceti clientul" << endl;
		in >> ws;
		in.getline(buffer, 100);
		delete[]f.client;
		f.client = new char[strlen(buffer) + 1];
		strcpy_s(f.client, strlen(buffer) + 1, buffer);
		cout << "introduceti pretul: " << endl;
		in >> f.pret;
		cout << "introduceti numarul de produse: " << endl;
		in >> f.nrproduse;
		cout << "introduceti produsele: " << endl;
		delete[]f.produse;
		f.produse = new string[f.nrproduse];
		for (int i = 0; i < f.nrproduse; i++) {
			in >> f.produse[i];
		}
		cout << "introduceti statutul comenzii: " << endl;
		in >> f.starecomanda;
		cout << "Introduceti ratingul: " << endl;
		in >> f.rating;
		return in;
	}
	//scirere in fisier text

	friend ofstream& operator<<(ofstream& fout, FirmaDistributie& f) {
		cout << "introduceti lungimea minima acceptata a comenzii/ a produsului: " << endl;
		int lungimeminimaacceptata;
		cin >> lungimeminimaacceptata;
		for (int i = 0; i < f.nrproduse; i++) {
			if (f.produse[i].size() >= lungimeminimaacceptata) {
				fout << f.produse[i] << " ";

			}
		}
		return fout;
	}
	string& operator [](int index) {
		for (int i = 0; i < nrproduse; i++) {
			if (index == i) {
				return this->produse[index];
			}
		}
	}
	//operatorul +=
	FirmaDistributie& operator+=(const string& produsnou) {
		string* copie = new string[nrproduse + 1];
		for (int i = 0; i < nrproduse; i++) {
			copie[i] = produse[i];
		}
		copie[nrproduse] = produsnou;
		delete[]this->produse;
		this->produse = copie;
		nrproduse++;
		return *this;
	}
	//suprascriere metodevirutale
	float calculprofit()override {
		return this->pret * this->nrproduse;
	}
	void afisareinformatiisuplimentare()override {
		cout << "Apel metoda virtuala void " << endl;
	}

	void inserareInContainerSTL(string produsExpiratNou) {
		produseExpirate.push_back(produsExpiratNou); //inseram in STL prin push_back
	}

	void afisareContainerSTL() {
		for (const auto& produs : produseExpirate) {//pentru afisare STL 
			cout << produs << endl;
		}
	}


};
int FirmaDistributie::nrfirma = 0;




int main() {
	FirmaDistributie f1;
	cin >> f1;
	f1.setclient("Ionut");
	string produse[] = { "lapte", "miere", "paine", "oua" };
	FirmaDistributie f2("Petru", 999, 4, produse, true, 5.0);
	cout << f2;
	cout << "==================================CONSTRUCTORUL DE COPIERE======================================" << endl;
	FirmaDistributie f3(f1);
	cout << f3;
	cout << "==================================OPERATORUL '='======================================" << endl;
	FirmaDistributie f4 = f2;
	cout << f4;
	cout << "=============================Scriere fisier text===========================================" << endl;
	ofstream fout("Produse.txt");
	fout << f1;
	fout.close();
	cout << "====================================Operatorul Index====================================" << endl;
	cout << f1[1] << endl;
	cout << "====================================Operatorul '+='====================================" << endl;
	f1 += "Pizza";
	cout << f1 << endl;
	cout << "====================================Apel Virtualizare====================================" << endl;
	cout << f1.calculprofit() << endl;
	f1.afisareinformatiisuplimentare();

	cout << "====================================Apel CONTAINER STL====================================" << endl;
	f1.inserareInContainerSTL("Branza");
	f1.inserareInContainerSTL("Cascaval");
	f1.inserareInContainerSTL("Sunca");
	f1.inserareInContainerSTL("Salam");

	f1.afisareContainerSTL();



	return 0;
}
