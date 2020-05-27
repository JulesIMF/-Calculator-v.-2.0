#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
#include "element.h"
#include <Windows.h>
#include <time.h>

#define _ER1 "Не найдена переменная.\n"
#define _ER2 "Скобочная последовательность в запросе не является корректной.\n"
#define _ER3 "Неизвестный символ.\n"
#define _ER4 "Невозможно применить один из операторов.\n"
#define _ER5 "Комплексные числа не поддерживаются в этой версии: извлечение квадратного корня из отрицательного числа невозможно.\n"
#define _ER6 "Математически некорректное действие (результатом является \"NaN\").\n"
#define _ER7 "Невозможно определить принадлежность одной из точек.\n"
#define _ER8 "Неизвестная команда.\n"
#define _ER9 "Переменная \"ans\" ещё не хранит значения.\n"
#define _ER10 "Переменной \"ans\" невозможно менять значение вручную.\n"
#define _ER11 "Содержатся кириллические символы.\n"

int aaoi(char c);

string g_case(int i) {

	if (i % 100 >= 10 && i % 100 <= 20) return "годиков";
	if (i % 10 == 0 || i % 10 >= 5) return "годиков";
	if (i % 10 == 1) return "годик";
	return "годика";
}

int julesAge() {
	time_t t;
	time(&t);
	tm* tk = localtime(&t);
	if (tk->tm_mon < 1) return tk->tm_year - 103;
	if (tk->tm_mon == 1 && tk->tm_mday<22) return tk->tm_year - 103;
	return tk->tm_year - 102;
	
}

enum inputType{quit, req, com};

void infoOut() {
	cout << "Calculator v. 2.0" << endl << "Джулс, " << julesAge() << ((julesAge()!=16)?(" (на момент создания 16)"):(""))<< " "<< g_case(julesAge()) << ", 2018 год." << endl;
	cout << "Учтите, что киррилические символы не поддерживаются." << endl;
	cout << "Для вывода помощи наберите \"#help\"." << endl << endl;
}

//¤†“‹‘
//„¦г«б

class momentChange {
public:
	bool y_changed, m_changed;
	momentChange(bool y, bool m) {
		y_changed = y;
		m_changed = m;
	}
};

class moment {
public:
	int day, month, year;
	moment(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}
	momentChange increment() {
		bool mc = false, yc = false;
		if (day == 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
			day = 1;
			month++;
			mc = true;
		}
		if (day == 30 && (month == 4 || month == 6 || month == 9 || month == 11)) {
			day = 1;
			month++; mc = true;
		}
		if (day == 28 && (month == 2)&&(year%4!=0||(year%400!=0&&year%100==0))) {
			day = 1;
			month++; mc = true;
		}
		if (day == 29 && (month == 2) && ((year % 4 == 0 && year%100!=0) ||year%400==0)) {
			day = 1;
			month++; mc = true;
		}
		if (month == 13) {
			year++;
			month = 1;
			yc = true;
		}
		if(!mc) day++;
		return momentChange(mc, yc);
	}
	void increment_nl() {
		bool mc = false, yc = false;
		if (day == 30 && (month == 0 || month == 2 || month == 4 || month == 6 || month == 7 || month == 9 || month == 11)) {
			day = 0;
			month++;
			mc = true;
		}
		if (day == 29 && (month == 3 || month == 5 || month == 8 || month == 10)) {
			day = 0;
			month++; mc = true;
		}
		if (day == 27 && (month == 1) && ((year+1) % 4 != 0 || ((year + 1) % 400 != 0 && (year + 1) % 100 == 0))) {
			day = 0;
			month++; mc = true;
		}
		if (day == 28 && (month == 1) && (((year + 1) % 4 == 0 && (year + 1) % 100 != 0) || (year + 1) % 400 == 0)) {
			day = 0;
			month++; mc = true;
		}
		if (month == 12) {
			year++;
			month = 0;
			yc = true;
		}
		if (!mc) day++;
		//return momentChange(mc, yc);
	}
	bool operator==(moment&m1) {
		if (year == m1.year && month == m1.month && day == m1.day) return true;
		else return false;
	}
	bool operator!=(moment &m1) {
		if (year == m1.year && month == m1.month && day == m1.day) return false;
		else return true;
	}
};

string y_case(int i) {
	if (i == 0) return "";
	if (i % 100 >= 10 && i % 100 <= 20) return "лет";
	if (i % 10 == 0 || i % 10 >= 5) return "лет";
	if (i % 10 == 1) return "год";
	return "года";
}

