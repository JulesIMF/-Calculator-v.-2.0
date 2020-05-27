#pragma once
#include "includes.h"
enum e_type {_symbol, _number, _element};
enum optype {_add, _sub, _mlp, _div, _pow, _root};


class element
{
public:
	 
	virtual ~element();
	virtual e_type a(void);
protected:


};

class symbol : virtual public element {
public:

	float priority;
	symbol(optype o, int p) {
		priority = 0;
		otype = o;
		switch (o) {
		case _pow:
		case _root:
			priority += 0.25;
		case _mlp:
		case _div:
			priority += 0.25;
		case _add:
		case _sub:
			priority += (float)p;
		}

	}
	optype otype;
	e_type a(void);
	
};

class number : public element {
public:
	number() = default;
	number(long double d);
	long double value = 0;
	e_type a(void);
	void find_num(string& s, int& i);

};

