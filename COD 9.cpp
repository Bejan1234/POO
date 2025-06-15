#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>//librarie stl;
using namespace std;

class GestiuneConstainerSistemeSTL
{
private:
	vector<string> vectorstlinregistari;//vector stl inregistrari
public:
	void adaugainregistare(string& inregistare) {
		vectorstlinregistari.push_back(inregistare);//push back este o functie predefinita prin care adaugam
		//un nou element inttr-un vector stl
	}
	void afisareinregistari() {
		for (const auto& inregistrare : vectorstlinregistari) {
			cout << inregistrare << endl;
		}
	}
};
//virtaulizare: Se foloseste in cadrul claselor abstracte
//Calasa abstracta este o clasa care nu poate fi instantiata,adica nu putem crea obiecte prin acea clasa
//o clasa abstracta poate contine una sau mai multe metode virtuale;
//o metoda virtauala este o metoda care nu are corp si daor semnatura;
//metodete virtaule sunt folosite in clasele ce mostenes clasa abstracta;
//metodele virtual pura sunt suprascrise/supradefinite in clasele ce mostenesc clasa abstracta.

class GestiuneSisteme {
public:
	virtual float calculvenit() = 0;//sintaxa
	virtual void afisaredetalii() = 0;
	virtual~GestiuneSisteme() {

	}
};




class Sistem : public GestiuneSisteme {
private:
	int numarcamere;
	string* camere;
	char* informatii;
	float durata;
	bool stare;
	const int idSistem;
	static int nrsisteme;

	string inregistrari;

	GestiuneConstainerSistemeSTL gestiune;
	//relatie has -a;

public:
	Sistem() :idSistem(nrsisteme++) {
		numarcamere = 0;
		camere = nullptr;
		informatii = nullptr;
		durata = 0;
		stare = true;
		inregistrari = 15;

	}
	Sistem(int numarcamere, string* camere, const char* informatii, float durata, bool stare, string inregistrari) :idSistem(nrsisteme++) {
		this->numarcamere = numarcamere;
		this->camere = new string[numarcamere];
		for (int i = 0; i < numarcamere; i++) {
			this->camere[i] = camere[i];
		}
		this->informatii = new char[strlen(informatii) + 1];
		strcpy_s(this->informatii, strlen(informatii) + 1, informatii);
		this->durata = durata;
		this->stare = stare;
		this->inregistrari = inregistrari;
	}

	Sistem(const Sistem& s) :idSistem(nrsisteme++) {
		this->numarcamere = s.numarcamere;
		this->camere = new string[numarcamere];
		for (int i = 0; i < numarcamere; i++) {
			this->camere[i] = s.camere[i];
		}
		this->informatii = new char[strlen(s.informatii) + 1];
		strcpy_s(this->informatii, strlen(s.informatii) + 1, s.informatii);
		this->durata = s.durata;
		this->stare = s.stare;
		this->inregistrari = s.inregistrari;
	}
	Sistem& operator=(const Sistem& s) {
		if (this != &s) {
			this->numarcamere = s.numarcamere;
			this->camere = new string[numarcamere];
			for (int i = 0; i < numarcamere; i++) {
				this->camere[i] = s.camere[i];
			}
			this->informatii = new char[strlen(s.informatii) + 1];
			strcpy_s(this->informatii, strlen(s.informatii) + 1, s.informatii);
			this->durata = s.durata;
			this->stare = s.stare;
			this->inregistrari = s.inregistrari;
		}return *this;
	}
	friend ostream& operator<<(ostream& out, Sistem& s) {
		out << s.numarcamere << "\n";
		for (int i = 0; i < s.numarcamere; i++) {
			out << s.camere[i] << " ";
		}out << endl;
		out << s.informatii << "\n";
		out << s.durata << "\n";
		out << s.stare << "\n";
		out << s.inregistrari << "\n";
		return out;
	}

