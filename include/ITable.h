#ifndef _ITABLE_
#define _ITABLE_

template <class TKEY, class TVAL>
class ITable 
{
public:
	virtual TVAL Find(TKEY k) = 0;
	virtual void Add(TKEY* k, TVAL* v) = 0;
	virtual void Push(TKEY k, TVAL v) = 0;
	virtual void Delete(TKEY k) = 0;
};
#endif