#ifndef TERM_H
#define TERM_H

#include <iostream>
#include <string>
using namespace std;

class Term {
public:
	Term() : Coefficient(0), Exponent(0) {}
	Term(int coefficient, int exponent) : Coefficient(coefficient), Exponent(exponent) {}
	int get_coefficient() { return Coefficient; };
	int get_exponent() { return Exponent; };
	void clear() { Exponent = 0; Coefficient = 0; };
	void SetData(int co, int exp) { Coefficient = co; Exponent = exp; };

	friend ostream& operator<<(ostream& os, const Term& term);
	bool operator<(const Term& rhs) const;
	bool operator>(const Term& rhs) const;
	bool operator==(const Term& rhs) const;
	Term operator+(Term rhs);
private:
	int Coefficient;
	int Exponent;
};

#endif