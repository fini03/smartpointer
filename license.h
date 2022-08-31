#ifndef LICENSE_H
#define LICENSE_H
#include<iostream>
#include<stdexcept>
#include<map>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<memory>
using namespace std;
class License {
	std::string name; //Name der austellenden Gilde
	unsigned int salary; //Lohn einer Aufgabe
	unsigned int counter{0}; //Anzahl der bereits getaetigten Aufgaben
	public:
	License(std::string name, unsigned int salary);
	std::string get_guildname() const; //Liefert den Namen der ausstellenden Gilde.
	unsigned int get_salary() const; //Liefert den Lohn einer Aufgabe.
	bool valid() const; //Liefert true, falls maximal 3 Aufgaben erst getaetigt wurden, ansonsten false
	bool use(); // false -> Lizenz nicht mehr gueltig; Anzahl der getaetigten Aufgaben um eins erhoeht und true zurueckgeliefert.
	std::ostream& print(std::ostream& o) const;
};
std::ostream& operator<<(std::ostream& o, const License& l);
#endif
