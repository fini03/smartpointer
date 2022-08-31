#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include<stdexcept>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
using namespace std;
class License;
class Person {
	std::string name; //Name der Person
	unsigned int wealth; //Vermoegen
	map<string, unique_ptr<License>> licenses; //Map von aktuellen Lizenzen
	public:
	Person(std::string name, unsigned int wealth = 0);
	virtual ~Person() = default;
	void work(string guild); ////Falls Lizenz für guild vorhanden ist und noch nutzbar ist, wird für das Gehalt von der Lizenz gearbeitet.
	void virtual work(unsigned int) = 0;
	void increase_wealth(unsigned int i); //Erhoeht wealth um i
	std::string get_name() const; //Liefert name
	bool pay_fee(unsigned int i); //Vermoegen um i reduzieren
	void receive_license(unique_ptr<License> l); ///Speichert die Lizenz l in der Map der Lizensen der Person. Falls Lizenz mit dem gleichen Namen vorhanden, ist die alte Lizenz zu zerstoeren.
	void transfer_license(std::string l, shared_ptr<Person> p); //Uebergibt Person p die Lizenz mit dem Namen l und entfernt sie von den Lizenzen vom this-Objekt.
	bool eligible(std::string l) const; ////Liefert true falls eine Lizenz mit Namen l vorhanden ist und diese gültig ist, ansonsten false.
	virtual std::ostream& print(std::ostream& o) const;
};
class Worker : public Person {
	public: 
	Worker(std::string, unsigned int = 0);
	void work(unsigned int i);
	std::ostream& print(std::ostream& o) const;
};
class Superworker : public Person {
	unsigned int fee;
	public:
	Superworker(unsigned int fee, std::string, unsigned int = 0);
	void work(unsigned int i);
	std::ostream& print(std::ostream& o) const;
};
std::ostream& operator<<(std::ostream&, const Person&);
#endif