#ifndef _TREETABLE_
#define _TREETABLE_
#include <algorithm>
#include <iostream>
#include "TTreeNode.h"
#include "TQueue.h"
#include "ITable.h"
using namespace std;

template <class TKEY, class TVAL>
class TTreeTable
{
protected:
	TTreeNode<TKEY, TVAL>* root;
	int count;
public:
	TTreeTable();
	TTreeTable(const TTreeTable<TKEY, TVAL>& p);
	~TTreeTable();

	void Clear();
	TVAL& operator [](TKEY* k);
	TVAL Find(TKEY k);
	void Add(TKEY* k, TVAL* v);
	void Delete(TKEY k);
	
	int GetCount();
	TTreeNode<TKEY, TVAL>* GetRoot();
};

template<class TKEY, class TVAL>
inline TTreeTable<TKEY, TVAL>::TTreeTable()
{
	count = 0;
	root = nullptr;
}

template<class TKEY, class TVAL>
inline TTreeTable<TKEY, TVAL>::TTreeTable(const TTreeTable<TKEY, TVAL>& p)
{
	count = p.count;
	// Создаем 2 очереди 
	TQueue <TTreeNode<TKEY, TVAL>*> tmp1; // очередь элементов, через которые еще не прошли
	TQueue <TTreeNode<TKEY, TVAL>*> tmp2; // очередь элементов, через которые уже прошли
	root = new TTreeNode<TKEY, TVAL>(p.root->GetKey(), p.root->GetVal(), nullptr, nullptr, nullptr);
	tmp1.Push(root);
	tmp2.Push(p.root);

	while (!tmp1.IsEmpty())
	{
		TTreeNode<TKEY, TVAL>* curr1 = tmp1.Front();
		TTreeNode<TKEY, TVAL>* curr2 = tmp2.Front();
		tmp1.Pop();
		tmp2.Pop();
		if (curr2->GetLeft() != nullptr)
		{
			TTreeNode<TKEY, TVAL>* newLeft = new TTreeNode<TKEY, TVAL>(curr2->GetLeft()->GetKey(), curr2->GetLeft()->GetVal(), nullptr, nullptr, curr1);
			curr1->SetLeft(newLeft);
			tmp1.Push(newLeft);
			tmp2.Push(curr2->GetLeft());
		}
		if (curr2->GetRight() != nullptr)
		{
			TTreeNode<TKEY, TVAL>* newRight = new TTreeNode<TKEY, TVAL>(curr2->GetRight()->GetKey(), curr2->GetRight()->GetVal(), nullptr, nullptr, curr1);
			curr1->SetRight(newRight);
			tmp1.Push(newRight);
			tmp2.Push(curr2->GetRight());
		}
	}
}

template<class TKEY, class TVAL>
inline TTreeTable<TKEY, TVAL>::~TTreeTable()
{
	Clear();
}

template<class TKEY, class TVAL>
inline void TTreeTable<TKEY, TVAL>::Clear()
{
	if (root == nullptr) 
	{
		return;
	}

	TQueue<TTreeNode<TKEY, TVAL>*> tmp1;
	tmp1.Push(root);

	while (!tmp1.IsEmpty())
	{
		TTreeNode<TKEY, TVAL>* curr1 = tmp1.Front();
		if (curr1->GetLeft() != nullptr) {
			tmp1.Push(curr1->GetLeft());
		}
		if (curr1->GetRight()) {
			tmp1.Push(curr1->GetRight());
		}
		delete curr1; // Удаление узла
		tmp1.Pop(); // Удаление узла из очереди
	}
	root = nullptr; // Устанавливаем корень в nullptr после удаления всех узлов
	count = 0;
}

template<class TKEY, class TVAL>
inline TVAL& TTreeTable<TKEY, TVAL>::operator[](TKEY* k)
{
	TTreeNode<TKEY, TVAL>* curr = root;
	TTreeNode<TKEY, TVAL>* prev = root;
	TVAL* v = new TVAL();

	TTreeNode<TKEY, TVAL>* next = nullptr;
	while (curr != nullptr)
	{
		prev = curr;
		if (*curr == *k)
		{
			return *curr->GetVal();
		}
		else if (*curr > *k)
		{
			next = (curr->GetLeft());
			curr = curr->GetLeft();
		}
		else
		{
			next = (curr->GetRight());
			curr = curr->GetRight();
		}
	}
	if (prev != nullptr)
	{
		if (*prev > *k)
		{
			prev->SetLeft(new TTreeNode<TKEY, TVAL>(k, v, nullptr, nullptr, nullptr));
		}
		else
		{
			prev->SetRight(new TTreeNode<TKEY, TVAL>(k, v, nullptr, nullptr, nullptr));
		}
	}
	count++;
	return *next->GetVal();
}