string m_case(int i) {
	if (i == 0) return "";
	if (i % 100 >= 10 && i % 100 <= 20) return "месяцев";
	if (i % 10 == 0 || i % 10 >= 5) return "месяцев";
	if (i % 10 == 1) return "месяц";
	return "месяца";
}

string d_case(int i) {
	
	if (i % 100 >= 10 && i % 100 <= 20) return "дней";
	if (i % 10 == 0 || i % 10 >= 5) return "дней";
	if (i % 10 == 1) return "день";
	return "дня";
}

bool parse(moment** mm) {
	string s;
	cin >> s;
	int d, m, y;
	if (s.length() != (2 + 2 + 4 + 2)) {
		cout << "Дата введена неверно" << endl;
		return false;
	}
	if (!isdigit(s[0]) || !isdigit(s[1]) || !isdigit(s[3]) || !isdigit(s[4]) || !isdigit(s[6]) || !isdigit(s[7]) || !isdigit(s[8]) || !isdigit(s[9]) || isdigit(s[2]) || isdigit(s[5])) {
		cout << "Дата введена неверно" << endl;
		return false;
	}
	d = aaoi(s[0]);
	d *= 10;
	d += aaoi(s[1]);
	m = aaoi(s[3]);
	m *= 10;
	m += aaoi(s[4]);
	y = aaoi(s[6]);
	y *= 10;
	y += aaoi(s[7]);
	y *= 10;
	y += aaoi(s[8]);
	y *= 10;
	y += aaoi(s[9]);
	if (d > 28 && m == 2 && (y % 4 != 0 || (y % 100 == 0 && y % 400 != 0))) {
		cout << "Дата не существует" << endl;
		return false;
	}
	if (d > 29 && m == 2) {
		cout << "Дата не существует" << endl;
		return false;
	}
	if (d > 30 && (m == 4 || m == 6 || m == 9 || m == 11)) {
		cout << "Дата не существует" << endl;
		return false;
	}
	if (d > 31 && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)) {
		cout << "Дата не существует" << endl;
		return false;
	}
	if (m > 12) {
		cout << "Дата не существует" << endl;
		return false;
	}
	
	*mm = new moment(d, m, y);
	return true;
}

bool greater(moment m1, moment m2) {
	if (m1.year > m2.year) return true;
	if (m1.year < m2.year) return false;
	if (m1.month > m2.month) return true;
	if (m1.month < m2.month) return false;
	if (m1.day > m2.day) return true;
	return false;
}

void datadiff(moment mm, moment me) {

	moment nl(0, 0, 0);
	int d = 0, m = 0, y = 0;
	momentChange mcc(false,false);
	
	while (mm != me && (greater(me,mm))) {
		mcc = mm.increment();
		d++;
		nl.increment_nl();
		if (d % 30 == 0) m++;
		if (d % 365 == 0) y++;
	}
	if (d == 0) {
		if (mm == me) {
			cout << "Даты равны" << endl;
			return;
		}
		while (mm != me) {
			mcc = me.increment();
			d++;
			nl.increment_nl();
			if (d % 30 == 0) m++;
			if (d % 365 == 0) y++;
		}
	}
	cout << "Между днями разница в ";
	if (nl.year != 0) {
		cout << nl.year << " " << y_case(nl.year);
		if (nl.month != 0 && nl.day != 0) cout << ", ";
		else {
			if (nl.month != 0 || nl.day != 0) cout << " и ";
		}
	}
	if (nl.month != 0) {
		cout << nl.month << " " << m_case(nl.month);
		if (nl.day != 0) cout << " и ";
	}
	if (nl.day != 0) {
		cout << nl.day << " " << d_case(nl.day);
	}
	cout << "."<< endl;
	cout << "Также разница составляет ровно " << d << " " << d_case(d) << "." << endl;
}

bool isJules(string& s){
	if (s.size() < 5) return false;
	if (s[0] != '„'&&s[0] != '¤') return false;
	if (s[1] != '†'&&s[1] != '¦') return false;
	if (s[2] != '“'&&s[2] != 'г') return false;
	if (s[3] != '‹'&&s[3] != '«') return false;
	if (s[4] != '‘'&&s[4] != 'б') return false;
}

