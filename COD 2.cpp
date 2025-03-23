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
	char* motor;
	int numarDistanteParcurse; //dimensiunea vectorului distnate parcurse
	int* DistantaParcurse;

	static string tarafabricare;//campul static este un camp care va avea aceeasi valoare pentru toate obiectele clasei
	//campurile statice nu se folosesc in constructori dar pot avea getteri si setteri
	//se initializeaza inafara clasei folosind operatorul de rezolutie.

public:
	//constructor default fara parametri
	Masina() {
		numarlocuri = 2;
		model = "BMW";
		pret = 8000;
		estehibrida = false;
		culoare = VERDE;

		motor = new char[4]; //declaram si initializam campul motor ca fiind un sir de caractere  alocat dinamic ce va ocupa cel mult 4 carartere
		//orice sire de caractere contine la final terminatorul de sir care marcheaza sfarsitul propozitiei
		strcpy_s(motor, 4, "N/A");//strcpy_s reprezinta o functie predefinita care aloca valoare N?A in campul motor
		//strcpy contine 3 parametri : campuri in care punem valoarea default, dimensiunea campului ,valoarea efectiva pe care o va avea camul.

		numarDistanteParcurse = 2;

		DistantaParcurse = new int[numarDistanteParcurse] {200, 300};//initializam campul dinamic distanta parcursa avand ca dimensiune numar distante parcurse,avand ca valori 200,300
		//trebuie sa avem atatea valori cu valoarea pe care i-am dat-o variabilei numarDistanteParcurse.
		//initializam vectorul dinamic de distante parcurse ca fiind un vector ce va avea dimensiunea egala cu numarDistanteParcurse si care va avea ca valori 200,330
	}
	//constructor cu parametri
	Masina(int numarlocuri, string model, float pret, bool estehibrida, Culoare culoare, const char* motor, int numarDistanteParcurse, int DistantaParcurse[]) {
		this->numarlocuri = numarlocuri;
		this->model = model;
		this->pret = pret;
		this->estehibrida = estehibrida;
		this->culoare = culoare;

		this->motor = new char[strlen(motor) + 1];
		strcpy_s(this->motor, strlen(motor) + 1, motor);
		//


		this->numarDistanteParcurse = numarDistanteParcurse;


		this->DistantaParcurse = new int[numarDistanteParcurse];

		for (int i = 0; i < numarDistanteParcurse; i++) {
			this->DistantaParcurse[i] = DistantaParcurse[i];
		}

	}

	//Constructor de copiere
	//este folosit pentru a crea un obiect identic 
	Masina(const Masina& m)
	{
		this->numarlocuri = numarlocuri;
		this->model = model;
		this->pret = pret;
		this->estehibrida = estehibrida;
		this->culoare = m.culoare;

		this->motor = new char[strlen(m.motor) + 1];
		strcpy_s(this->motor, strlen(m.motor) + 1, m.motor);

		this->numarDistanteParcurse = m.numarDistanteParcurse;

		this->DistantaParcurse = new int[numarDistanteParcurse];

		for (int i = 0; i < numarDistanteParcurse; i++) {
			this->DistantaParcurse[i] = m.DistantaParcurse[i];
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
	char* getmotor() {
		return this->motor;

	}

	int getnumaDistanteParcurse() {
		return this->numarDistanteParcurse;
	}

	int* getDistanteParcurse() {
		return this->DistantaParcurse;
	}

	//getter pentru camp static
	static string getTaraFabricare() {
		return tarafabricare;//campurile statice nu pot fi accessate cu (this) fiindca sunt campuri ale clasei nu ale obiectului
	}


	//setter
	// getterii si setteriii reprezinta metode de acces ale clasei (metode accesori)
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
	void setmotor(const char* motornou) {
		delete[]this->motor;
		this->motor = new char[strlen(motornou) + 1];
		strcpy_s(this->motor, strlen(motornou) + 1, motornou);
	}
	void setnumarDistanteParcurse(int numarnouDistanteParcurse) {
		this->numarDistanteParcurse = numarnouDistanteParcurse;
	}

	void setDistantaParcurse(int numarDistantaParcurse, int DistantanoiParcurse[]) {
		delete[]this->DistantaParcurse;
		this->numarDistanteParcurse = numarDistanteParcurse;
		this->DistantaParcurse = new int[numarDistantaParcurse];

		for (int i = 0; i < numarDistantaParcurse; i++) {
			this->DistantaParcurse[i] = DistantanoiParcurse[i];
		}
	}





	//setter pentru static

	static void setTaraFabricare(static string taraNouaFabricare) {
		tarafabricare = taraNouaFabricare;
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

		//1
		if (motor != nullptr) {
			cout << motor << endl;
		}//2
		cout << numarDistanteParcurse << endl;
		//3
		if (this->DistantaParcurse != nullptr) {
			for (int i = 0; i < this->numarDistanteParcurse; i++) {
				cout << this->DistantaParcurse[i] << " ";

			}
			cout << endl;
		}

		cout << Masina::tarafabricare << endl;
	}
	//metoda care calculeaza valoarea masinii care poate fi pret * numar locuri
	float calculvaloaremasina() {
		return this->numarlocuri * this->pret;
	}

	//supraincarcare operatori = insemana a defini un comportament diferit peste un comportamnet deja existent al operatorului
	// egalul are roulul de a atribui o valoare  dar are si are rolul de a crea o clona
	// supraincarcare operatori 
	Masina& operator=(const Masina& m) {
		if (this != &m) {
			this->numarlocuri = m.numarlocuri;
			this->model = m.model;
			this->pret = m.pret;
			this->estehibrida = m.estehibrida;
			this->culoare = m.culoare;

			this->motor = new char[strlen(m.motor) + 1];
			strcpy_s(this->motor, strlen(m.motor) + 1, m.motor);

			this->numarDistanteParcurse = m.numarDistanteParcurse;

			this->DistantaParcurse = new int[numarDistanteParcurse];

			for (int i = 0; i < numarDistanteParcurse; i++) {
				this->DistantaParcurse[i] = m.DistantaParcurse[i];
			}
			return*this;//this reprezinta obiectul curent
		}
	}
	//destructori 
	~Masina() {
		delete[]this->motor;
		delete[]this->DistantaParcurse;


		cout << "destructor apelat cu succes " << endl;
	}
};

//initializare camp static
string Masina::tarafabricare = "Japonia";//toate obiectele vor avea tara fabricare Japonia;



int main() {

	int numarDistanteParcurse = 3;
	int DistanteParcurse[] = { 250, 350, 550 };



	//apel constuctor fara parametri
	Masina m1; //creem un obiect de tip masina cu numele m1 folosind construcotrul fara parametri/ defaul/ implicit
	m1.afisare();
	cout << "====================================" << endl;
	//apel cosntructor cu parametru
	Masina m2(4, "Audi", 10000, true, NEGRU, "I3", numarDistanteParcurse, DistanteParcurse);
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
	cout << "=====================================" << endl;

	//Constructor de copiere

	Masina m3(m2);
	m3.setmotor("IX70");
	int vectornouDistante[] = { 700,300,250 };
	m3.setDistantaParcurse(3, vectornouDistante);
	m3.afisare();

	//apel supraincarcare =

	Masina m4 = m3;
	m4.afisare();



}
