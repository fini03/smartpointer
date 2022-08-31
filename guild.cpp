#include"license.h"
#include"guild.h"
#include"person.h"

Guild::Guild(std::string name, unsigned int fee, unsigned int sal, const std::vector<shared_ptr<Person>>& mem) : name{name}, fee{fee}, salary{sal} {
	if(name.empty()) {
		throw std::runtime_error("Name is empty!\n");	
	}
	if(fee <= 0 || salary <= 0) {
		throw std::runtime_error("Fee or Salary is negative!\n");	
	}
	for(const auto& m : mem) {
		size_t found{0};
		for(const auto& m2 : mem) {
			if(m == m2) {
				++found;			
			}		
		}
		if(found > 1) {
			throw std::runtime_error("Double accurance of a member!\n");
		}	
	}
	for(const auto& m : mem) {
		members[m->get_name()] = m;
	}
}
bool Guild::add_member(shared_ptr<Person> p) {
	for(const auto& m : members) {
    		if(m.second == p) {
      			return false;
		}
  	}
	//members[name] = p;
	members.insert(pair<const std::string, shared_ptr<Person>> {p->get_name(), p});
	return true;
}
bool Guild::remove_member(std::string n) {
	for(const auto& m : members) {
    		if(m.first == n) {
      			members.erase(n);
    			return true;
    		}
  	}
	return false;
}
void Guild::grant_license(std::string n) {
	bool found{false};
	for(const auto& m : members) {
		if(m.first == n) {
			found = true;
			if(members[n]->pay_fee(fee)) {
				unique_ptr<License> l(new License(name, salary));
				members[n]->receive_license(move(l));
			}
			else {
				throw std::runtime_error("Not enough money!\n");
			}
		}
	}
	if(!found) {
			throw std::runtime_error("This person is not a guildmember!\n");
	}
}
bool Guild::offer_job(shared_ptr<Person> p) const {
	for(const auto& m : members) {
		if(m.first == p->get_name()) {
			p->work(salary*2);
			return true;
		}
	}
	if(p->eligible(name)) {
		p->work(name);
		return true;
	}
	return false;
}
std::ostream& Guild::print(std::ostream& o) const {
	o << '[' << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";
	bool first{true};
	for(const auto& m : members)  {
		if(first) {
			o << m.first;
			first = false;		
		}
		else {
			o << ", " << m.first;	
		}
	}
	o << "}]";
	return o;
}
std::ostream& operator<<(std::ostream& o, const Guild& g) {
	return g.print(o);
}
