#ifndef _NODE_
#define _NODE_

#include <iostream>
using namespace std;

template <class T>
class TNode 
{
	template <class T>
	friend class TListIterator;
protected:
	TNode<T>* prev; //указатель на предыдущий узел
	TNode<T>* next; //указатель на следующий узел
	T* data;

public:
	TNode();
	TNode(T* data_);
	~TNode();
	TNode(TNode<T>* n, TNode<T>* p, T* d);
	TNode(const TNode<T>& p);
	TNode(TNode<T>&& p);
	TNode<T>& operator = (const TNode<T>& p);
	TNode<T>& operator = (TNode<T>&& p);
	TNode<T>* GetNext();
	TNode<T>* GetPrev();
	T* GetData();
	void SetNext(TNode<T>* p);
	void SetPrev(TNode<T>* p);
	void SetData(T* p);
	TNode<T> operator + (TNode<T> t);
	//TNode<T>& operator ++();
};


template<class T>
inline TNode<T>::TNode()
{
	next = nullptr;
	prev = nullptr;
	data = nullptr;
}

template<class T>
inline TNode<T>::TNode(T* data_)
{
	next = nullptr;
	prev = nullptr;
	data = data_;
}

template<class T>
inline TNode<T>::~TNode()
{
	next = nullptr;
	prev = nullptr;
	data = nullptr;
}

template<class T>
inline TNode<T>::TNode(TNode<T>* n, TNode<T>* p, T* d)
{
	next = n;
	prev = p;
	data = d;
}

template<class T>
inline TNode<T>::TNode(const TNode<T>& p)
{
	next = p.next;
	prev = p.prev;
	data = p.data;
}

template<class T>
inline TNode<T>::TNode(TNode<T>&& p)
{
	next = p.next;
	prev = p.prev;
	data = p.data;
	p.next = nullptr;
	p.prev = nullptr;
	p.data = nullptr;
}

template<class T>
inline TNode<T>& TNode<T>::operator=(const TNode<T>& p)
{
	next = p.next;
	prev = p.prev;
	data = p.data;
  return *this;
}

template<class T>
inline TNode<T>& TNode<T>::operator=(TNode<T>&& p)
{
	next = p.next;
	prev = p.prev;
	data = p.data;
	p.next = nullptr;
	p.prev = nullptr;
	p.data = nullptr;
	return *this;
}

template<class T>
inline TNode<T>* TNode<T>::GetNext()
{
	return next;
}

template<class T>
inline TNode<T>* TNode<T>::GetPrev()
{
	return prev;
}

template<class T>
inline T* TNode<T>::GetData()
{
	return data;
}

template<class T>
inline void TNode<T>::SetNext(TNode<T>* p)
{
	next = p;
}

template<class T>
inline void TNode<T>::SetPrev(TNode<T>* p)
{
	prev = p;
}

template<class T>
inline void TNode<T>::SetData(T* p)
{
	data = p;
}
template<class T>
inline TNode<T> TNode<T>::operator+(TNode<T> t)
{
	TNode<T> m;
	m.data = data + t.data;
}
/*template<class T>
inline TNode<T>& TNode<T>::operator++()
{
	if (data != nullptr) {
		*data = *data + 1;
	}
	return *this;
}*/
#endif