#ifndef _LISTITER_
#define _LISTITER_

#include <iostream>
#include "MyNode.h"
#include "MyList.h"

using namespace std;

template <class T>
class TListIterator
{
protected:
  TNode<T>* curr; // ��������� �� ����
  TList<T>* list; // ��������� �� ������
public:
  TListIterator(TList<T>* d, TNode<T>* p) : list(d), curr(p) {}
  TListIterator(const TListIterator<T>& p) : list(p.list), curr(p.curr) {}
  TListIterator(TListIterator<T>&& p) : list(p.list), curr(p.curr) { p.curr = nullptr; }
  ~TListIterator() {}

  void PushAfter(T* a)
  {
    if (curr != nullptr) {
      TNode<T>* t = new TNode<T>(curr->Next(), curr, a);
      curr->GetNext()->SetPrev(t);
      curr->Set(t);
      list->count++;
    }
    else {
      throw "������";
    }
  }

  void PushBefore(T* a)
  {
    if (curr != nullptr && curr->GetPrev() != nullptr) {
      TNode<T>* t = new TNode<T>(curr, curr->GetPrev(), a);
      curr->GetPrev()->SetNext(t);
      curr->SetPrev(t);
      list->count++;
    }
    else {
      throw "������";
    }
  }

  T* operator*()
  {
    if (curr != nullptr) {
      return &(*curr).GetData();
    }
    else {
      throw "������";
    }
  }

  TListIterator<T>& operator=(const TListIterator<T>& p)
  {
    curr = p.curr;
    list = p.list;
    return *this;
  }

  TListIterator<T>& operator=(const TListIterator<T>&& p)
  {
    curr = p.curr;
    list = p.list;
    p.curr = nullptr;
    return *this;
  }

  TListIterator<T>& operator++()
  {
    if (curr != nullptr && curr->GetNext() != nullptr) {
      curr = curr->GetNext();
    }
    else {
      throw "������";
    }
    return *this;
  }

  TListIterator<T>& operator--()
  {
    if (curr != nullptr && curr->GetPrev() != nullptr) {
      curr = curr->GetPrev();
    }
    else {
      throw "������";
    }
    return *this;
  }

  bool operator==(const TListIterator<T>& p)
  {
    return (curr == p.curr);
  }

  bool operator!=(const TListIterator<T>& p)
  {
    return (curr != p.curr);
  }
};
#endif