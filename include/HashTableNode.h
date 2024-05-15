#ifndef _HASHNODE_
#define _HASHNODE_
#include <algorithm>
#include <iostream>
using namespace std;

template <class TKEY, class TVAL>
class THashNode 
{
protected:
	TKEY* key;
	TVAL* val;
	THashNode<TKEY, TVAL>* next;
	THashNode<TKEY, TVAL>* prev;
public:
	THashNode();
	THashNode(TKEY* _key, TVAL* _val, THashNode<TKEY, TVAL>* _next, THashNode<TKEY, TVAL>* _prev);
	THashNode(TKEY* _key, TVAL* _val);
	THashNode(const THashNode<TKEY, TVAL>& p);

	TKEY* GetKey();
	TVAL* GetValue();
	void SetKey(TKEY _key);
	void SetValue(TVAL _val);
	THashNode<TKEY, TVAL>* GetNext();
	THashNode<TKEY, TVAL>* GetPrev();
	void  SetNext(THashNode<TKEY, TVAL>* n);
	void  SetPrev(THashNode<TKEY, TVAL>* p);

	bool operator == (THashNode<TKEY, TVAL>& p);
	bool operator == (TKEY& p);
};

template<class TKEY, class TVAL>
inline THashNode<TKEY, TVAL>::THashNode()
{
	key = nullptr;
	val = nullptr;
	next = nullptr;
	prev = nullptr;
}

template<class TKEY, class TVAL>
inline THashNode<TKEY, TVAL>::THashNode(TKEY* _key, TVAL* _val, THashNode<TKEY, TVAL>* _next, THashNode<TKEY, TVAL>* _prev)
{
	key = _key;
	val = _val;
	next = _next;
	prev = _prev;
}

template<class TKEY, class TVAL>
inline THashNode<TKEY, TVAL>::THashNode(TKEY* _key, TVAL* _val)
{
	key = _key;
	val = _val;
	next = nullptr;
	prev = nullptr;
}

template<class TKEY, class TVAL>
inline THashNode<TKEY, TVAL>::THashNode(const THashNode<TKEY, TVAL>& p)
{
	key = p.key;
	val = p.val;
	next = p.next;
	prev = p.prev;
}

template<class TKEY, class TVAL>
inline TKEY* THashNode<TKEY, TVAL>::GetKey()
{
	return key;
}

template<class TKEY, class TVAL>
inline TVAL* THashNode<TKEY, TVAL>::GetValue()
{
	return val;
}

template<class TKEY, class TVAL>
inline void THashNode<TKEY, TVAL>::SetKey(TKEY _key)
{
	key = _key;
}

template<class TKEY, class TVAL>
inline void THashNode<TKEY, TVAL>::SetValue(TVAL _val)
{
	val = _val;
}

template<class TKEY, class TVAL>
inline THashNode<TKEY, TVAL>* THashNode<TKEY, TVAL>::GetNext()
{
	return next;
}

template<class TKEY, class TVAL>
inline THashNode<TKEY, TVAL>* THashNode<TKEY, TVAL>::GetPrev()
{
	return prev;
}

template<class TKEY, class TVAL>
inline void THashNode<TKEY, TVAL>::SetNext(THashNode<TKEY, TVAL>* n)
{
	next = n;
}

template<class TKEY, class TVAL>
inline void THashNode<TKEY, TVAL>::SetPrev(THashNode<TKEY, TVAL>* p)
{
	prev = p;
}

template<class TKEY, class TVAL>
inline bool THashNode<TKEY, TVAL>::operator==(THashNode<TKEY, TVAL>& p)
{
	if (key == p.key) { return true; }
	else { return false; }
}

template<class TKEY, class TVAL>
inline bool THashNode<TKEY, TVAL>::operator==(TKEY& p)
{
	return *key == p;
}
#endif