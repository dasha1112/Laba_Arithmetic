#ifndef _MONOM_
#define _MONOM_
#include "TVector.h"

class TMonom 
{
protected:
	double C; // Коэффицент
	TVector<double> degrees; // Степени
public:
	TMonom();
	TMonom(double _c, TVector<double> _d = 0.0);
	TMonom(const TMonom& p);

	int GetDimension();
	double GetC() const;
	TVector<double>& GetDegrees();
	void SetC(double _c);
	void SetDegrees(TVector<double>& _d);

	void Clear();
	TMonom operator + (TMonom& p);
	TMonom operator - (TMonom& p);
	TMonom operator * (TMonom& p);
	TMonom& operator = (const TMonom& p);
	bool operator == (TMonom& p);
	bool operator != (TMonom& p);
	bool operator < (TMonom& p);
	bool operator > (TMonom& p);
	double operator () (const TVector<double>& value);
	friend ostream& operator<< (ostream& out, const TMonom& monom);
	friend istream& operator >> (istream& in, TMonom& monom);
};
#endif