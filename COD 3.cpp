#define CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
enum Culoare { VERDE, ROSU, NEGRU, BLUE };
class Masina {
private:
	int numarlocuri;					//atributele: variabilele care stocheaza informatii specifice fiecarui obiect creat din aceasta clasa.
	string model;						//De exemplu, in cazul unei clase Masina, atributelele pot fi Numarlocuri, model, pret, estehibrida, culoare	
	float pret;
	bool estehibrida;
	Culoare culoare;
	char* motor;         //
	int NrdistanteParcurse;  //dimensiunea vectorilor distanteparcurse    avem nevoie de un camp care sa stocheze dimensiunea sa
	int* DistanteParcurse;
	static string TaraFabricare;		//Campul static este un camp care va avea aceiasi valoare pentru toate obiectele clasei
	//campurile statice nu se folosesc in constructori dar pot avea getteri si setteri
	//se initializeaza inafara clasei folosind operatorul de rezolutie care este ::
	const int idmasina;
	static int nrmasini;
public:
	Masina() :idmasina(nrmasini++) {				//constructor default fara parametri
		numarlocuri = 2;
		model = "BMW";
		pret = 8000;
		estehibrida = false;
		culoare = VERDE;
		motor = new char[4];    //declaram si initializam campul motor ca fiind un sir de caractere alocat dinamic ce va ocupa cel mmult 4 caractere
		// orice sir de caractere contine la final terminatorul de sir care marcheaza sfarsitul propozitiei	
		strcpy_s(motor, 4, "N/A");  // strcpy_s reprezint o functie predefinita care aloca valoarea n/a in campul motor
		// strcpy contine 3 parametri (ordinea trebuie respectata):   (campul in care punem valoare default, dimensiunea campului declarata mai sus adica 4, valoarea efectiva pe care o va avea campul)
		NrdistanteParcurse = 2;
		DistanteParcurse = new int[NrdistanteParcurse] {200, 300};		// alocam initializam campul dinamic distantaparcursa avand ca dimensiune nrdistanteparcurse, avand ca valori 200 si 300.
		// trebuie sa avem atatea valori cu valoarea pe care i am dato variabile nrdistanteparcurse.
	}
	//constructor cu parametri
	Masina(int _numarlocuri, string model, float pret, bool estehibrida, Culoare culoare, const char* motor, int NrdistanteParcurse, int DistanteParcurse[]) :idmasina(nrmasini++) {
		numarlocuri = _numarlocuri;
		this->model = model;
		this->pret = pret;
		this->estehibrida = estehibrida;
		this->culoare = culoare;
		this->motor = new char[strlen(motor) + 1];
		strcpy_s(this->motor, strlen(motor) + 1, motor);
		this->NrdistanteParcurse = NrdistanteParcurse;
		this->DistanteParcurse = new int[NrdistanteParcurse];
		for (int i = 0; i < NrdistanteParcurse; i++) {
			this->DistanteParcurse[i] = DistanteParcurse[i];
		}
	}
	//Cosntructor de Copiere:
	//Este folosit pentru a crea un obiect identic un obiect deja creat, o copie, o clona
	Masina(const Masina& m) :idmasina(nrmasini++) {
		this->numarlocuri = m.numarlocuri;
		this->model = m.model;
		this->pret = m.pret;
		this->estehibrida = m.estehibrida;
		this->culoare = m.culoare;
		this->motor = new char[strlen(m.motor) + 1];
		strcpy_s(this->motor, strlen(m.motor) + 1, m.motor);
		this->NrdistanteParcurse = m.NrdistanteParcurse;
		this->DistanteParcurse = new int[NrdistanteParcurse];
		for (int i = 0; i < NrdistanteParcurse; i++) {
			this->DistanteParcurse[i] = m.DistanteParcurse[i];
		}
	}
	//getter
	int getnumarlocuri() {
		return this->numarlocuri;
	}
	string getmodel() {
		return this->model;

	}
	float getpret() {
		return this->pret;

	}
	bool getestehibrid() {
		return this->estehibrida;
	}
	Culoare getculoare() {
		return this->culoare;
	}
	static string getTaraFabricare() {
		return TaraFabricare;	// Campurile statice nu pot accesate cu this, deoarece sunt considerate campuri ale clasei dar ale obiectului
	}
	char* getmotor() {
		return this->motor;
	}
	int getNrDistanteParcurse() {
		return this->NrdistanteParcurse;
	}
	int* getDistanteParcurse() {
		return this->DistanteParcurse;
	}
	//setter
	// getterii si setterii reprezinta metode de acces ale clasei (metode accesori)
	// void pentru ca seteaza o valoare nu o si intoarce
	// metodele cu tip de return cum ar fi getterii se apeleaza in main printr un cout pe cand metodele void se apeleaza direct prin obiect (fara cout)
	void setnumarlocuri(int numarnoulocuri) {
		this->numarlocuri = numarnoulocuri;
	}
	void setmodel(string modelnou) {
		this->model = modelnou;
	}
	void setpret(float pretnou) {
		this->pret = pretnou;
	}
	void setestehibrida(bool estehibridanou) {
		this->estehibrida = estehibridanou;
	}
	void setculoare(Culoare culoarenou) {
		this->culoare = culoarenou;
	}
	void setTaraFabricare(static string TaraNouaFabricare) {
		TaraFabricare = TaraNouaFabricare;
	}
	void setmotor(const char* motornou) {
		delete[]this->motor;
		this->motor = new char[strlen(motornou) + 1];
		strcpy_s(this->motor, strlen(motornou) + 1, motornou);

	}
	void setNrDistanteParcurse(int NrdistanteParcurseNou) {
		NrdistanteParcurse = NrdistanteParcurseNou;
	}
	void setDistanteParcurse(int NrdistanteParcurse, int DistantenoiParcurse[]) {
		delete[]this->DistanteParcurse;
		this->NrdistanteParcurse = NrdistanteParcurse;
		this->DistanteParcurse = new int[NrdistanteParcurse];
		for (int i = 0; i < NrdistanteParcurse; i++) {
			this->DistanteParcurse[i] = DistantenoiParcurse[i];
		}
	}
	//metode proprii: 
	//1. metoda de afisare
	//vom afisa la consola toate valorile din obiect
	//2. metoda de calcul valoare masina
	//metoda de afisare mereu este void
	void afisare() {
		cout << "numar locuri: " << this->numarlocuri << endl;
		cout << "model: " << this->model << endl;
		cout << "pret: " << this->pret << endl;
		cout << "estehibrida? " << this->estehibrida << endl;
		cout << "culoarea este: " << this->culoare << endl;
		if (motor != nullptr) {
			cout << motor << endl;
		}
		cout << NrdistanteParcurse << endl;
		if (DistanteParcurse != nullptr) {
			for (int i = 0; i < this->NrdistanteParcurse; i++) {
				cout << this->DistanteParcurse[i] << " ";
			}
			cout << endl;
		}
		cout << Masina::TaraFabricare << endl;
	}
	//metoda care calculeaza valoarea masinii care poate fi pret * numar locuri
	float calculvaloaremasina() {
		return this->numarlocuri * this->pret;
	}