template<class TKEY, class TVAL>
inline TVAL TTreeTable<TKEY, TVAL>::Find(TKEY k)
{
	TTreeNode<TKEY, TVAL>* curr = root;
	bool flag = false;
	while (curr!=nullptr)
	{
		if (*curr == k) 
		{
			return *curr->GetVal();
			flag = true;
		}
		else if (*curr > k) 
		{
			curr = curr->GetLeft();
		}
		else 
		{
			curr = curr->GetRight();
		}
	}
	if (flag == false)
		throw "Error";
}

template<class TKEY, class TVAL>
inline void TTreeTable<TKEY, TVAL>::Add(TKEY* k, TVAL* v)
{
	if (root == nullptr) 
	{
		root = new TTreeNode<TKEY, TVAL>(k, v, nullptr, nullptr, nullptr);
		count++;
		return;
	}

	TTreeNode<TKEY, TVAL>* curr = root;
	TTreeNode<TKEY, TVAL>* prev = root;

	TTreeNode<TKEY, TVAL>* next = nullptr;
	while (curr != nullptr)
	{
		prev = curr;
		if (*curr == *k) 
		{
			throw "Error";
		}
		else if (*curr > *k) 
		{
			next = (curr->GetLeft());
			curr = curr->GetLeft();
		}
		else 
		{
			next = (curr->GetRight());
			curr = curr->GetRight();
		}
	}
	 if (prev != nullptr)
    {
        if (*prev > *k)
        {
            prev->SetLeft(new TTreeNode<TKEY, TVAL>(k, v, nullptr, nullptr, nullptr));
        }
        else
        {
            prev->SetRight(new TTreeNode<TKEY, TVAL>(k, v, nullptr, nullptr, nullptr));
        }
    }
	count++;
}
template<class TKEY, class TVAL>
void TTreeTable<TKEY, TVAL>::Delete(TKEY k)
{
	TQueue<TTreeNode<TKEY, TVAL>*> nodesQueue;
	nodesQueue.Push(root);
	TTreeNode<TKEY, TVAL>* keyNode = nullptr;
	TTreeNode<TKEY, TVAL>* parentNode = nullptr;

	while (!nodesQueue.IsEmpty())
	{
		TTreeNode<TKEY, TVAL>* currentNode = nodesQueue.Front();
		nodesQueue.Pop();

		if (*currentNode == k)
		{
			keyNode = currentNode;
			break;
		}
		else if (*currentNode > k)
		{
			parentNode = currentNode;
			nodesQueue.Push(currentNode->GetLeft());
		}
		else
		{
			parentNode = currentNode;
			nodesQueue.Push(currentNode->GetRight());
		}
	}

	if (keyNode == nullptr)
	{
		// Узел с ключом k не найден в дереве
		return;
	}

	if (keyNode->GetLeft() == nullptr && keyNode->GetRight() == nullptr)
	{
		// Узел не имеет потомков, его можно просто удалить
		if (parentNode == nullptr)
		{
			root = nullptr;
		}
		else if (parentNode->GetLeft() == keyNode)
		{
			parentNode->SetLeft(nullptr);
		}
		else
		{
			parentNode->SetRight(nullptr);
		}
		delete keyNode;
	}
	else if (keyNode->GetLeft() == nullptr)
	{
		// Узел имеет только правого потомка
		if (parentNode == nullptr)
		{
			root = keyNode->GetRight();
		}
		else if (parentNode->GetLeft() == keyNode)
		{
			parentNode->SetLeft(keyNode->GetRight());
		}
		else
		{
			parentNode->SetRight(keyNode->GetRight());
		}
		delete keyNode;
	}
	else if (keyNode->GetRight() == nullptr)
	{
		// Узел имеет только левого потомка
		if (parentNode == nullptr)
		{
			root = keyNode->GetLeft();
		}
		else if (parentNode->GetLeft() == keyNode)
		{
			parentNode->SetLeft(keyNode->GetLeft());
		}
		else
		{
			parentNode->SetRight(keyNode->GetLeft());
		}
		delete keyNode;
	}
	else
	{
		// Узел имеет обоих потомков, нужно найти наименьший узел в правом поддереве
		TTreeNode<TKEY, TVAL>* minRight = keyNode->GetRight();
		TTreeNode<TKEY, TVAL>* minRightParent = keyNode;

		while (minRight->GetLeft() != nullptr)
		{
			minRightParent = minRight;
			minRight = minRight->GetLeft();
		}

		// Замена ключа и значения удаляемого узла узлом с минимальным ключом в правом поддереве
		keyNode->SetKey(*(minRight->GetKey()));
		keyNode->SetValue(*(minRight->GetVal()));

		// Удаление узла с минимальным ключом в правом поддереве
		if (minRightParent == keyNode)
		{
			keyNode->SetRight(minRight->GetRight());
		}
		else
		{
			minRightParent->SetLeft(minRight->GetRight());
		}
		delete minRight;
	}
}
template<class TKEY, class TVAL>
inline int TTreeTable<TKEY, TVAL>::GetCount()
{
	return count;
}

template<class TKEY, class TVAL>
inline TTreeNode<TKEY, TVAL>* TTreeTable<TKEY, TVAL>::GetRoot()
{
	return root;
}
#endif