#include "TMonom.h"
TMonom::TMonom()
{
  C = 0;
}

TMonom::TMonom(double _c, TVector<double> _d) 
{
  C = _c;
  degrees = _d;
}

TMonom::TMonom(const TMonom& p)
{
  C = p.C;
  degrees = p.degrees;
}

int TMonom::GetDimension() // Количество переменных в мономе
{
  return degrees.Length();
}

double TMonom::GetC() const 
{
  return C;
}


TVector<double>& TMonom::GetDegrees() // Степени переменных
{
   return degrees;
}

void TMonom::SetC(double _c) 
{
  C = _c;
}

void TMonom::SetDegrees(TVector<double>& _d)
{
  degrees = _d;
}

void TMonom::Clear()
{
  C = 0.0;
  degrees.~TVector();
}

TMonom TMonom::operator+(TMonom& p)
{
  if (GetDimension() != p.GetDimension()) // Если количество переменных не совпадает
  {
    throw "Ошибка";
  }
  if (*this != p)
  {
    throw "Ошибка";
  }
  TMonom m = *this;
  m.C = C + p.C;
  return m;
}

TMonom TMonom::operator- (TMonom& p)
{
  if (GetDimension() != p.GetDimension())
  {
    throw "Ошибка";
  }
  if (*this != p)
  {
    throw "Ошибка";
  }
  TMonom m = *this;
  m.C = C - p.C;
  return m;
}

TMonom TMonom::operator*(TMonom& p)
{
  /*if (GetDimension() != p.GetDimension())
  {
    throw "Ошибка";
  }*/
  TMonom m = *this;
  m.C = C * p.C;
  for (int i = 0; i < GetDimension(); i++) 
  {
    m.GetDegrees()[i] = GetDegrees()[i] + p.GetDegrees()[i];
  }
  return m;
}

TMonom& TMonom::operator=(const TMonom& p)
{
  C = p.C;
  degrees = p.degrees;
  return *this;
}

bool TMonom::operator==(TMonom& p)
{
  if (this->degrees.Length()!=p.degrees.Length()) // Если количество переменных не совпадает
  {
    return false;
  }
  for (int i = 0; i < p.GetDimension(); i++) // Проходимся по степеням
  {
    if (degrees[i] != p.degrees[i]) 
    {
      return false;
    }
  }
  return true;
}

bool TMonom::operator!=(TMonom& p)
{
  if (this->degrees.Length() != p.degrees.Length())
  {
    return true;
  }
  for (int i = 0; i < p.GetDimension(); i++)
  {
    if (degrees[i] != p.degrees[i])
    {
      return true;
    }
  }
  return false;
}

bool TMonom::operator<(TMonom& p)
{
  if (this->degrees.Length() != p.degrees.Length())
  {
    return false;
  }
  for (int i = 0; i < p.GetDimension(); i++) {
    if (degrees[i] < p.degrees[i]) {
      return true;
    }
    else if (degrees[i] > p.degrees[i]) {
      return false;
    }
  }
  return false;
}

bool TMonom::operator>(TMonom& p)
{
  if (this->degrees.Length() != p.degrees.Length())
  {
    return false;
  }
  for (int i = 0; i < p.GetDimension(); i++) {
    if (degrees[i] > p.degrees[i]) {
      return true;
    }
    else if (degrees[i] < p.degrees[i]) {
      return false;
    }
  }
  return false;
}

double TMonom::operator()(const TVector<double>& value)
{
    return 0.0;
}

ostream& operator<<(ostream& out, const TMonom& monom)
{
  out << "C: " << monom.GetC()<<"\n";
  out << "Degrees: " << monom.degrees;
  return out;
}

istream& operator>>(istream& in, TMonom& monom)
{
  double c;
  in >> c;
  monom.SetC(c);

  TVector<double> degrees;
  in >> degrees;
  monom.SetDegrees(degrees);

  return in;
}