	//Supraincarcare operatori = a defini un comportament diferit peste un comportament deja existent al operatorului
	// egalul are roulul de a atribui o valoare dar poate avea si rolul de a creea o clona
	// supraincare operator egal
	Masina& operator=(const Masina& m) {
		if (this != &m) {
			this->numarlocuri = m.numarlocuri;
			this->model = m.model;
			this->pret = m.pret;
			this->estehibrida = m.estehibrida;
			this->culoare = m.culoare;
			this->motor = new char[strlen(m.motor) + 1];
			strcpy_s(this->motor, strlen(m.motor) + 1, m.motor);
			this->NrdistanteParcurse = m.NrdistanteParcurse;
			this->DistanteParcurse = new int[NrdistanteParcurse];
			for (int i = 0; i < NrdistanteParcurse; i++) {
				this->DistanteParcurse[i] = m.DistanteParcurse[i];
			}
		}
		return *this; //this reprezint obiectul curent adica clona
	}
	//Supraincarcare operator !
	//Verifica daca valoarea unui camp boolean este fals
	bool operator! () {
		return !estehibrida;
	}
	//supraincarcare apel ==
	//verifica daca 2 obiecte sunt egale pe baza anumitor campuri
	bool operator== (const Masina& m) { // pentru char pointer trebuie sa folosim o functie predefinita a C++ 
		return this->numarlocuri == m.numarlocuri && this->model == m.model && strcmp(this->motor, m.motor) == 0; //doua masini sunt egale daca au acelasi numar de locuri care este un int, daca au acelasi model, si daca au acelasi motor.
	}
	//supraincarcare operator <
	bool operator< (const Masina& m) {
		return this->pret < m.pret;
	}
	//supraincarcare operator !=       verifica daca 2 obiecte sunt diferite
	bool operator!=(const Masina& m) {
		return this->pret != m.pret;
	}
	// tema fa operatorul mai mare >

