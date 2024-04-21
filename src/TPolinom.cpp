#include "TPolinom.h"

TPolinom::TPolinom():TList <TMonom>::TList()
{
}

TPolinom::TPolinom(const TPolinom& p):TList<TMonom>::TList(p)
{

}

void TPolinom::AddMonom(TMonom mon)
{
  TNode<TMonom>* temp = new TNode<TMonom>(&mon); // Создаем новый узел для добавляемого монома
  if (IsEmpty())
  {
    begin = end = temp; // Если список пуст, новый узел становится началом и концом списка
  }
  else
  {
    end->SetNext(temp); // Устанавливаем новый узел как следующий после текущего последнего узла списка
    temp->SetPrev(end); // Устанавливаем указатель на предыдущий узел для нового узла
    end = temp; // Перемещаем указатель конца списка на новый узел
  }
  count++; // Увеличиваем счетчик элементов списка
}

TPolinom::~TPolinom()
{
  Clear();
}

TPolinom TPolinom::operator+(TPolinom& p)
{
  TPolinom res;
  TNode<TMonom>* i = begin; // Указатель на первый элемент списка
  TNode<TMonom>* j = p.begin; // Указатель на первый элемент второго списка

  while (i != nullptr && j != nullptr)
  {
    if (i->GetData()->GetDegrees() == j->GetData()->GetDegrees()) // Проверяем сравниваем данные узлов
    {
      TMonom* m = new TMonom(i->GetData()->GetC() + j->GetData()->GetC(), i->GetData()->GetDegrees());
      res.PushEnd(m);
      i = i->GetNext(); // Переходим к следующему элементу
      j = j->GetNext();
    }
    else if (i->GetData()->GetDimension() > j->GetData()->GetDimension())
    {
      res.PushEnd(i->GetData());
      i = i->GetNext();
    }
    else
    {
      res.PushEnd(j->GetData());
      j = j->GetNext();
    }
  }

  while (i != nullptr)
  {
    res.PushEnd(i->GetData());
    i = i->GetNext();
  }

  while (j != nullptr)
  {
    res.PushEnd(j->GetData());
    j = j->GetNext();
  }

  return res;
}

TPolinom TPolinom::operator-(TPolinom& p)
{
  TPolinom res;
  TNode<TMonom>* i = begin; // Указатель на первый элемент списка
  TNode<TMonom>* j = p.begin; // Указатель на первый элемент второго списка

  while (i != nullptr && j != nullptr)
  {
    if (i->GetData()->GetDegrees() == j->GetData()->GetDegrees()) // Проверяем сравниваем данные узлов
    {
      TMonom* m = new TMonom(i->GetData()->GetC() - j->GetData()->GetC(), i->GetData()->GetDegrees());
      res.PushEnd(m);
      i = i->GetNext(); // Переходим к следующему элементу
      j = j->GetNext();
    }
    else if (i->GetData()->GetDimension() > j->GetData()->GetDimension())
    {
      res.PushEnd(i->GetData());
      i = i->GetNext();
    }
    else
    {
      res.PushEnd(j->GetData());
      j = j->GetNext();
    }
  }

  while (i != nullptr)
  {
    res.PushEnd(i->GetData());
    i = i->GetNext();
  }

  while (j != nullptr)
  {
    res.PushEnd(j->GetData());
    j = j->GetNext();
  }

  return res;
}

TPolinom TPolinom::operator*(TPolinom& p)
{
  TPolinom res;
  TNode<TMonom>* i = begin;
  while (i != nullptr)
  {
    TNode<TMonom>* j = p.begin;
    while (j != nullptr)
    {
      TMonom* tempMonom = new TMonom(i->GetData()->GetC() * j->GetData()->GetC(), i->GetData()->GetDegrees() * j->GetData()->GetDegrees());
      res.PushEnd(tempMonom);
      j = j->GetNext();
    }
    i = i->GetNext();
  }
  return res;
}

TPolinom TPolinom::operator*(double p)
{
  TPolinom res;
  TNode<TMonom>* i = begin;
  while (i != nullptr)
  {
    TMonom* tempMonom = new TMonom(i->GetData()->GetC() * p, i->GetData()->GetDegrees());
    res.PushEnd(tempMonom);
    i = i->GetNext();
  }
  return res;
}

TPolinom& TPolinom::operator=(TPolinom& p)
{
  if (this == &p) { return *this; }
  if (this != &p) 
  {
    this->Clear(); // Очищаем текущий список мономов  
    TNode<TMonom>* temp = p.GetBegin();// Копируем мономы из списка p в текущий объект
    while (temp != nullptr) {
      TMonom *monom = temp->GetData();
      this->PushEnd(monom); // Добавляем скопированный моном в конец списка текущего объекта
      temp = temp->GetNext();
    }
  }
  return *this;
}

TPolinom& TPolinom::operator+=(TMonom& m)
{
  TNode<TMonom>* temp = new TNode<TMonom>(&m);
  if (IsEmpty()) {
    begin = end = temp;
  }
  else {
    end->SetNext(temp);
    temp->SetPrev(end);
    end = temp;
  }
  count++;
  return *this;
}

TPolinom& TPolinom::operator-=(TMonom m)
{
  TNode<TMonom>* temp = new TNode<TMonom>(&m);
  if (IsEmpty()) {
    begin = end = temp;
  }
  else {
    end->SetNext(temp);
    temp->SetPrev(end);
    end = temp;
  }
  count++;
  return *this;
}

TPolinom& TPolinom::operator*=(TMonom m)
{
  TNode<TMonom>* current = begin;
  double k = m.GetC();
  TVector<double> d = m.GetDegrees();
  while (current != nullptr) {
    current->GetData()->SetC(current->GetData()->GetC() * k);
    current->GetData()->SetDegrees(current->GetData()->GetDegrees()*d);
    current = current->GetNext();
  }
  return *this;
}

bool TPolinom::operator==(const TPolinom& p)
{
  if (count != p.count) 
  {
    return false;
  }
  TNode<TMonom>* i = begin;
  TNode<TMonom>* j = p.begin;
  while (i != nullptr && j != nullptr) 
  {
    if (i->GetData()->GetC()!=j->GetData()->GetC() ||
      i->GetData()->GetDegrees() != j->GetData()->GetDegrees()) 
    {
      return false;
    }
    i = i->GetNext();
    j = j->GetNext();
  }
  return true;
}

bool TPolinom::operator!=(const TPolinom& p)
{
  if (count != p.count)
  {
    return true;
  }
  TNode<TMonom>* i = begin;
  TNode<TMonom>* j = p.begin;
  while (i != nullptr && j != nullptr)
  {
    if (i->GetData()->GetC() != j->GetData()->GetC() ||
      i->GetData()->GetDegrees() != j->GetData()->GetDegrees())
    {
      return true;
    }
    i = i->GetNext();
    j = j->GetNext();
  }
  return false;
}

int TPolinom::GetCount()
{
  return this->count;
}

ostream& operator<<(ostream& out, const TPolinom& polinom)
{
  TNode<TMonom>* temp = polinom.GetBegin();
  while (temp != nullptr) {
    out << "C: " << temp->GetData()->GetC() << "\n";
    out << "Degrees: " << temp->GetData()->GetDegrees() << "\n";
    temp = temp->GetNext();
  }
  return out;
}

istream& operator>>(istream& in, TPolinom& polinom)
{
  return in;
}
