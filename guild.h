#ifndef GUILD_H
#define GUILD_H
#include<iostream>
#include<stdexcept>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
using namespace std;
class Person;
class License;
class Guild {
	std::string name; //Name der Gilde
	unsigned int fee; //Lizenzgebuehr	
	unsigned int salary; //Gehalt pro Aufgabe
	map<std::string, shared_ptr<Person>> members; //Map von Gildenmitgliedern
	public:
	Guild(std::string name, unsigned int fee, unsigned int sal, const std::vector<shared_ptr<Person>>& members = {});
	bool add_member(shared_ptr<Person> p); //Fuegt Person p der Gilde hinzu, falls nicht schon bereits vorhanden. Liefert true bei Erfolg, ansonst false.
	bool remove_member(std::string n); //Entfernt Person mit Namen n aus der Gilde. Liefert true bei Erfolg, ansonsten false.
	void grant_license(std::string n); //Verkauft Gildenmitglied eine Lizenz der Gilde, sofern sich Person mit Namen n eine Lizenz leisten kann (fee) und ein Mitglied der Gilde ist
	bool offer_job(shared_ptr<Person> p) const; //Bietet Aufgabe Person p an -> arbeitet diese ab. Wenn p Gildenmitglied -> *2 sal + no license; Keine Mitglieder brauchen Lizenz + Gehalt der Lizenz.
	std::ostream& print(std::ostream&) const;
};
std::ostream& operator<<(std::ostream&, const Guild&);
#endif
