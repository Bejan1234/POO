#include <iostream>
#include <string>

#define TRAINROUTE_H

using namespace std;

class TrainRoute
{
private:
	string departure;
	string destination;
	char* trainCode;

public:
	TrainRoute(string departure, string destination, const char* trainCode)
	{
		this->departure = departure;
		this->destination = destination;
		this->trainCode = new char[strlen(trainCode) + 1];
		strcpy_s(this->trainCode, strlen(trainCode) + 1, trainCode);
	}
	TrainRoute(const TrainRoute& t) {
		this->departure = t.departure;
		this->destination = t.destination;
		this->trainCode = new char[strlen(t.trainCode) + 1];
		strcpy_s(this->trainCode, strlen(t.trainCode) + 1, t.trainCode);
	}

	TrainRoute& operator=(const TrainRoute& t)
	{
		if (this != &t)
		{
			delete[] trainCode;
		this->departure = t.departure;
		this->destination = t.destination;
		this->trainCode = new char[strlen(t.trainCode) + 1];
		strcpy_s(this->trainCode, strlen(t.trainCode) + 1, t.trainCode);
			
		}
		return *this;
	}


	virtual ~TrainRoute() {
		delete[] trainCode;
	}

	virtual float totalWeight() const {
		
		return 0.0f; 
	}

	

	friend ostream& operator<<(ostream& o, const TrainRoute& t);
	friend istream& operator>>(istream& i, TrainRoute& t);

};

ostream& operator<<(ostream& o, const TrainRoute& t) {
	o << "Departure: " << t.departure << "\n";
	o << "Destination: " << t.destination << "\n";
	o << "Train code: " << t.trainCode << "\n";
	return o;
}
istream& operator>>(istream& i, TrainRoute& t) {
	string tempDeparture, tempDestination, tempTrainCode;

	cout << "Enter Departure: ";
	getline(i >> ws, tempDeparture);
	cout << "Enter Destination: ";
	getline(i >> ws, tempDestination);
	cout << "Enter Train Code: ";
	getline(i >> ws, tempTrainCode);

	t.departure = tempDeparture;
	t.destination = tempDestination;

	delete[] t.trainCode; // Eliberăm memoria existentă
	t.trainCode = new char[tempTrainCode.length() + 1];
	strcpy_s(t.trainCode, tempTrainCode.length() + 1, tempTrainCode.c_str());

	return i;
}


class FreightTrainRoute : public TrainRoute
{
private:
	int nbOfWagons;
	float* weigthPerWagon;

public:
	FreightTrainRoute() : TrainRoute("", "", "Necunoscut")
	{
		nbOfWagons = 0;
		weigthPerWagon = nullptr;

	}

	FreightTrainRoute(string departure, string destination, const char* trainCode)
		: TrainRoute(departure, destination, trainCode) {
		nbOfWagons = 0;
		weigthPerWagon = nullptr;
	}

