#include "Term.h"

bool Term::operator<(const Term& rhs) const {
	if (Exponent < rhs.Exponent)
		return true;
	else
		return false;
}

bool Term::operator>(const Term& rhs) const {
	if (Exponent > rhs.Exponent)
		return true;
	else
		return false;
}

bool Term::operator==(const Term& rhs) const {
	if (Exponent == rhs.Exponent)
		return true;
	else
		return false;
}

Term Term::operator+(Term rhs) {
	if (Exponent != rhs.Exponent)
		throw invalid_argument("Cannot add two terms with different exponents");
	int new_constant = Coefficient + rhs.Coefficient;
	Term new_term(new_constant, Exponent);
	return new_term;
}

ostream& operator<<(ostream& os, const Term& term) {
	if (term.Exponent == 0)
	{
		if (term.Coefficient == 0)
		{
			return os;
		}
		else 
		{
			os << term.Coefficient;
		}
	}
	else if (term.Exponent > 1 || term.Exponent < 1)
	{
		if (term.Coefficient == 1)
		{
			os << "X^" << term.Exponent;
		}
		else if (term.Coefficient == -1)
		{
			os << "-X^" << term.Exponent;
		}
		else if (term.Coefficient == 0)
		{
			return os;
		}
		else if(term.Exponent != 0)
		{
		os << term.Coefficient << "X^" << term.Exponent;
		}
	}
	else if (term.Exponent == 1)
	{
		if (term.Coefficient == 1)
		{
			os << 'X';
		}
		else if (term.Coefficient == -1)
		{
			os << "-X";
		}
		else if (term.Coefficient == 0)
		{
			return os;
		}
		else
		{
			os << term.Coefficient << 'X';
		}
	}
	return os;
}