#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class TrainRoute {
private:
    string departure;
    string destination;

    int nbOfStops;
    //vectorul de distante dintre opriri
    //acesta va avea nbOfStops-1 elemente
    
    int* distances;
    char* trainCode;

public:


    TrainRoute(string departure, string destination) {
        this->departure = departure;
        this->destination = destination;
        this->nbOfStops = 0;
        this->distances = nullptr;
        this->trainCode = nullptr;
    }

    void setTrip(int* distancesnew, int nbOfStops)
    {
        delete[]this->distances;
        this->nbOfStops = nbOfStops;
        this->distances = new int[nbOfStops - 1];

        for (int i = 0; i < nbOfStops - 1; i++) {
            this->distances[i] = distancesnew[i];
        }

    }

    void setTrainCode(const char* trainCode) {
        if (this->trainCode != nullptr) {
            delete[] this->trainCode;
        }
        if (trainCode != nullptr) {
            this->trainCode = new char[strlen(trainCode) + 1];
            strcpy_s(this->trainCode, strlen(trainCode) + 1, trainCode);
        }
        else {
            this->trainCode = nullptr;
        }
    }

    TrainRoute(const TrainRoute& t) {
        this->departure = t.departure;
        this->destination = t.destination;
        this->nbOfStops = t.nbOfStops;

        if (t.distances != nullptr) {
            this->distances = new int[nbOfStops - 1];
            for (int i = 0; i < nbOfStops - 1; i++) {
                this->distances[i] = t.distances[i];
            }
        }
        else {
            this->distances = nullptr;
        }

        if (t.trainCode != nullptr) {
            this->trainCode = new char[strlen(t.trainCode) + 1];
            strcpy_s(this->trainCode, strlen(t.trainCode) + 1, t.trainCode);
        }
        else {
            this->trainCode = nullptr;
        }
    }

    ~TrainRoute() {
        if (distances != nullptr) {
            delete[] distances;
        }
        if (trainCode != nullptr) {
            delete[] trainCode;
        }
    }

    TrainRoute& operator=(const TrainRoute& t) {
        if (this != &t) {
            delete[] distances;
            delete[] trainCode;

            this->departure = t.departure;
            this->destination = t.destination;
            this->nbOfStops = t.nbOfStops;

            if (t.distances) {
                this->distances = new int[t.nbOfStops - 1];
                for (int i = 0; i < t.nbOfStops - 1; i++) {
                    this->distances[i] = t.distances[i];
                }
            }
            else {
                this->distances = nullptr;
            }

            if (t.trainCode) {
                this->trainCode = new char[strlen(t.trainCode) + 1];
                strcpy_s(this->trainCode, strlen(t.trainCode) + 1, t.trainCode);
            }
            else {
                this->trainCode = nullptr;
            }
        }
        return *this;
    }

   

    bool operator<(TrainRoute t) {
        int thisTotal = 0;
        int otherTotal = 0;

        for (int i = 0; i < this->nbOfStops - 1; i++) {
            thisTotal += this->distances[i];
        }
        for (int i = 0; i < t.nbOfStops - 1; i++) {
            otherTotal += t.distances[i];
        }

        return thisTotal < otherTotal;
    }

    void operator+=(int distance) {
        int* newDistances = new int[nbOfStops];
        for (int i = 0; i < nbOfStops - 1; i++) {
            newDistances[i] = distances[i];
        }
        newDistances[nbOfStops - 1] = distance;

        delete[] distances;
        distances = newDistances;
        nbOfStops++;
    }

    friend ofstream& operator<<(ofstream& out, const TrainRoute& r) {
        out << r.departure << endl;
        out << r.destination << endl;
        out << (r.trainCode ? r.trainCode : "null") << endl;
        out << r.nbOfStops << endl;
        for (int i = 0; i < r.nbOfStops - 1; i++) {
            out << r.distances[i] << " ";
        }
        out << endl;
        return out;
    }

    friend ifstream& operator>>(ifstream& in, TrainRoute& r) {
        string dep, dest, code;
        getline(in, dep);
        getline(in, dest);
        getline(in, code);

        r = TrainRoute(dep, dest);
        if (code != "null") {
            r.setTrainCode(code.c_str());
        }

        int stops;
        in >> stops;
        if (stops > 1) {
            int* dist = new int[stops - 1];
            for (int i = 0; i < stops - 1; i++) {
                in >> dist[i];
            }
            r.setTrip(dist, stops);
            delete[] dist;
        }
        in.ignore();
        return in;
    }

    void serialize(string fileName) {
        ofstream f(fileName, ios::binary);
        int depLen = departure.length();
        int destLen = destination.length();
        int tcLen = (trainCode ? strlen(trainCode) : 0);

        f.write((char*)&depLen, sizeof(int));
        f.write(departure.c_str(), depLen);
        f.write((char*)&destLen, sizeof(int));
        f.write(destination.c_str(), destLen);
        f.write((char*)&tcLen, sizeof(int));
        if (tcLen > 0) {
            f.write(trainCode, tcLen);
        }
        f.write((char*)&nbOfStops, sizeof(int));
        if (nbOfStops > 1) {
            f.write((char*)distances, (nbOfStops - 1) * sizeof(int));
        }
        f.close();
    }

    void deserialize(string fileName) {
        ifstream f(fileName, ios::binary);
        int depLen, destLen, tcLen;

        f.read((char*)&depLen, sizeof(int));
        char* depBuf = new char[depLen + 1];
        f.read(depBuf, depLen);
        depBuf[depLen] = '\0';
        departure = depBuf;
        delete[] depBuf;

        f.read((char*)&destLen, sizeof(int));
        char* destBuf = new char[destLen + 1];
        f.read(destBuf, destLen);
        destBuf[destLen] = '\0';
        destination = destBuf;
        delete[] destBuf;

        f.read((char*)&tcLen, sizeof(int));
        if (trainCode != nullptr) delete[] trainCode;
        if (tcLen > 0) {
            trainCode = new char[tcLen + 1];
            f.read(trainCode, tcLen);
            trainCode[tcLen] = '\0';
        }
        else {
            trainCode = nullptr;
        }

        if (distances != nullptr) delete[] distances;
        f.read((char*)&nbOfStops, sizeof(int));
        if (nbOfStops > 1) {
            distances = new int[nbOfStops - 1];
            f.read((char*)distances, (nbOfStops - 1) * sizeof(int));
        }
        else {
            distances = nullptr;
        }
        f.close();
    }

    string getDeparture() const { return departure; }
    string getDestination() const { return destination; }
    char* getTrainCode() const { return trainCode; }
    int getNbOfStops() const { return nbOfStops; }
    int* getDistances() const { return distances; }
};