	friend istream& operator>>(istream& in, Sistem& s) {
		cout << "Numar camere:" << endl;
		in >> s.numarcamere;
		delete[]s.camere;
		s.camere = new string[s.numarcamere];
		for (int i = 0; i < s.numarcamere; i++) {
			in >> s.camere[i];
		}
		char buffer[100];
		cout << "Introduceti info:" << endl;
		in >> ws;
		in.getline(buffer, 100);
		delete[]s.informatii;
		s.informatii = new char[strlen(buffer) + 1];
		strcpy_s(s.informatii, strlen(buffer) + 1, buffer);
		cout << "Durata:" << endl;
		in >> s.durata;
		cout << "Starea:" << endl;
		in >> s.stare;
		cout << "Inregistrari:" << endl;
		in >> s.inregistrari;
		return in;
	}

	~Sistem() {
		delete[]this->camere;
		delete[]this->informatii;
	}
	//1.
	string operator[](int index) {
		if (index >= 0 && index < numarcamere) {
			return this->camere[index];
		}
		else
			return "index invalid";
	}

	//2.
	Sistem& operator+=(const string& Cameranoua) {
		string* copie = this->camere;
		this->camere = new string[this->numarcamere + 1];
		for (int i = 0; i < this->numarcamere; i++) {
			this->camere[i] = copie[i];
		}
		this->camere[this->numarcamere] = Cameranoua;
		//noua camera pe ultima pozitie din vector;
		this->numarcamere++;
		delete[]copie;
		return *this;
	}

	float calculvenit()override {
		return numarcamere * durata;
	}

	void afisaredetalii()override {
		cout << "Detelii indisponibile: " << endl;
	}

	void adaugainregistrare(string inregistrare) {
		gestiune.adaugainregistare(inregistrare);
	}
	void afisareinregistrare() {
		gestiune.afisareinregistari();
	}

};
//3.
class SistemSupraveghere : public Sistem {
private:
	string producator;
	int numaragenti;
public:
	SistemSupraveghere() :Sistem() {
		this->producator = "necunoscut";
		this->numaragenti = 0;
	}
	SistemSupraveghere(int numarcamere, string* camere, const char* informatii, float durata, bool stare, string inregistrari, string producator, int numaragenti) :Sistem(numarcamere, camere, informatii, durata, stare, inregistrari) {

		this->producator = producator;
		this->numaragenti = numaragenti;
	}
	SistemSupraveghere(const SistemSupraveghere& s) : Sistem(s) {
		this->producator = s.producator;
		this->numaragenti = s.numaragenti;
	}
	SistemSupraveghere& operator=(const SistemSupraveghere& s) {
		Sistem::operator=(s);
		this->producator = s.producator;
		this->numaragenti = s.numaragenti;
		return *this;
	}
	friend ostream& operator<<(ostream& out, SistemSupraveghere& s) {
		out << (Sistem&)s;
		out << s.producator << "\n";
		out << s.numaragenti << "\n";
		return out;
	}
	friend istream& operator>>(istream& in, SistemSupraveghere& s) {
		in >> (Sistem&)s;
		in.ignore();
		cout << "Introduceti producator: ";
		in >> s.producator;
		cout << "Introduceti numar agenti: ";
		in >> s.numaragenti;
		return in;

	}



};

int Sistem::nrsisteme = 0;

int main() {
	Sistem s1;
	cin >> s1;
	cout << s1;

	cout << "===============" << endl;
	string camere[] = { "camere0","camere1","camere 3" };
	Sistem s2(3, camere, "alerata", 200, true, "Disponibil");
	cout << s2;

	cout << "=================" << endl;

	Sistem s3(s1);
	cout << s3;

	cout << "=================" << endl;

	Sistem s4 = s3;
	cout << s4;

	cout << "=================" << endl;
	//1.
	cout << s1[0] << endl;
	//2.
	cout << "=================" << endl;
	s4 += "camera noua";
	cout << s4 << endl;
	//3..
	cout << "=================" << endl;
	SistemSupraveghere ss1;
	cin >> ss1;
	cout << ss1;

	cout << "=================" << endl;

	cout << "Apel vitualizare" << endl;
	cout << s1.calculvenit() << endl;
	cout << "=======================+" << endl;
	s1.afisaredetalii();

	cout << "=======================+" << endl;
	//apel container STL

	s1.adaugainregistrare("inregistare 1");
	s1.adaugainregistrare("inregistare 2");
	s1.adaugainregistrare("inregistare 3");
	s1.afisareinregistrare();

}
