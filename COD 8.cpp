#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream> // avem nevoie de aceasta biblioteca pentru fisiere text si binare
using namespace std;
class Marker {
private:
	char* culoare;
	int greutatemarker;
	string producator;
	float pret;
	static int nrmarker;
	int nrmodele;
	string* modele;   // este un vector de stringuri, un vector de cuvinte
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
	Marker(const char* culoare, int greutatemarker, string producator, float pret, int nrmodele, string* modele) {
		this->culoare = new char[strlen(culoare) + 1];
		strcpy_s(this->culoare, strlen(culoare) + 1, culoare);
		this->greutatemarker = greutatemarker;
		this->producator = producator;
		this->pret = pret;
		this->nrmodele = nrmodele;
		this->modele = new string[nrmodele];
		for (int i = 0; i < nrmodele; i++) {
			this->modele[i] = modele[i];
		}
		nrmodele++;
	}
	Marker(const Marker& m) {
		this->culoare = new char[strlen(m.culoare) + 1];
		strcpy_s(this->culoare, strlen(m.culoare) + 1, m.culoare);
		this->greutatemarker = m.greutatemarker;
		this->producator = m.producator;
		this->pret = m.pret;
		this->nrmodele = m.nrmodele;
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
			strcpy_s(this->culoare, strlen(m.culoare) + 1, m.culoare);
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
	friend ostream& operator<<(ostream& out, Marker& m) {
		out << "Culoarea Markerului este: " << m.culoare << "\n";
		out << "Greutatea Markerului este: " << m.greutatemarker << "\n";
		out << "Producatorul Markerului este: " << m.producator << "\n";
		out << "Pretul Markerului este: " << m.pret << "\n";
		out << "Numarul Modelelor este: " << m.nrmodele << "\n";
		out << "Modelele sunt: ";
		for (int i = 0; i < m.nrmodele; i++) {
			out << m.modele[i] << " ";
		}
		out << endl;
		out << m.nrmarker << "\n";
		return out;
	}
	friend istream& operator>>(istream& in, Marker& m) {
		char buffer[100];    // un sir de caractere care stocheaza temporar ce avem in culoare
		cout << "Introduceti buffer: ";
		in >> ws; // ca sa pot afisa un sir cu spatii la consola

		in.getline(buffer, 100);
		delete[] m.culoare;
		m.culoare = new char[strlen(buffer) + 1];
		strcpy_s(m.culoare, strlen(buffer) + 1, buffer);
		cout << "Introduceti greutatea Markerului: ";
		in >> m.greutatemarker;
		cout << "introducet producatorul Markerului: ";
		in >> m.producator;
		cout << "Introduceti pretul Markerului: ";
		in >> m.pret;
		cout << "Introduceti numarul modelelor: ";
		in >> m.nrmodele;
		delete[]m.modele;
		m.modele = new string[m.nrmodele];
		for (int i = 0; i < m.nrmodele; i++) {
			in >> m.modele[i];
		}
		return in;
	}
	bool operator==(const Marker& m) {
		return strcmp(this->culoare, m.culoare) == 0 && this->producator == m.producator;
	}



	//A specializa o clasa inseamna a crea o noua clasa ce va contine toate campurile sin toate functiile din clasa initaiala
	//clasa specializata se mai numeste clasa copil, subclasa, clasa derivata
	// clasa derivata sau clasa copil contine toate campruile si functiile din clasa parinte dar pe langa aceastea ea poate avea campuri si functii proprii
	//clasa care specializaeaza se mai numeste clasa parinte, superclasa, clasa de baza;






	~Marker() {
		delete[]this->culoare;
		delete[]this->modele;
	}
	// scriere in fisier text
	friend ofstream& operator<< (ofstream& out, Marker& m) {
		out << m.culoare << "\n";
		out << m.greutatemarker << "\n";
		out << m.producator << "\n";
		out << m.pret << "\n";
		out << m.nrmodele << "\n";
		for (int i = 0; i < m.nrmodele; i++) {
			out << m.modele[i] << " ";
		}
		out << endl;
		out << m.nrmarker << "\n";
		return out;
	}
	//citire din fisier text
	friend ifstream& operator>>(ifstream& in, Marker& m) {
		char buffer[100];    // un sir de caractere care stocheaza temporar ce avem in culoare
		//cout << "Introduceti buffer: ";
		in >> ws; // ca sa pot afisa un sir cu spatii la consola

		in.getline(buffer, 100);
		delete[] m.culoare;
		m.culoare = new char[strlen(buffer) + 1];
		strcpy_s(m.culoare, strlen(buffer) + 1, buffer);
		//cout << "Introduceti greutatea Markerului: ";
		in >> m.greutatemarker;
		//cout << "introducet producatorul Markerului: ";
		in >> m.producator;
		//cout << "Introduceti pretul Markerului: ";
		in >> m.pret;
		//cout << "Introduceti numarul modelelor: ";
		in >> m.nrmodele;
		delete[]m.modele;
		m.modele = new string[m.nrmodele];
		for (int i = 0; i < m.nrmodele; i++) {
			in >> m.modele[i];
		}
		return in;
	}

};
int Marker::nrmarker = 0;
// facem o clasa copil care va avea toate campurile din clasa de baza
class MarkerElectronic :public Marker {
private:
	int baterie;
	int razaactiune;
	bool arerezerva;
public:
	MarkerElectronic() :Marker() {  // aici practic mostenim parametri din cosntructorul marker
		this->baterie = 0;
		this->razaactiune = 0;
		this->arerezerva = false;
	}
	MarkerElectronic(const char* culoare, int greutatemarker, string producator, float pret, int nrmodele, string* modele, int baterie, int razaactiune, bool arerezerva) : Marker(culoare, greutatemarker, producator, pret, nrmodele, modele) {
		this->baterie = baterie;
		this->razaactiune = razaactiune;
		this->arerezerva = arerezerva;
	}
	MarkerElectronic(const MarkerElectronic& me) :Marker(me) {
		this->baterie = me.baterie;
		this->razaactiune = me.razaactiune;
		this->arerezerva = me.arerezerva;
	}
	MarkerElectronic& operator=(const MarkerElectronic& me) {
		if (this != &me) {
			Marker::operator=(me);
			this->baterie = me.baterie;
			this->razaactiune = me.razaactiune;
			this->arerezerva = me.arerezerva;
		}
		return*this;
	}
	friend ostream& operator<<(ostream& out, MarkerElectronic& me) {
		out << (Marker&)me << endl;
		out << "Nivelul bateriei este: " << me.baterie << "\n";
		out << me.razaactiune << "\n";
		out << me.arerezerva << "\n";
		return out;
	}
	friend istream& operator>>(istream& in, MarkerElectronic& me) {
		in >> (Marker&)me;
		cout << "Introduceti nivelul bateriei: " << endl;
		in >> me.baterie;
		cout << "Introduceti raza de actiune: " << endl;
		in >> me.razaactiune;
		cout << "Introduceti daca are rezerva: " << endl;
		in >> me.arerezerva;
		return in;
	}


};
int main() {
	Marker m1;
	cin >> m1;
	cout << m1;
	cout << "===========================================" << endl;
	Marker m2(m1);
	cout << m2;

	cout << "===========================================" << endl;
	MarkerElectronic me1;
	cin >> me1;
	cout << me1;
	cout << "===========================================" << endl;
	MarkerElectronic me2;
	cin >> me2;
	cout << me2;
	cout << "===========================================" << endl;
	MarkerElectronic me3(me2);
	cout << me3;
	cout << "===========================================" << endl;
	MarkerElectronic me4 = me3;
	cout << me4;
	cout << "===========================================" << endl;
	if (m2 == m1) {
		cout << "Markerele sunt egale" << endl;
	}
	cout << "===========================================" << endl;
	//apel scriere in fisier text
	ofstream fout("Marker.txt", ios::out);
	fout << m1;
	fout.close();

	cout << "===========================================" << endl;
	//apel citire din fisier text
	Marker Markercititdinfisiertext;
	ifstream fin("Marker.txt", ios::in);
	//populam obiectul marker citit din markertfisier text il pupulam cu datele din fisier.txt
	fin >> Markercititdinfisiertext;
	fin.close();
	cout << "============Apel citire apel text============" << endl;
	cout << Markercititdinfisiertext;



	return 0;

} // ce am facut astazi se numeste relatie "IS A"

//intrbari de pus: intraba care e treaba cu protected si daca putem face ceva o aplicatie cu protected
