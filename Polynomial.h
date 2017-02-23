#include <string>
#include <list>
#include "Term.h"
using namespace std;

class Polynomial
{
public:
	Polynomial(string polynomial);
	void insert(Term item);
	Polynomial operator+(Polynomial rhs);
	friend ostream& operator<<(ostream& os, Polynomial& poly);
private:
	list<Term> m_polynomial;
};