	//supreaincarcare operator [] index
	// are rolul de a accesa un element din vectorul unui obiect , are rolul de a modifica valoarea de la un anumit index din vectorul unui obiect
	int& operator[](int index) {
		if (index >= 0 && index < NrdistanteParcurse) {
			return DistanteParcurse[index];
		}
		else
			cout << "index invalid" << endl;
	}
	//operatorul functie
	//operatorul functie are rolul de a calcula o valoare specifica sau de a extrage anumite valori i anumite situtaii
		// sa se supraincarce  operatorul functie pentru a determina conversia intr o alta moneda data ca parametru a pretului masina

	void operator()(int cursdeschimb) {
		cout << this->pret / cursdeschimb << endl;

	}

	//apel operator tilda ~     il folosim ca sa schimbam starea variabile bool aici dar poate face altceva
	void operator~ () {
		this->estehibrida = !estehibrida;
	}
	//supraincarcare operator <<     este folosit pentru a afisa la consola campurile obiectelor   
	// friend este un keyword care permite unei metode sa acceseze campurile private si protective ale clasei
	friend ostream& operator<<(ostream& out, const Masina& m) {
		out << "numar locuri: " << m.numarlocuri << "\n";
		out << "model: " << m.model << "\n";
		out << "pret: " << m.pret << "\n";
		out << "estehibrida? " << m.estehibrida << "\n";
		out << "culoarea este: " << m.culoare << "\n";
		if (m.motor != nullptr) {
			out << m.motor << "\n";
		}
		out << m.NrdistanteParcurse << endl;
		if (m.DistanteParcurse != nullptr) {
			for (int i = 0; i < m.NrdistanteParcurse; i++) {
				out << m.DistanteParcurse[i] << " ";
			}
			out << "\n";
		}
		out << m.TaraFabricare << endl;
		out << "nrMasina" << m.nrmasini << "\n";
		return out;
	}
	//supraincarcarea operator >>         este folosit pentru a citi de la consola campurile obiectelor de la tastatura
	friend istream& operator>> (istream& in, Masina& m) {
		cout << "indroduceti numarul de locuri" << endl;
		in >> m.numarlocuri;
		cout << "introduceti modelul" << endl;
		in >> m.model;
		cout << "introduceti pretul" << endl;
		in >> m.pret;
		cout << "este masina hibrida? 0 nu 1 da" << endl;
		in >> m.estehibrida;
		cout << "introduceti culoarea: 0 pentru verde 1 pentru rosu 2 pentru negru 3 pentru blue" << endl;
		int optiune;
		in >> optiune;
		if (optiune == 0) {
			m.culoare = VERDE;
		}
		if (optiune == 1) {
			m.culoare = ROSU;
		}
		if (optiune == 2) {
			m.culoare = NEGRU;
		}
		if (optiune == 3) {
			m.culoare = BLUE;
		}
		char aux[100];
		cout << "introduceti motorul" << endl;
		in >> aux;
		delete[]m.motor;
		m.motor = new char[strlen(aux) + 1];
		strcpy_s(m.motor, strlen(aux) + 1, aux);
		cout << "introduceti numarul de distante" << endl;
		in >> m.NrdistanteParcurse;
		cout << "introduceti distantele parcurse" << endl;
		delete[]m.DistanteParcurse;
		m.DistanteParcurse = new int[m.NrdistanteParcurse];
		for (int i = 0; i < m.NrdistanteParcurse; i++) {
			in >> m.DistanteParcurse[i];
		}
		return in;
	}
	// supraincarcare operator conversie
	operator int() {
		return this->pret * this->numarlocuri;
	}


