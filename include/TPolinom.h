#ifndef _POLINOM_
#define _POLINOM_
#include "TMonom.h"
#include "MyList.h"

class TPolinom :protected TList<TMonom> 
{
public:
	TPolinom();
	TPolinom(const TPolinom& p);
	void AddMonom(TMonom mon);
	~TPolinom();

	TPolinom operator +(TPolinom& p);
	TPolinom operator -(TPolinom& p);
	TPolinom operator *(TPolinom& p);
	TPolinom operator *(double p);
	TPolinom& operator = (TPolinom& p);
	TPolinom& operator += (TMonom& m);
	TPolinom& operator -= (TMonom m);
	TPolinom& operator *= (TMonom m);
	bool operator == (const TPolinom& p);
	bool operator != (const TPolinom& p);
	int GetCount();
	friend ostream& operator<< (ostream& out, const TPolinom& polinom);
	friend istream& operator >> (istream& in, TPolinom& polinom);
};
#endif