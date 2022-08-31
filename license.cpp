#include"license.h"
using namespace std;
License::License(std::string name, unsigned int salary) : name{name}, salary{salary} {
	if(name.empty()) {
		throw std::runtime_error ("Name is empty!\n");	
	}
	if(salary <= 0) {
		throw	std::runtime_error ("Salary is negative!\n");
	}
}
std::string License::get_guildname() const {
	return name;
}
unsigned int License::get_salary() const {
	return salary;
}
bool License::valid() const {
	return counter <= 3;
}
bool License::use() {
	if(!valid()) {
		return false;	
	}
	++counter;
	return true;
}
std::ostream& License::print(std::ostream& o) const {
	return o << "[License for " << name << ", Salary: " << salary << ", Used: " << counter << ']';
}
std::ostream& operator<<(ostream& o, const License& l) {
	return l.print(o);
}