void helpOut() {
	cout << "Доступные операции:" << endl;
	cout << "Операция\t\t\t\tПример" << endl << endl;

	cout << "Сложение\t\t\t\t2+2" << endl;
	cout << "Вычитание\t\t\t\t3-8.5" << endl;
	cout << "Умножение\t\t\t\t8*9" << endl;
	cout << "Деление\t\t\t\t\t91/13" << endl;
	cout << "Возведение в степень\t\t\t2^10" << endl;
	cout << "Взятие квадратного корня\t\t_2" << endl << endl;
	cout << "Для получения ответа необходимо ввести какое-либо выражение. Пример:" << endl;
	cout << "(2+2)*2" << endl << "  =8" << endl;
	cout << "Заметьте, что скобочная последовательность должна являться корректной. \nДопускается отсутствие последних закрывающих скобок.\n";
	cout << "Программа поддерживает неограниченное количество переменных (ячеек памяти).\nВ каждую из них можно записать последний ответ.\n";
	cout << "Ячейка \"ans\" зарезервирована и всегда хранит последний ответ.\n";
	cout << "Пример использования:" << endl;
	cout << "afd+5*(6+7/3.5))" << endl << "  =43\nЗдесь ячейка \"afd\" хранила значение 3.\n" << endl;
	cout << "Программа поддерживает команды. Любая команда начинается с символа \"#\"." << endl <<"Список команд:" << endl << endl;
	cout << "#set <name>\t\tУстанавливает значение ячейки <name> равным последнему ответу" << endl;
	cout << "#list\t\t\tПоказывает все ответы, найденные за время работы программы" << endl;
	cout << "#date\t\t\tРассчёт разницы между днями" << endl;
	cout << "#cls\t\t\tСтирает всё с экрана, оставляя только начальный экран" << endl;
	cout << "#vacant\t\t\tСтирает абсолютно всё с экрана" << endl;
	cout << "#restart\t\tПерезагружает программу" << endl;
	cout << "#init\t\t\tТо же, что и #restart" << endl;
	cout << "#void\t\t\tТо же, что и #restart + #vacant" << endl;
	cout << "#help\t\t\tВыводит помощь по программе" << endl;
	cout << "#quit\t\t\tЗавершает программу" << endl;
	cout << "#exit\t\t\tТо же, что и #quit" << endl;
	cout << "#terminate\t\tТо же, что и #quit" << endl;

}

inline std::string smaller(std::string s) {
	std::string s_;
	for (int i = 0; i < s.size(); i++) {
		if ((int)s[i] <= 90 && (int)s[i] >= 65) s_ += (char)(int(s[i]) + 32);
		else s_ += s[i];
	}
	return s_;
}


std::string ctos(char c) {
	std::string s;
	s += c;
	return s;

}

inline std::string sub_name(std::string& s, int& i) {
	std::string ans;
	for (; i < s.size(); i++) {
		if (isalpha(s[i])) {
			ans += s[i];
			continue;
		}
		else break;
	}
	i--;
	return ans;
}

inline bool subname_is_ans(std::string& s, int& i) {
	return (s.substr(i, 3) == "ans") ? true : false;
}

inline void err_out(std::string s){
	cout << "Ошибка! " << s;
}

bool operator==(std::string s, inputType t) {
	if (smaller(s).substr(0,5) == "#quit" || smaller(s).substr(0, 10) == "#terminate" || smaller(s).substr(0, 5) == "#exit") {
		if (t == quit) return true;
		else return false;
	}
	else {
		if (s[0] == '#') {
			if (t == com) return true;
			else return false;
		}
		else {
			if (t == req) return true;
			else return false;
		}
	}
}