	void setWeigth(int nbOfWagons, float* weightPerWagon)
	{
		delete[] this->weigthPerWagon;
		this->nbOfWagons = nbOfWagons;

		if (nbOfWagons > 0) {
			this->weigthPerWagon = new float[nbOfWagons];
			for (int i = 0; i < nbOfWagons; i++) {
				this->weigthPerWagon[i] = weightPerWagon[i];
			}
		}
		else {
			
			this->weigthPerWagon = nullptr;
		}
	}
	~FreightTrainRoute() {
		delete[] weigthPerWagon;

	}
	FreightTrainRoute(const FreightTrainRoute& f)
		: TrainRoute(f), nbOfWagons(f.nbOfWagons), weigthPerWagon(nullptr) {
		if (f.weigthPerWagon != nullptr) {
			this->weigthPerWagon = new float[f.nbOfWagons];
			for (int i = 0; i < f.nbOfWagons; i++) {
				this->weigthPerWagon[i] = f.weigthPerWagon[i];
			}
		}
	}
	FreightTrainRoute& operator=(const FreightTrainRoute& f) {
		if (this != &f) {
			TrainRoute::operator=(f);

			delete[] weigthPerWagon;

			this->nbOfWagons = f.nbOfWagons;
			if (f.weigthPerWagon != nullptr) {
				this->weigthPerWagon = new float[f.nbOfWagons];
				for (int i = 0; i < f.nbOfWagons; i++) {
					this->weigthPerWagon[i] = f.weigthPerWagon[i];
				}
			}
			else {
				this->weigthPerWagon = nullptr;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& o, const FreightTrainRoute& f);
	friend istream& operator>>(istream& i, FreightTrainRoute& f);



	float totalWeight() const override { 
		float totalWagonWeight = 0.0f;

		
		for (int j = 0; j < nbOfWagons; ++j) {
			totalWagonWeight += weigthPerWagon[j];
		}

		
		float total = TrainRoute::totalWeight() + totalWagonWeight;

		return static_cast<int>(total);
	}


};
ostream& operator<<(ostream& o, const FreightTrainRoute& f) {
	
	o << static_cast<const TrainRoute&>(f);

	
	o << "Nb of wagons: " << f.nbOfWagons << "\n";
	o << "Weigth per wagon: ";
	for (int i = 0; i < f.nbOfWagons; i++) {
		o << static_cast<int>(f.weigthPerWagon[i]) << " "; // Trunchiem la partea întreagă
	}
	o << "\n";

	return o;
}
istream& operator>>(istream& i, FreightTrainRoute& f) {
	
	i >> static_cast<TrainRoute&>(f);

	cout << "Enter number of wagons: ";
	i >> f.nbOfWagons;

	
	delete[] f.weigthPerWagon;

	if (f.nbOfWagons > 0) {
		f.weigthPerWagon = new float[f.nbOfWagons];
		cout << "Enter weights per wagon (space-separated): ";
		for (int j = 0; j < f.nbOfWagons; j++) {
			i >> f.weigthPerWagon[j];
		}
	}
	else {
		f.weigthPerWagon = nullptr;
	}

	return i;
}






//ATENTIE!!!
//* Sunt punctate doar solutiile originale si individuale
//* Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//* Signatura functiilor se poate modifica doar pentru a realiza supradefinirea
//* Utilizarea valorilor din teste pentru a obtine rezultate fals pozitive este considerata frauda

//1. Modificati constructorul cu parametri din clasa TrainRoute pentru a initializa
//statia de plecare, statia de sosire si codul trenului

//2. Respectati "regula celor 3" in cadrul clasei TrainRoute

//3. Modificati operatorul de scriere la consola pentru a afisa informatiile despre ruta
//se pot folosi functii friend sau getteri
//afisarea va fi de forma:
//Departure: departure
//Destination: destination
//Train code: trainCode

//Modificati operatorul de citire de la consola pentru a citi informatii despre ruta
//se vor citi in ordine urmatoarele informatii (fiecare pe o linie noua)
//Departure
//Destination
//Train code
//se pot folosi setteri sau functii friend
//operatorul trebuie sa poata citi siruri de caractere ce contin spatii

//4. Modificati constructorul implicit al clasei FreightTrainRoute
//acesta va initializa numarul de vagoane cu 0 si vectorul de greutati cu nullptr
//statia de plecare si destinatia vor fi initializate cu un sir vid
//codul trenului va fi "Necunoscut"

//5. Modificati constructorului cu parametri al clasei FreightTrainRoute
//astfel incat sa initializeze corect statia de plecare, destinatia si codul trenului
//numarul de vagoane si vectorul de greutati vor ramane 0, respectiv nullptr
//clasa TrainCode nu se poate modifica pentru a contine constructor implicit

//6. Modificati metoda setWeigth astfel incat sa se poata modifica
//vectorul de greutati si numarul de vagoane

//7. Aplicati "regula celor 3" si in clasa derivata

//8. Supraincarcati operatorii de citire si afisare pentru clasa derivata
//cel de afisarea arata in plus urmatoarele linii la consola
//Nb of wagons: nbOfWagons
//Weigth per wagon: weigth1 weigth2 etc.
//se va afisa doar partea intreaga a greutatilor (fara zecimale)
//cel de citire va citi in continuare numarul de vagoane de pe o linie noua
//si greutatile separate prin spatii

//9. Supradefiniti metoda totalWeight in clasa FreightTrainRoute
//astfel incat sa returneze greutatea totala a trenului ca intreg
//prin trunchiere (se ignora zecimalele rezultatului final)

//10. Evitati memory leaks generate odata cu virtualizarea

int main()
{
	//Playgroud
	//Testati aici functiile dorite si folositi debugger-ul pentru eventualele probleme
}