ostream& operator<<(ostream& out, TrainRoute r) {
    out << "Departure: " << r.getDeparture() << endl;
    out << "Destination: " << r.getDestination() << endl;
    out << "Train code: " << (r.getTrainCode() ? r.getTrainCode() : "N/A") << endl;
    out << "Number of stops: " << r.getNbOfStops() << endl;
    out << "Distances between stops: ";
    if (r.getNbOfStops() > 1) {
        for (int i = 0; i < r.getNbOfStops() - 1; i++) {
            out << r.getDistances()[i] << " ";
        }
    }
    out << endl;
    return out;
}

istream& operator>>(istream& in, TrainRoute& r) {
    string departure, destination, trainCode;
    int nbOfStops;

    cout << "Departure: ";
    getline(in, departure);

    cout << "Destination: ";
    getline(in, destination);

    r = TrainRoute(departure, destination);

    cout << "Train code: ";
    getline(in, trainCode);
    r.setTrainCode(trainCode.c_str());

    cout << "Number of stops: ";
    in >> nbOfStops;
    in.ignore();

    if (nbOfStops > 1) {
        int* distances = new int[nbOfStops - 1];
        for (int i = 0; i < nbOfStops - 1; i++) {
            cout << "Distance " << i + 1 << ": ";
            in >> distances[i];
            in.ignore();
        }
        r.setTrip(distances, nbOfStops);
        delete[] distances;
    }

    return in;
}

//ATENTIE!!!
//* Sunt punctate doar solutiile originale si individuale
//* Orice incercare de frauda va duce la pierderea intregului punctaj de la seminar
//* Signatura functiilor nu se poate modifica, doar continului lor
//* Utilizarea valorilor din teste pentru a obtine rezultate fals pozitive este considerata frauda

//1. Modificati constructorul cu parametri pentru a initializa
//statia de plecare si statia de sosire
//numarul de opriri va fi initializat cu 0, iar cei doi vectori
//(vectorul de distante si codul trenului) cu null

//2. Modificati metoda setTrip astfel incat vectorul existent de distante
//sa fie inlocuit de cel primit drept parametru
//nu uitati faptul ca vectorul are cu un element mai putin decat numarul de statii

//3. Modificati metoda setTrainCode pentru a inlocui codul existent
//cu cel primit drept parametru

//4. Respectati "regula celor 3" in cadrul clasei de mai sus

//5. Modificati supraincarcarea operatorului <
//acesta va returna true daca distanta totala a rutei reprezentata de primul operand
//este mai mica decat distanta totala a rutei reprezentate de al doilea operand

//6. Modificati operatorul += pentru a adauga un element in vectorul de distante
//numarul de statii va fi de asemenea incrementat

//7. Modificati operatorul de scriere la consola pentru a afisa informatiile despre ruta
//se pot folosi functii friend sau getteri
//afisarea va fi de forma:
//Departure: departure
//Destination: destination
//Train code: trainCode
//Number of stops: nbOfStops
//Distances between stops: distance1 distance2 distance3 etc

//8. Modificati operatorul de citire de la consola pentru a citi informatii despre ruta
//se vor citi in ordine urmatoarele informatii (fiecare pe o linie noua)
//Departure
//Destination
//Train code
//Number of stops
//distance 1
//distance 2
//distance 3
//etc
//se pot folosi setteri sau functii friend
//operatorul trebuie sa poata citi siruri de caractere ce contin spatii

//9. Supraincarcati operatorii de scriere si citire din fisiere text
//operatorii functioneaza pe fisiere text deschise deja
//ordinea sau formatul nu conteaza atata vreme cat obiectul scris
//poate fi citit ulterior din fisier si va avea aceleasi atribute

//10. Modificati metodele serialize si deserialize pentru a scrie
//si a citi obiectul curent de clasa TrainRoute intr-un/dintr-un fisier binar
//se vor serializa toate campurile (ordinea nu conteaza)
//numele fisierului este primit drept parametru
//metodele deschid si inchid fisierele specificate

int main()
{
    //Playgroud
    //Testati aici functiile dorite si folositi debugger-ul pentru eventualele probleme
}