void main() {
	SetConsoleTitle("Calculator 2.0");
	bool julesEnabled = true;
	bool julesOnceDisabled = false;
	setlocale(LC_ALL, "RUS");
//	SetConsoleCP(1251);
	std::string input;
	int CBS;
	long double ans;
	int counter = 0;
	map<std::string, long double> memory;
	

	vector<element*> v;
	vector<long double> l_ans;
	symbol* sp;
	number* np;
	infoOut();

	do {
		np = nullptr;
		sp = nullptr;
		v.clear();
		getline(cin, input);

		if (input == quit) break;
//TODO обработка команд
	
		
		//проверка на корректность
		CBS = 0;
		try {
			if (isJules(input)&&julesEnabled) {
				cout << "Подлива" << endl;
				continue;
			}
			for (auto& t : input) {
				if ((int)t < 0) throw 11;
			}
			if (smaller(input) == "jules" && julesEnabled) {
				cout << "Podliva" << endl;
				continue;
			}
			if (input[0] == '#') {
				if (input.size() < 4) throw 8;
				if (smaller(input.substr(1, 3)) == "set") {
					int i = 4;
					for (; i < input.size(); i++) {
						if (isalpha(input[i])) break;
						if (input[i] != ' ') throw 3;
					}
					if (counter) {
						std::string __s = sub_name(input, i);
						if (__s == "") throw 1;
						if (__s == "ans") throw 10;
						memory[__s] = ans;
						cout << "Значение переменной \"" << __s << "\" установлено." << endl;

					}
					else throw 9;
					continue;
				}
				else {
					try {
						if (smaller(input.substr(1, 6)) == "vacant") {
							system("cls");
							continue;
						}
						if (smaller(input.substr(1, 11)) == "enablejules") {
							if (julesEnabled) cout << "Джулс и так enabled" << endl;
							else cout << "Ккккккк" << endl;
							julesEnabled = true;
							continue;
						}
						if (smaller(input.substr(1, 12)) == "disablejules") {
							if (!julesEnabled) cout << "Джулс и так disabled (в плане пасхалочки)" << endl;
							else {if(!julesOnceDisabled) cout << "Это же какой подливой нужно быть, чтобы disable Джулса??" << endl; 
							else cout << "Ну ты и даун конечно" << endl;
							julesOnceDisabled = true;
							}
							julesEnabled = false;
							continue;
						}
						if (smaller(input.substr(1, 3)) == "cls") {
							system("cls");
							infoOut();
							continue;
						}
						if (smaller(input.substr(1, 4)) == "list" || smaller(input.substr(1, 4)) == "show") {
							for (int i = 0; i < l_ans.size(); i++) {
								cout << i + 1 << ":\t" << l_ans[i] << endl;
							}
							if (l_ans.size() == 0)
								cout << "До сих пор не было получено ни одного результата!\n";
							continue;
						}
						if (smaller(input.substr(1, 4)) == "help") {
							helpOut();
							continue;
						}
						if (smaller(input.substr(1, 4)) == "init") {
							counter = 0;
							input = "";
							ans = 0;

							l_ans.clear();
							memory.clear();
							np = nullptr;
							sp = nullptr;
							for (int i = 0; i < v.size(); i++) {
								delete v[i];
							}
							v.clear();
							CBS = 0;
							system("cls");
							infoOut();
							continue;
						}
						if (smaller(input.substr(1, 4)) == "void") {
							counter = 0;
							input = "";
							ans = 0;

							l_ans.clear();
							memory.clear();
							np = nullptr;
							sp = nullptr;
							for (int i = 0; i < v.size(); i++) {
								delete v[i];
							}
							v.clear();
							CBS = 0;
							system("cls");
							continue;
						}
						if (smaller(input.substr(1, 7)) == "restart") {
							counter = 0;
							input = "";
							ans = 0;

							l_ans.clear();
							memory.clear();
							np = nullptr;
							sp = nullptr;
							for (int i = 0; i < v.size(); i++) {
								delete v[i];
							}
							v.clear();
							CBS = 0;
							system("cls");
							infoOut();
							continue;
						}
						if (smaller(input.substr(1, 4)) == "date"|| smaller(input.substr(1, 4)) == "data") {
							moment* m1 = nullptr, *m2 = nullptr;
						nr1:
							cout << "Введите первую дату в формате ДД.ММ.ГГГГ: ";
							
							if (parse(&m1) != true) goto nr1;
						nr2:

							cout << "Введите вторую дату в формате ДД.ММ.ГГГГ: ";
							if (parse(&m2) != true) goto nr2;
							datadiff((*m1), (*m2));
							continue;
						}
					}
					catch (out_of_range e) {
						throw 8;
					}
				}
				throw 8;
			}
			for (int i = 0; i < input.size(); i++) {
				if ((int)input[i] < 0) throw 11;
				if (isalpha(input[i])) {
					try {
						if (subname_is_ans(input,i) && !counter) throw 9;
						np = new number(memory.at(sub_name(input, i)));
						v.insert(v.end(), np);
						np = nullptr;
						continue;
					}
					catch (out_of_range& e) {
						throw 1;
					}
				}
				if (isdigit(input[i])) {
					np = new number;
					np->find_num(input, i);
					v.insert(v.end(), np);
					np = nullptr;
					continue;
				}
				switch (input[i]) {
				case '(':
					CBS++;
					continue;
				case ')':
					if (--CBS < 0) throw 2;
					continue;
				case '+':
					sp = new symbol(_add, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;
				case '-':
					sp = new symbol(_sub, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;
				case '*':
					sp = new symbol(_mlp, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;
				case '/':
					sp = new symbol(_div, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;
				case '^':
					sp = new symbol(_pow, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;
				case '_':
					sp = new symbol(_root, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;
				default:
					throw 3;
				}
			}


			while (v.size()) {
				float pm = -1;
				int it = -1;
				for (int i = 0; i < v.size(); i++) {
					if (v[i]->a() == _symbol) {
						if (dynamic_cast<symbol*>(v[i])->priority > pm) {
							pm = dynamic_cast<symbol*>(v[i])->priority;
							it = i;
						}
					}
				}
				if (it == -1) {
					ans = dynamic_cast<number*>(v[0])->value;
					break;
				}
				if (dynamic_cast<symbol*>(v[it])->otype == _sub) {
					if(it + 1 == v.size()) throw 4;
					if (v[it + 1]->a() == _number && it == 0) {
						if (dynamic_cast<number*>(v[it + 1])->value < 0) throw 4;
						np = new number(0-dynamic_cast<number*>(v[it + 1])->value);
						delete v[it];
						delete v[it + 1];
						v[it] = np;
						np = nullptr;
						v.erase(v.begin() + it + 1);
						continue;
					}
					if (v[it + 1]->a() == _number && v[it-1]->a()==_symbol) {
						if (dynamic_cast<number*>(v[it + 1])->value < 0) throw 4;
						np = new number(0 - dynamic_cast<number*>(v[it + 1])->value);
						delete v[it];
						delete v[it + 1];
						v[it] = np;
						np = nullptr;
						v.erase(v.begin() + it + 1);
						continue;
					}
				}
				if (((it == 0) && (dynamic_cast<symbol*>(v[it])->otype != _root)) || it + 1 == v.size()) throw 4;
				if ((dynamic_cast<symbol*>(v[it])->otype == _root) && (v[it + 1]->a() != _number)) throw 4;
				if ((dynamic_cast<symbol*>(v[it])->otype != _root)) {
					if (v[it - 1]->a() != _number || v[it + 1]->a() != _number)
						throw 4;
				}


				if ((dynamic_cast<symbol*>(v[it])->otype == _root)) {
					if (dynamic_cast<number*>(v[it + 1])->value < 0) throw 5;
					np = new number(sqrt(dynamic_cast<number*>(v[it + 1])->value));
					delete v[it];
					delete v[it + 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					np = nullptr;
					continue;
				}

				switch (dynamic_cast<symbol*>(v[it])->otype) {
				case _add:
					np = new number(dynamic_cast<number*>(v[it - 1])->value + dynamic_cast<number*>(v[it + 1])->value);
					if (isnan(np->value) || isinf(np->value)) throw 6;
					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;
				case _sub:
					np = new number(dynamic_cast<number*>(v[it - 1])->value - dynamic_cast<number*>(v[it + 1])->value);
					if (isnan(np->value) || isinf(np->value)) throw 6;
					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;
				case _mlp:
					np = new number((dynamic_cast<number*>(v[it - 1])->value) * (dynamic_cast<number*>(v[it + 1])->value));
					if (isnan(np->value) || isinf(np->value)) throw 6;
					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;
				case _div:
					np = new number((dynamic_cast<number*>(v[it - 1])->value) / (dynamic_cast<number*>(v[it + 1])->value));
					if (isnan(np->value) || isinf(np->value)) throw 6;
					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;
				case _pow:
					np = new number(pow((dynamic_cast<number*>(v[it - 1])->value), (dynamic_cast<number*>(v[it + 1])->value)));
					if (isnan(np->value) || isinf(np->value)) throw 6;
					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;
				}



			}
		}
		catch (int i) {
			switch (i) {
			case 1:
				err_out(_ER1);
				break;
			case 2:
				err_out(_ER2);
				break;
			case 3:
				err_out(_ER3);
				break;
			case 4:
				err_out(_ER4);
				break;
			case 5:
				err_out(_ER5);
				break;
			case 6:
				err_out(_ER6);
				break;
			case 7:
				err_out(_ER7);
				break;
			case 8:
				err_out(_ER8);
				break;
			case 9:
				err_out(_ER9);
				break;
			case 10:
				err_out(_ER10);
				break;
			case 11:
				err_out(_ER11);
				break;
			default:
				err_out("Неизвестная ошибка.\n");
			}
			for (int i = 0; i < v.size(); i++) {
				delete v[i];
				v[i] = nullptr;
			}
			v.clear();
			continue;
		}
		if (v.size()) {
			cout << "=  " << ans << endl;
			memory["ans"] = ans;
			l_ans.insert(l_ans.end(), ans);
			delete v[0];
			if (np != nullptr) {
				delete np;
			}
			if (sp != nullptr) {
				delete sp;
			}
			counter++;
		}
		

	} while (!(input == quit));
}
