#include "element.h"



//element::element()
//{
//}

int aaoi(char c) {
	switch (c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	}
}

element::~element()
{
}

e_type symbol::a(void) { return _symbol; }
e_type number::a(void) { return _number; }
e_type element::a(void) { return _element; }

number::number(long double d) {
	value = d;
}

void number::find_num(std::string& s, int& i) {
	bool dot = false;
	int p = 1;
	long double v = 0;

	for (;(i!=s.size()); i++) {
		if (isdigit(s[i])) {
			if (!dot) {
				v *= 10;
				v += aaoi(s[i]);
			}
			else {
				v+=pow(0.1,p++)*aaoi(s[i]);
			}
			continue;
		}

		if (s[i] == '.') {
			if (!dot) dot = true;
			else throw 7;
			continue;
		}
		i--;
		this->value = v;
		return;
	}
	i--;
	this->value = v;
	return;
}
