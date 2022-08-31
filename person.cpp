#include"license.h"
#include"guild.h"
#include"person.h"
using namespace std;
Person::Person(std::string name, unsigned int wealth) : name{name}, wealth{wealth} {
	if(name.empty()) {
		throw std::runtime_error("Name is empty!\n");
	}
}
void Person::work(std::string guild) {
	if(eligible(guild)) {
		if(licenses[guild]->use()) {
			work(licenses[guild]->get_salary());
		}
		else {
			throw std::runtime_error("License is not useable!\n");
		}
	}
	else {
		throw std::runtime_error("License not found!\n");
	}
}
void Person::increase_wealth(unsigned int i) {
	wealth+=i;
}
std::string Person::get_name() const {
	return name;
}
bool Person::pay_fee(unsigned int i) {
	if(wealth < i || i == 0) {
		return false;
	}
	wealth-=i;
	return true;
}
void Person::receive_license(unique_ptr<License> l) {
	if(licenses.find(l->get_guildname()) != licenses.end()) {
		licenses.erase(l->get_guildname());
  }
	licenses.insert(pair<string, unique_ptr<License>> {l->get_guildname(), move(l)});
}
void Person::transfer_license(std::string l, shared_ptr<Person> p) {
	if(eligible(l)) {
		p->receive_license(move(licenses[l]));
		licenses.erase(l);
	}
	else {
		throw std::runtime_error("License not found!\n");
	}
}
bool Person::eligible(std::string l) const {
	for(const auto& lic : licenses) {
		if((lic.first == l) && ((lic.second)->valid())) {
			return true;
		}
	}
	return false;
}
std::ostream& Person::print(std::ostream& o) const {
	o << name << ", " << wealth << " Coins, {";
	bool first{true};
	for(const auto& l : licenses)  {
		if(first) {
			o << *(l.second);
			first = false;		
		}
		else {
			o << ", " << *(l.second);	
		}
	}
	o << "}]";
	return o;
}
Worker::Worker(std::string name, unsigned int wealth) : Person{name, wealth} {}
void Worker::work(unsigned int i) {
	increase_wealth(i);
}
std::ostream& Worker::print(std::ostream& o) const {
	o << "[Worker ";
	return Person::print(o);
}
Superworker::Superworker(unsigned int fee, std::string name, unsigned int wealth) : Person{name, wealth}, fee{fee} {}
void Superworker::work(unsigned int i) {
	increase_wealth(i+fee);
}
std::ostream& Superworker::print(std::ostream& o) const {
	o << "[Superworker ";
	return Person::print(o);
}
std::ostream& operator<<(std::ostream& o, const Person& p) {
	return p.print(o);
}
