#ifndef _PLH_
#define _PLH_
#include <string>

class Polynom
{
private:
	const static unsigned int mainpower = 40;
	size_t len;
	int* variables;


	unsigned int __midLenPolynom(const Polynom& plA, const Polynom& plB, Polynom& savePlA, Polynom& savePlB);
	void __extendPolynom(unsigned int lenNew, const Polynom& plA, const Polynom& plB, Polynom& savePlA, Polynom& savePlB);
	void __fillVariables(unsigned int len, int num);
	unsigned int __minPower(const Polynom& plA, const Polynom& plB);


public:
	Polynom(const std::string& s);
	Polynom(const Polynom& pl);
	Polynom();
	~Polynom();
	void writePolynom(const std::string& str);
	void print_Equation();


	void add(const Polynom& plB);
	void subtract(const Polynom& plB);
	void multiplication(const Polynom& plB);
	void multiplication(int scalar);
	void mod(Polynom& unitPl, Polynom& remainsPl, const Polynom& plB, int mods);
	bool logic_mathematical_operations(char sign, std::string user_consol_polunom);


	Polynom& operator= (const Polynom& pl);
	size_t getLen() { return this->len; }
	void setVariables(const int* arrint, const int lenarr);
};


#endif