	// Operatorul + pentru a aduna prețurile a două mașini
	float operator+(const Masina& m) const {
		return this->pret + m.pret;
	}

	// Operatorul * pentru a înmulți prețul cu un număr
	float operator*(int factor) const {
		return this->pret * factor;
	}
	// Operatorul * pentru a înmulți prețul cu un număr
	float operator*(int factor) const {
		return this->pret * factor;
	}

	//destructori 
	~Masina() {
		delete[] this->motor;
		delete[] this->DistanteParcurse;

		cout << "destructor apelat cu succes " << endl;
	}
};
// Initializare camp static se intializeaza inafara clasei mereu
string Masina::TaraFabricare = "Japonia";		//toate obiectele vor avea tara fabriucare Japonia;
int Masina::nrmasini = 0;
int main() {
	cout << "====================================" << endl;
	int NrdistanteParcurse = 3;
	int DistanteParcurse[] = { 250, 350, 550 };
	//apel constuctor fara parametri
	Masina m1; //creem un obiect de tip masina cu numele m1 folosind construcotrul fara parametri/ defaul/ implicit
	cin >> m1;
	m1.afisare();
	cout << "====================================" << endl;
	//apel cosntructor cu parametru
	Masina m2(4, "Audi", 10000, true, NEGRU, "I3", NrdistanteParcurse, DistanteParcurse);
	m2.afisare();
	cout << "====================================" << endl;
	//apel getter
	cout << m2.getmodel() << endl;


	//apel setter
	m2.setmodel("Mercedes");
	cout << m2.getmodel() << endl;
	m2.afisare();
	cout << "====================================" << endl;
	cout << m2.calculvaloaremasina() << endl;
	cout << m1.calculvaloaremasina() << endl;

	//Apel constructor de copiere
	Masina m3(m2);
	m3.setmotor("ix70");
	int vectornoudistante[] = { 600, 321, 432 };
	m3.setDistanteParcurse(3, vectornoudistante);
	m3.afisare();
	cout << "====================================" << endl;
	// apel supraincarcare = 
	Masina m4 = m3;
	m4.afisare();
	cout << "====================================" << endl;
	//apel operator negare / not / !
	if (!m4) {   //daca avem operatorul de negare la test trebuie sa avem un camp bool
		cout << "masina nu este hibrida" << endl;
	}
	else {
		cout << "masina este hibrida" << endl;
	}
	cout << "====================================" << endl;
	//apel operator ==
	if (m4 == m3) {
		cout << "m3 si m4 sunt egale....... apel operator ==" << endl;
	}
	else {
		cout << "m3 si m4 nu sunt egale" << endl;
	}
	cout << "====================================" << endl;
	m3.setpret(2000);
	// apelare operator <
	if (m3 < m4) {
		cout << "pretul masinii m3 este mai mica decat pretul masinii m4" << endl;
	}
	else {
		cout << "pretul masinii m3 este mai mare decat pretul masinii m4" << endl;
	}
	cout << "====================================" << endl;
	//apel operator !=
	if (m3 != m4) {
		cout << "preturile sunt diferite" << endl;
	}
	else {
		cout << "preturile sunt aceleasi" << endl;
	}
	cout << "====================================" << endl;
	//apel operator index []
	//primul mod este sa returnam o valoare din vector
	//al doilea mod e sa modificam o valoare din vector
	cout << m2[0] << "   m2[0] este primul vector" << endl;
	m2[0] = 1000;
	cout << m2[0] << "       am afisat dupa ce am schimbat valoarea" << endl;
	cout << "====================================" << endl;
	//apel operator functie
	m4(5);
	cout << "====================================" << endl;
	// apel operator ~
	~m4;
	m4.afisare();
	cout << "====================================" << endl;
	//apel operator <<
	cout << m1;
	cout << "====================================" << endl;
	//apel operator de coversie sau se mai numeste cast
	cout << (int)m1 << endl;

	// Adunăm prețurile celor două mașini
	float pretTotal = m1 + m2;
	cout << "Prețul total al mașinilor: " << pretTotal << endl;

	cout << "====================================" << endl;
	// Înmulțim prețul mașinii m1 cu 2
	float pretNou = m1 * 2;
	cout << "Prețul mașinii m1 după înmulțire: " << pretNou << endl;

}

