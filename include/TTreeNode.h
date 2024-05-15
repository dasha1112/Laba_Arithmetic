#ifndef _TREENODE_
#define _TREENODE_
#include <algorithm>
#include <iostream>
using namespace std;

template <class TKEY, class TVAL>
class TTreeNode
{
protected:
	TKEY* key;
	TVAL* value;
	TTreeNode<TKEY, TVAL>* left, * right, * prev;
public:
	TTreeNode();
	TTreeNode(TKEY* _key, TVAL* _val, TTreeNode<TKEY, TVAL>* _left, TTreeNode<TKEY, TVAL>* _right, TTreeNode<TKEY, TVAL>* _prev);
	TTreeNode(const TTreeNode<TKEY, TVAL>& p);
	TKEY* GetKey();
	TVAL* GetVal();
	TTreeNode<TKEY, TVAL>* GetRight();
	TTreeNode<TKEY, TVAL>* GetLeft();
	void SetRight(TTreeNode<TKEY, TVAL>* r);
	void SetLeft(TTreeNode<TKEY, TVAL>* l);
	void SetKey(TKEY* _key);
	void SetValue(TVAL* _val);

	bool operator == (TTreeNode<TKEY, TVAL>& p);
	bool operator == (TKEY& p);
	bool operator > (TKEY& p);
};

template<class TKEY, class TVAL>
inline TTreeNode<TKEY, TVAL>::TTreeNode()
{
	key = nullptr;
	value = nullptr;
	left = nullptr;
	right = nullptr;
	prev = nullptr;
}

template<class TKEY, class TVAL>
inline TTreeNode<TKEY, TVAL>::TTreeNode(TKEY* _key, TVAL* _val, TTreeNode<TKEY, TVAL>* _left, TTreeNode<TKEY, TVAL>* _right, TTreeNode<TKEY, TVAL>* _prev)
{
	key = _key;
	value = _val;
	left = _left;
	right = _right;
	prev = _prev;
}

template<class TKEY, class TVAL>
inline TTreeNode<TKEY, TVAL>::TTreeNode(const TTreeNode<TKEY, TVAL>& p)
{
	key = p.key;
	value = p.value;
	left = p.left;
	right = p.right;
	prev = p.prev;
}
template<class TKEY, class TVAL>
inline TKEY* TTreeNode<TKEY, TVAL>::GetKey()
{
	return key;
}
template<class TKEY, class TVAL>
inline TVAL* TTreeNode<TKEY, TVAL>::GetVal()
{
	return value;
}
template<class TKEY, class TVAL>
inline TTreeNode<TKEY, TVAL>* TTreeNode<TKEY, TVAL>::GetRight()
{
	return right;
}
template<class TKEY, class TVAL>
inline TTreeNode<TKEY, TVAL>* TTreeNode<TKEY, TVAL>::GetLeft()
{
	return left;
}
template<class TKEY, class TVAL>
inline void TTreeNode<TKEY, TVAL>::SetRight(TTreeNode<TKEY, TVAL>* r)
{
	right = r;
}
template<class TKEY, class TVAL>
inline void TTreeNode<TKEY, TVAL>::SetLeft(TTreeNode<TKEY, TVAL>* l)
{
	left = l;
}

template<class TKEY, class TVAL>
inline void TTreeNode<TKEY, TVAL>::SetKey(TKEY* _key)
{
	key = _key;
}

template<class TKEY, class TVAL>
inline void TTreeNode<TKEY, TVAL>::SetValue(TVAL* _val)
{
	value = _val;
}


template<class TKEY, class TVAL>
inline bool TTreeNode<TKEY, TVAL>::operator==(TTreeNode<TKEY, TVAL>& p)
{
	if (key == p.key) { return true; }
	else { return false; }
}
template<class TKEY, class TVAL>
inline bool TTreeNode<TKEY, TVAL>::operator==(TKEY& p)
{
	return *key == p;
}
template<class TKEY, class TVAL>
inline bool TTreeNode<TKEY, TVAL>::operator>(TKEY& p)
{
	return *key > p;
}
#endif