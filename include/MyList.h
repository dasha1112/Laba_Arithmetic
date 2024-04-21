#ifndef _LIST_
#define _LIST_

#include <iostream>
#include <MyNode.h>
using namespace std;

template <class T>
class TList 
{
	template <class T>
	friend class TListIterator;
protected:
	TNode<T>* begin; //указатель на начало списка
	TNode<T>* end; //указатель на конец списка
	int count; //длина списка
	
public:
	TList();
	~TList();
	TList(const TList<T>& p);
	TList(TList<T>&& p);
	TList<T>& operator = (const TList<T>& p);
	TList<T>& operator = (TList<T>&& p);
	void PushBegin(T* a);
	void Push_Begin(T data);
	void PushEnd(T* a);
	void DelBegin();
	void DelEnd();
	void Clear();
	bool IsEmpty();
	bool IsFull();
	TNode<T>* GetBegin();
	TNode<T>* GetBegin() const;
	TNode<T>* GetEnd();
	int GetCount();
	void operator ++();
};

template<class T>
inline TList<T>::TList()
{
	begin = nullptr;
	end = nullptr;
	count = 0;
}

template<class T>
inline TList<T>::~TList()
{
	TNode<T>* temp = begin;
	TNode<T>* next = nullptr;
	while (temp != nullptr) 
	{
		next = temp->GetNext();
		delete temp;
		temp = next;
	}
	begin = nullptr;
	end = nullptr;
	count = 0;
}

template<class T>
inline TList<T>::TList(const TList<T>& p)
{
	if (p.begin == nullptr)
	{
		begin = nullptr;
		end = nullptr;
		count = 0;
	}
	else 
	{
		count = p.count;
		begin = new TNode<T>(nullptr, nullptr, p.begin->GetData());
		TNode<T>* temp = begin;
		TNode<T>* temp2 = p.begin->GetNext();
		while (temp2 != nullptr)
		{
			TNode<T>* a = new TNode<T>();
			a->SetPrev(temp);
			a->SetData(temp2 -> GetData());
			temp->SetNext(a);
			temp = temp->GetNext();
			temp2 = temp2->GetNext();
		}
		end = temp;
		end->SetNext(nullptr);
	}
}

template<class T>
inline TList<T>::TList(TList<T>&& p)
{
	begin = p.begin;
	p.begin = nullptr;
	end = p.end;
	p.end = nullptr;
	count = p.count;
	p.count = 0;
}

template<class T>
inline TList<T>& TList<T>::operator=(const TList<T>& p)
{
	if (this == &p) 
	{
		return *this;
	}
	else 
	{
		Clear();
		begin = new TNode<T>(nullptr, nullptr, p.begin->GetData());
		TNode<T>* temp = begin;
		TNode<T>* temp2 = p.begin->GetNext();
		while (temp2 != nullptr)
		{
			TNode<T>* a = new TNode<T>();
			a->SetPrev(temp);
			a->SetData(temp2->GetData());
			temp->SetNext(a);
			temp = temp->GetNext();
			temp2 = temp2->GetNext();
		}
		end = temp;
		end->SetNext(nullptr);
	}
	return *this;
}

template<class T>
inline TList<T>& TList<T>::operator=(TList<T>&& p)
{
	begin = p.begin;
	p.begin = nullptr;
	end = p.end;
	p.end = nullptr;
	count = p.count;
	p.count = 0;
	return *this;
}


template<class T>
inline void TList<T>::PushBegin(T* a)
{
	TNode<T>* temp = new TNode<T>(begin, nullptr, a);
	if (begin == nullptr) 
	{
		begin = temp;
		end = temp;
	}
	else 
	{
		begin->SetPrev(temp);
		begin = temp;
	}
	count++;
}

template<class T>
inline void TList<T>::Push_Begin(T data)
{
	TNode<T>* tmp = new TNode<T>(data);
	tmp->SetNext(begin);
	begin->SetPrev(tmp);
	begin = tmp;
	count++;
}

template<class T>
inline void TList<T>::PushEnd(T* a)
{
	TNode<T>* temp = new TNode<T>(nullptr, end, a);
	if (begin == nullptr) 
	{
		end = temp;
		begin = temp;
	}
	else 
	{
		end->SetNext(temp);
		end = temp;
	}
	count++;
}

template<class T>
inline void TList<T>::DelBegin() //удаление первого узла из списка
{
	if (begin == nullptr) 
	{
		throw "Ошибка";
	}
	else 
	{
		TNode<T>* temp = begin;
		begin = begin->GetNext();
		if (begin != nullptr) 
		{
			begin->SetPrev(nullptr);
		}
		else 
		{
			end = nullptr;
		}
		delete temp;
		count--;
	}
}

template<class T>
inline void TList<T>::DelEnd() //удаление последнего узла из списка
{
	if (begin == nullptr)
	{
		throw "Ошибка";
	}
	else
	{
		TNode<T>* temp = end;
		end = end->GetPrev();
		if (end != nullptr)
		{
			end->SetNext(nullptr);
		}
		else 
		{
			begin = nullptr;
		}
		delete temp;
		count--;
	}
}
template<class T>
inline void TList<T>::Clear()
{
	TNode<T>* temp = begin;
	while (temp != nullptr) 
	{
		TNode<T>* temp2 = temp;
		temp = temp->GetNext();
		delete temp2;
		begin = nullptr;
		end = nullptr;
		count = 0;
	}
}
template<class T>
inline bool TList<T>::IsEmpty()
{
	if (count == 0) { return true; }
	return false;
}
template<class T>
inline bool TList<T>::IsFull()
{
	return false;
}
template<class T>
TNode<T>* TList<T>::GetBegin()
{
	return begin;
}

template<class T>
inline TNode<T>* TList<T>::GetBegin() const
{
	return begin;
}

template<class T>
TNode<T>* TList<T>::GetEnd()
{
	return end;
}

template<class T>
int TList<T>::GetCount()
{
	return count;
}

template<class T>
inline void TList<T>::operator++()
{
	if (begin != nullptr) {
		begin = begin->next;
	}
}

#endif