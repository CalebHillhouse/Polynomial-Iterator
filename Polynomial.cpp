#include "Polynomial.h"
#include <sstream>
#include <cctype>
using namespace std;

Polynomial::Polynomial(string line)
{
	istringstream tokens(line);
	char next_char;
	bool term_parsed = false;
	int coef = 0;
	int expo = 0;
	bool caret_found = false;
	bool sign_negative = false;
	bool coef_finished = false;
	bool expo_finished = false;


	while (tokens >> next_char)
	{
		if (isdigit(next_char))
		{
			tokens.putback(next_char);
			int value;
			tokens >> value;
			if (!caret_found)
			{
				coef = value;
				if (sign_negative)
				{
					coef *= -1;
					sign_negative = false;
				}
				coef_finished = true;
			}
			else
			{
				expo = value;
				if (sign_negative)
				{
					expo *= -1;
				}
				expo_finished = true;
			}
		}
		if (next_char == '-' && !sign_negative)
			sign_negative = true;
		else if (next_char == '-' && sign_negative)
			sign_negative = false;
		if (next_char == '^')
			caret_found = true;
		if (isalpha(next_char))
		{
			if (!coef_finished && !sign_negative)
			{
				coef = 1;
				coef_finished = true;
			}
			else if (!coef_finished && sign_negative)
			{
				coef = -1;
				coef_finished = true;
				sign_negative = false;
			}
			expo = 1;
		}
		if (coef_finished && !caret_found && (next_char == '-' || next_char == '+'))
		{
			term_parsed = true;
			tokens.putback(next_char);
		}
		if (expo_finished && (next_char == '-' || next_char == '+'))
		{
			term_parsed = true;
			tokens.putback(next_char);
		}
		if (!(tokens >> next_char))//expression finished
		{
			term_parsed = true;
		}
		else
			tokens.putback(next_char);
		if (term_parsed)
		{
			Term new_term(coef, expo);
			m_polynomial.push_back(new_term);
			term_parsed = false;
			coef = 0;
			expo = 0;
			caret_found = false;
			sign_negative = false;
			coef_finished = false;
			expo_finished = false;
		}
	}
}

void Polynomial::insert(Term item) {

	list<Term>::iterator it = m_polynomial.begin();

	do {
		if (it == m_polynomial.end())
		{
			m_polynomial.insert(it, item);
			return;
		}
		else if (*it > item)
		{							// adds a term to the polynomial list in order.
			++it;					// if terms have equal exponents
		}							// it will combine the terms
		else if (*it == item)
		{
			*it = *it + item;
			return;
		}
		else if (*it < item)
		{
			m_polynomial.insert(it, item);
			return;
		}
	} while (it != m_polynomial.end());
	m_polynomial.push_back(item);
}

Polynomial Polynomial::operator+(Polynomial rhs)
{
	//logic here is to add the two polynomials.
	
	list<Term>::iterator rhsTempTerm;
	list<Term>::iterator lhsTempTerm;
	Term temp;
	string nada = "";
	Polynomial sumPoly(nada);


	for (rhsTempTerm = rhs.m_polynomial.begin(); rhsTempTerm != rhs.m_polynomial.end(); ++rhsTempTerm)
	{
		bool added = false;
		for (lhsTempTerm = m_polynomial.begin(); lhsTempTerm != m_polynomial.end(); ++lhsTempTerm)
		{
			if (lhsTempTerm->get_exponent() == rhsTempTerm->get_exponent())
			{
				temp.SetData(lhsTempTerm->get_coefficient() + rhsTempTerm->get_coefficient(), lhsTempTerm->get_exponent());
				lhsTempTerm->clear();
				added = true;
			}
		}
		if (!added)
		{
			temp.SetData(rhsTempTerm->get_coefficient(), rhsTempTerm->get_exponent());
		}
		sumPoly.insert(temp);
	}
	for (lhsTempTerm = m_polynomial.begin(); lhsTempTerm != m_polynomial.end(); ++lhsTempTerm)
	{
		temp.SetData(lhsTempTerm->get_coefficient(), lhsTempTerm->get_exponent());
		sumPoly.insert(temp);
	}
	return sumPoly;
}

ostream& operator<<(ostream& os, Polynomial& poly)
{
	list<Term>::iterator tempTerm;
	for (tempTerm = poly.m_polynomial.begin(); tempTerm != poly.m_polynomial.end(); ++tempTerm)
	{
		if (tempTerm->get_coefficient() > 0 && tempTerm != poly.m_polynomial.begin())
		{
			cout << '+';
		}
		os << *tempTerm;
	}
	return os;
}