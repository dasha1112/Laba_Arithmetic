#ifndef _TABLE_
#define _TABLE_
#include <algorithm>
#include <iostream>
#include "HashTableNode.h"
#include "ITable.h"
using namespace std;

template <class TKEY, class TVAL>
class THashTable
{
protected:
	THashNode<TKEY, TVAL>** data;
	int count;
	int size;
public:
	int Hash(TKEY& k);
	THashTable(int _size = 300);
	THashTable(const THashTable<TKEY, TVAL>& p);
	~THashTable();

	TVAL& operator [](TKEY* k);
	TVAL Find(TKEY k);
	void Add(TKEY* k, TVAL* v);
	void Delete(TKEY k);
	int GetCount();
	int GetSize();
};

template<class TKEY, class TVAL>
inline int THashTable<TKEY, TVAL>::Hash(TKEY& k)
{
	std::string keyStr = k;

	// Вычисляем сумму символов в строке
	int sum = 0;
	for (char c : keyStr)
	{
		sum += static_cast<int>(c);
	}

	return sum % size;
}

template<class TKEY, class TVAL>
inline THashTable<TKEY, TVAL>::THashTable(int _size)
{
	count = 0;
	if (_size <= 0)
		throw "Error";
	size = _size;

	data = new THashNode<TKEY, TVAL>*[_size];
	for (int i = 0; i < size; i++)
		data[i] = nullptr;
}

template<class TKEY, class TVAL>
inline THashTable<TKEY, TVAL>::THashTable(const THashTable<TKEY, TVAL>& p)
{
	size = p.size;
	count = p.count;

	data = new THashNode<TKEY, TVAL>*[size]; // Выделяем новую память

	for (int i = 0; i < size; i++)
	{
		if (p.data[i] != nullptr) 
		{
			THashNode<TKEY, TVAL>* curr = p.data[i];
			THashNode<TKEY, TVAL>* prev = nullptr; // Указатель на предыдущий узел
			while (curr != nullptr) 
			{
				THashNode<TKEY, TVAL>* newNode = new THashNode<TKEY, TVAL>(curr->GetKey(), curr->GetValue()); // Создаем новый узел и копируем туда ключ и значение
				if (prev) 
				{
					prev->SetNext(newNode);
					newNode->SetPrev(prev);
				}
				else 
				{
					data[i] = newNode;
				}
				prev = newNode;
				curr = curr->GetNext();
			}
		}
		else 
		{
			data[i] = nullptr;
		}
	}
}

template<class TKEY, class TVAL>
inline THashTable<TKEY, TVAL>::~THashTable()
{
	if (data != nullptr) 
	{
		for (int i = 0; i < size; i++) 
		{
			if (data[i] != nullptr)
				delete data[i];
		}
		size = 0;
		count = 0;
	}
}

template<class TKEY, class TVAL>
inline TVAL& THashTable<TKEY, TVAL>::operator[](TKEY* k)
{
	int index = Hash(*k);
	THashNode<TKEY, TVAL>* curr_item = data[index];

	while (curr_item != nullptr)
	{
		if (*(curr_item->GetKey()) == *k) // Нашли узел с заданным ключом
		{
			return *curr_item->GetValue();
		}
		curr_item = curr_item->GetNext();
	}

	// Если узел с указанным ключом не найден, создаем новый узел и возвращаем его ссылку
	TVAL* v = new TVAL();
	THashNode<TKEY, TVAL>* newNode = new THashNode<TKEY, TVAL>(k, v); // Создаем новый узел
	if (data[index] != nullptr) 
	{
		newNode->SetNext(data[index]);
		data[index]->SetPrev(newNode);
	}
	data[index] = newNode; // Обновляем указатель на начало цепочки
	count++;

	return *newNode->GetValue();
}

template<class TKEY, class TVAL>
inline TVAL THashTable<TKEY, TVAL>::Find(TKEY k)
{
	int index = Hash(k);
	THashNode<TKEY, TVAL>* curr_item = data[index];

	while (curr_item != nullptr)
	{
		if (*(curr_item->GetKey()) == k) // Сравниваем ключи
		{
			return *curr_item->GetValue(); // Возвращаем узел, если ключи совпадают
		}
		curr_item = curr_item->GetNext();
	}

	return TVAL(); // Узел не найден
}

template<class TKEY, class TVAL>
inline void THashTable<TKEY, TVAL>::Add(TKEY* k, TVAL* v)
{
	int index = Hash(*k);
	THashNode<TKEY, TVAL>*& curr_item = data[index]; // Ссылка на указатель

	if (curr_item == nullptr)
	{
		curr_item = new THashNode<TKEY, TVAL>(k, v);
		count++;
	}
	else
	{
		// Обработка коллизии - добавление в конец связанного списка
		while (curr_item->GetNext() != nullptr)
		{
			curr_item = curr_item->GetNext();
		}

		THashNode<TKEY, TVAL>* newNode = new THashNode<TKEY, TVAL>(k, v);
		curr_item->SetNext(newNode);
		newNode->SetPrev(curr_item);
		count++;
	}
}

template<class TKEY, class TVAL>
inline void THashTable<TKEY, TVAL>::Delete(TKEY k)
{
	int index = Hash(k);
	THashNode<TKEY, TVAL>* curr_item = data[index];

	THashNode<TKEY, TVAL>* prev_item = nullptr; // Указатель на предыдущий узел

	while (curr_item != nullptr)
	{
		if (*(curr_item->GetKey()) == k) // Нашли нужный узел
		{
			if (prev_item != nullptr) 
			{
				prev_item->SetNext(curr_item->GetNext()); // Обновляем указатель на следующий узел у предыдущего узла
				if (curr_item->GetNext() != nullptr) 
				{
					curr_item->GetNext()->SetPrev(prev_item); // Обновляем указатель на предыдущий узел у следующего узла
				}
				delete curr_item;
				return;
			}
			else 
			{
				data[index] = curr_item->GetNext(); // Если удаляемый узел - первый в списке
				if (curr_item->GetNext() != nullptr) 
				{
					curr_item->GetNext()->SetPrev(nullptr); // Обнуляем указатель на предыдущий узел у нового первого узла
				}
				delete curr_item;
				return;
			}
		}
		prev_item = curr_item;
		curr_item = curr_item->GetNext();
	}
}

template<class TKEY, class TVAL>
inline int THashTable<TKEY, TVAL>::GetCount()
{
	return count;
}

template<class TKEY, class TVAL>
inline int THashTable<TKEY, TVAL>::GetSize()
{
	return size;
}

#endif