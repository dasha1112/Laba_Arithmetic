#ifndef _QUEUE_
#define _QUEUE_

#include <iostream>
using namespace std;

template <class T>
class TQueue
{
protected:
	int size;
	int start, end;
	T* data;

public:
	TQueue(int _size = 100);
	TQueue(const TQueue<T>& q);
	TQueue(TQueue<T>&& q);
	~TQueue();
	void Push(T a);
	T GetElem();
	int GetCount();
	bool IsFull();
	bool IsEmpty();
	T Front();
	void Pop();
};

template <class T>
TQueue <T> ::TQueue(int _size)
{
	if (_size < 0)
	{
		throw "Error";
	}
	else if (_size == 0)
	{
		data = nullptr;
		size = 0;
	}
	else
	{
		size = _size;
		data = new T[size];
	}
	start = 0;
	end = 0;
}

template <class T>
TQueue<T> ::TQueue(const TQueue<T>& q)
{
	if (q.data == nullptr)
	{
		data = nullptr;
		size = 0;
	}
	else
	{
		size = q.size;
		data = new T[size];
		for (int i = 0; i < size; i++)
		{
			data[i] = q.data[i];
		}
	}
	start = q.start;
	end = q.end;
}

template <class T>
TQueue<T> :: ~TQueue() 
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
}

template <class T>
TQueue<T> ::TQueue(TQueue<T>&& q)
{
	data = q.data;
	size = q.size;
	start = q.start;
	end = q.end;
	q.data = nullptr;
	q.size = 0;
	q.start = 0;
	q.end = 0;
}

template <class T>
bool TQueue<T> ::IsEmpty()
{
	if (start == end) return true;
	else return false;
}

template <class T>
bool TQueue<T> ::IsFull()
{
	if ((end + 1) % size == start) return true;
	else return false;
}

template <class T>
T TQueue <T> ::GetElem()
{
	if (IsEmpty())
	{
		throw "Error";
	}
	int st = start;
	start = (start + 1) % size;
	return data[st];
}

template <class T>
void TQueue<T> ::Push(T a)
{
	if (IsFull())
	{
		throw "Error";
	}
	else
	{
		data[end] = a;
		end++;
		if (end == size)
		{
			end = 0;
		}
	}
}

template <class T>
int TQueue <T> ::GetCount()
{
	return (end - start + size) % size;
}

template <class T>
T TQueue<T>::Front() {
	if (IsEmpty()) {
		throw "Error";
	}
	return data[start];
}

template<class T>
inline void TQueue<T>::Pop()
{
	if (IsEmpty()) 
	{
		throw "Error";
	}
	else 
	{
		start = (start + 1) % size;
	}
}

#endif