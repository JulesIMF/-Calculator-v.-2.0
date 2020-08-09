#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cmath>
#include <clocale>
#include <cstdlib>
#include <cctype>
#include <map>
#include <list>
#include <time.h>
//<Element.h>
enum ElementType { _symbol, _number, _element }; //Тип элемента
enum OperatorType { _add, _sub, _mlp, _div, _pow, _root }; //Тип оператора


class Element
{
public:
	virtual ~Element();
	virtual ElementType elementType(void);
protected:

};

class Symbol : virtual public Element
{
public:
	float priority;
	ElementType elementType(void);
	Symbol(OperatorType o, int p);
	OperatorType otype;
};

class Number : public Element
{
public:
	Number();
	ElementType elementType(void);
	Number(long double d);
	long double value = 0;
	void find_num(std::string& s, int& i);
};
//</Element.h>

//<Element.cpp>
//Цифра в число
int aaoi(char c) {
	return static_cast<int>(c - '0');
}

Element::~Element()
{
}
ElementType Element::elementType(void) { return _element; }
ElementType Symbol::elementType(void) { return _symbol; }
ElementType Number::elementType(void) { return _number; }

Number::Number(long double d)
{
	value = d;
}

void Number::find_num(std::string& s, int& i)
{
	bool dot = false;
	int p = 1;
	long double v = 0;

	for (; (i != s.size()); i++)
	{
		if (isdigit(s[i]))
		{
			//Часть до точки
			if (!dot)
			{
				v *= 10;
				v += aaoi(s[i]);
			}
			//Часть после точки
			else
			{
				v += pow(0.1, p++) * aaoi(s[i]);
			}
			continue;
		}

		//Точка
		if (s[i] == '.')
		{
			if (!dot)
				dot = true;
			else throw 7; //Невозможно определить принадлежность этой точки
			continue;
		}
		i--;
		value = v;
		return;
	}
	i--;
	value = v;
	return;
}

Number::Number() = default;

Symbol::Symbol(OperatorType o, int p)
{
	priority = 0;
	otype = o;
	switch (o)
	{
	case _pow:
	case _root:
		priority += 0.25;
	case _mlp:
	case _div:
		priority += 0.25;
	case _add:
	case _sub:
		priority += static_cast<float>(p);
	}

}
//</Element.cpp>


//Список исключений
const char* ExceptionMessages[] =
{
	/*1*/  "Не найдена переменная.\n",
	/*2*/  "Скобочная последовательность в запросе не является корректной.\n",
	/*3*/  "Неизвестный символ.\n",
	/*4*/  "Невозможно применить один из операторов.\n",
	/*5*/  "Комплексные числа не поддерживаются в этой версии: извлечение квадратного корня из отрицательного числа невозможно.\n",
	/*6*/  "Математически некорректное действие (результатом является \"NaN\").\n",
	/*7*/  "Невозможно определить принадлежность одной из точек.\n",
	/*8*/  "Неизвестная команда.\n",
	/*9*/  "Переменная \"ans\" ещё не хранит значения.\n",
	/*10*/ "Переменной \"ans\" невозможно менять значение вручную.\n",
	/*11*/ "Содержатся неподдерживаемые символы.\n",
	/*12*/ "Некорректное выражение.\n",
};

//char -> int
extern int aaoi(char c);

//Функция ставит слово "годик" в соответствующий CurrentYear падеж
std::string age(int CurrentYear)
{
	if (CurrentYear % 100 >= 10 && CurrentYear % 100 <= 20)
		return "годиков";
	if (CurrentYear % 10 == 0 || CurrentYear % 10 >= 5)
		return "годиков";
	if (CurrentYear % 10 == 1)
		return "годик";

	return "годика";
}

//Функция возвращает мой возраст на момент запуска программы
int julesAge()
{
	time_t tCurrentTime;
	time(&tCurrentTime);
	tm* tk = localtime(&tCurrentTime);

	if (tk->tm_mon < 1)
		return tk->tm_year - 103;
	if (tk->tm_mon == 1 && tk->tm_mday < 22)
		return tk->tm_year - 103;

	return tk->tm_year - 102;
}

//Функция выводит начальный экран
void infoOut()
{
	std::cout << "Calculator v. 2.2" << std::endl << "Джулс, " << julesAge();
	std::cout << ((julesAge() != 16) ? (" (на момент создания 16)") : ("")) << " ";
	std::cout << age(julesAge()) << ", 2018 год." << std::endl;
	std::cout << "Учтите, что киррилические символы не поддерживаются." << std::endl;
	std::cout << "Для вывода помощи наберите \"#help\"." << std::endl << std::endl;
}

//¤†“‹‘
//„¦г«б

class MomentChange
{
public:
	bool yChanged, mChanged;
	MomentChange(bool y, bool m)
	{
		yChanged = y;
		mChanged = m;
	}
};

class Moment
{
public:
	Moment(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}



	MomentChange increment()
	{
		bool monthChanged = false, yearChanged = false;

		if (day == 31 && (month == 1 || month == 3 || month == 5 ||
			month == 7 || month == 8 || month == 10 || month == 12))

		{
			day = 1;
			month++;
			monthChanged = true;
		}



		if (day == 30 && (month == 4 || month == 6 ||
			month == 9 || month == 11))
		{
			day = 1;
			month++;
			monthChanged = true;
		}


		if (day == 28 && (month == 2) &&
			(year % 4 != 0 || (year % 400 != 0 && year % 100 == 0)))

		{
			day = 1;
			month++;
			monthChanged = true;
		}



		if (day == 29 && (month == 2) &&
			((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))

		{
			day = 1;
			month++;
			monthChanged = true;
		}
		if (month == 13)
		{
			year++;
			month = 1;
			yearChanged = true;
		}

		if (!monthChanged) day++;
		return MomentChange(monthChanged, yearChanged);
	}



	void increment_nl()
	{
		bool monthChanged = false, yearChanged = false;
		if (day == 30 && (month == 0 || month == 2 || month == 4 ||
			month == 6 || month == 7 || month == 9 || month == 11))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (day == 29 && (month == 3 || month == 5 ||
			month == 8 || month == 10))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (day == 27 && (month == 1) &&
			((year + 1) % 4 != 0 ||
				((year + 1) % 400 != 0 && (year + 1) % 100 == 0)))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (day == 28 && (month == 1) &&
			(((year + 1) % 4 == 0 && (year + 1) % 100 != 0) ||
				(year + 1) % 400 == 0))
		{
			day = 0;
			month++;
			monthChanged = true;
		}
		if (month == 12)
		{
			year++;
			month = 0;
			yearChanged = true;
		}
		if (!monthChanged) day++;
	}




	bool operator==(Moment& moment)
	{
		if (year == moment.getYear() &&
			month == moment.getMonth() &&
			day == moment.getDay())   return true;

		else
			return false;
	}

	bool operator!=(Moment& moment)
	{
		return !(*this == moment);
	}



	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

protected:
	int day, month, year;
};


//Следующие три функции возращают слова
//"год", "месяц" и "день" в соответствующей
//числительному форме

std::string y_case(int numeral)
{
	if (numeral == 0)
		return "";

	if (numeral % 100 >= 10 && numeral % 100 <= 20)
		return "лет";

	if (numeral % 10 == 0 || numeral % 10 >= 5)
		return "лет";

	if (numeral % 10 == 1)
		return "год";

	return "года";
}

std::string m_case(int numeral)
{
	if (numeral == 0)
		return "";

	if (numeral % 100 >= 10 && numeral % 100 <= 20)
		return "месяцев";

	if (numeral % 10 == 0 || numeral % 10 >= 5)
		return "месяцев";

	if (numeral % 10 == 1)
		return "месяц";

	return "месяца";
}

std::string d_case(int numeral)
{
	if (numeral % 100 >= 10 && numeral % 100 <= 20)
		return "дней";

	if (numeral % 10 == 0 || numeral % 10 >= 5)
		return "дней";

	if (numeral % 10 == 1)
		return "день";

	return "дня";
}

bool parseDate(Moment * *moment)
{
	std::string s;
	std::cin >> s;
	int d, m, y;

	//Выражение должно иметь вид "dd.mm.yyyy"
	if (s.length() != (2 + 2 + 4 + 2))
	{
		std::cout << "Дата введена неверно" << std::endl;
		return false;
	}

	if (!isdigit(s[0]) || !isdigit(s[1]) ||
		!isdigit(s[3]) || !isdigit(s[4]) ||
		!isdigit(s[6]) || !isdigit(s[7]) ||
		!isdigit(s[8]) || !isdigit(s[9]) ||
		isdigit(s[2]) || isdigit(s[5]))
	{
		std::cout << "Дата введена неверно" << std::endl;
		return false;
	}

	//Если выражение корректно,
	//устанавливаем дату

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

	//Проверка на високосный год и 29 февраля
	if (d == 29 && m == 2 &&
		(y % 4 != 0 || (y % 100 == 0 && y % 400 != 0)))

	{
		std::cout << "Дата не существует" << std::endl;
		return false;
	}

	//Проверка на наличие дня в феврале
	if (d > 29 && m == 2)
	{
		std::cout << "Дата не существует" << std::endl;
		return false;
	}

	//Проверка на наличие дня в
	//апреле, июне, сентябре, ноябре
	if (d > 30 && (m == 4 || m == 6 ||
		m == 9 || m == 11))

	{
		std::cout << "Дата не существует" << std::endl;
		return false;
	}

	//Проверка на наличие дня в
	//январе, марте, мае, июле, 
	//августе, октябре, декабре
	if (d > 31 && (m == 1 || m == 3 || m == 5 ||
		m == 7 || m == 8 || m == 10 || m == 12))

	{
		std::cout << "Дата не существует" << std::endl;
		return false;
	}

	//А существует ли вообще такой месяц?
	if (m > 12)
	{
		std::cout << "Дата не существует" << std::endl;
		return false;
	}

	//Если дата корректна,
	//устанавливаем ее
	*moment = new Moment(d, m, y);
	return true;
}

bool isGreater(Moment m1, Moment m2)
{
	if (m1.getYear() > m2.getYear())
		return true;
	if (m1.getYear() < m2.getYear())
		return false;
	if (m1.getMonth() > m2.getMonth())
		return true;
	if (m1.getMonth() < m2.getMonth())
		return false;
	if (m1.getDay() > m2.getDay())
		return true;

	return false;
}


void dataDifference(Moment m1, Moment m2)
{

	//Если m1 был позже m2,
	//необходимо свапнуть их
	if (isGreater(m1, m2)) std::swap(m1, m2);

	//Считаем прошешие дни,
	//инкрементируя счетчик counter
	Moment counter(0, 0, 0);

	int d = 0, m = 0, y = 0;

	while (m1 != m2 && (isGreater(m2, m1)))
	{
		d++;
		m1.increment();
		counter.increment_nl();
		if (d % 30 == 0) m++;
		if (d % 365 == 0) y++;
	}

	if (d == 0)
	{
		std::cout << "Даты равны" << std::endl;
		return;
	}

	std::cout << "Между днями разница в ";

	if (counter.getYear() != 0)
	{
		std::cout << counter.getYear() << " " << y_case(counter.getYear());

		if (counter.getMonth() != 0 && counter.getDay() != 0) std::cout << ", ";

		else
		{
			if (counter.getMonth() != 0 || counter.getDay() != 0) std::cout << " и ";
		}
	}

	if (counter.getMonth() != 0)
	{
		std::cout << counter.getMonth() << " " << m_case(counter.getMonth());
		if (counter.getDay() != 0) std::cout << " и ";
	}

	if (counter.getDay() != 0)
	{
		std::cout << counter.getDay() << " " << d_case(counter.getDay());
	}

	std::cout << "." << std::endl;

	std::cout << "Также разница составляет ровно " << d
		<< " " << d_case(d) << "." << std::endl;
}


void helpOut() {
	std::cout << "Доступные операции:" << std::endl;
	std::cout << "Операция\t\t\t\tПример" << std::endl << std::endl;
	std::cout << "Сложение\t\t\t\t2+2" << std::endl;
	std::cout << "Вычитание\t\t\t\t3-8.5" << std::endl;
	std::cout << "Умножение\t\t\t\t8*9" << std::endl;
	std::cout << "Деление\t\t\t\t\t91/13" << std::endl;
	std::cout << "Возведение в степень\t\t\t2^10" << std::endl;
	std::cout << "Взятие квадратного корня\t\t_2" << std::endl << std::endl;
	std::cout << "Для получения ответа необходимо ввести какое-либо выражение. Пример:" << std::endl;
	std::cout << "(2+2)*2" << std::endl << "  =8" << std::endl;
	std::cout << "Заметьте, что скобочная последовательность должна являться корректной. \n"
		"Допускается отсутствие последних закрывающих скобок.\n";
	std::cout << "Программа поддерживает неограниченное количество переменных "
		"(ячеек памяти).\nВ каждую из них можно записать последний ответ.\n";
	std::cout << "Ячейка \"ans\" зарезервирована и всегда хранит последний ответ.\n";
	std::cout << "Пример использования:" << std::endl;
	std::cout << "afd+5*(6+7/3.5)" << std::endl << "=  43\nЗдесь ячейка \"afd\" хранила значение 3.\n" << std::endl;
	std::cout << "Программа поддерживает команды. Любая команда начинается с символа \"#\"."
		<< std::endl << "Список команд:" << std::endl << std::endl;
	std::cout << "#set <name>\t\tУстанавливает значение ячейки <name> равным последнему ответу" << std::endl;
	std::cout << "#list\t\t\tПоказывает все ответы, найденные за время работы программы" << std::endl;
	std::cout << "#date\t\t\tРассчёт разницы между днями" << std::endl;
	std::cout << "#cls\t\t\tСтирает всё с экрана, оставляя только начальный экран" << std::endl;
	std::cout << "#vacant\t\t\tСтирает абсолютно всё с экрана" << std::endl;
	std::cout << "#restart\t\tПерезагружает программу" << std::endl;
	std::cout << "#init\t\t\tТо же, что и #restart" << std::endl;
	std::cout << "#void\t\t\tТо же, что и #restart + #vacant" << std::endl;
	std::cout << "#help\t\t\tВыводит помощь по программе" << std::endl;
	std::cout << "#quit\t\t\tЗавершает программу" << std::endl;
	std::cout << "#exit\t\t\tТо же, что и #quit" << std::endl;
	std::cout << "#terminate\t\tТо же, что и #quit" << std::endl;

}



//Функция опускает регистр всех букв в строке
inline std::string smaller(std::string s)
{
	std::string s_;
	for (int i = 0; i < s.size(); i++)
	{
		if ((int)s[i] <= 90 && (int)s[i] >= 65) s_ += (char)(int(s[i]) + 32);
		else s_ += s[i];
	}
	return s_;
}



//Функция возвращает строку,
//состоящую из одного символа
std::string ctos(char c)
{
	std::string s_;
	s_ += c;
	return s_;
}

//Функция выделяет имя переменной
//из запроса, модифицируя итератор i
inline std::string sub_name(std::string & s, int& i)
{
	std::string ans;
	for (; i < s.size(); i++)
	{
		if (isalpha(s[i]))
		{
			ans += s[i];
			continue;
		}

		else break;
	}
	i--;
	return ans;
}



//Функция проверяет, является ли
//имя переменной зарезервированной
//переменной "ans"
inline bool subname_is_ans(std::string & s, int& i)
{
	return (s.substr(i, 3) == "ans") ? true : false;
}



//Функция выводит сообщение об ошибке
inline void err_out(std::string s)
{
	std::cout << "Ошибка! " << s;
}



//Функция проверяет, является ли
//введеный запрос командой к выходу
bool isQuit(std::string s)
{
	if (smaller(s).substr(0, 5) == "#quit" ||
		smaller(s).substr(0, 10) == "#terminate" ||
		smaller(s).substr(0, 5) == "#exit") return true;

	else return false;
}



//Точка входа в приложение
int main()
{
	//wchar_t applicationTitle[] = L"Calculator 2.2\0";
	//SetConsoleTitle(applicationTitle);
	bool julesEnabled = true;
	bool julesOnceDisabled = false;
	setlocale(LC_ALL, "RUS");
	//	SetConsoleCP(1251);
	std::string input;
	int CBS;
	long double ans = 0.0;
	int counter = 0;

	std::map<std::string, long double> memory; //Здесь хранятся переменные


	std::vector<Element*> v;
	std::vector<long double> listOfAnswers;
	Symbol* sp; //Указатель на символ (оператор)
	Number* np; //Указатель на число
	infoOut();

	do
	{
		np = nullptr;
		sp = nullptr;
		v.clear();
		std::getline(std::cin, input);

		//Первым делом проверяем,
		//является ли введенный запрос
		//командой выхода?

		if (isQuit(input))
			break;

		//проверка на корректность
		CBS = 0;
		try
		{

			//Проверяем, есть ли запрещенные символы
			for (auto& t : input)
			{
				if ((int)t < 0) throw 11;
			}


			if (smaller(input) == "jules" && julesEnabled)
			{
				std::cout << "Podliva" << std::endl;
				continue;
			}



			//<Обработка команд>

						//Проверяем, является ли intput командой
			if (input[0] == '#')
			{
				if (input.size() < 4) throw 8; //Нет команды короче 3 символов

				//Команда установки переменной
				if (smaller(input.substr(1, 3)) == "set")
				{
					//Продвигаем i на 4 символа вперед 
					//и проверяем, все ли нормально
					int i = 4;
					for (; i < input.size(); i++)
					{
						if (isalpha(input[i])) break;

						if (input[i] != ' ')
							throw 3; //Неизвестный символ
					}

					//Устанавливать переменную можно, только
					//если хоть раз выполнялось вычисление
					if (counter)
					{
						std::string variableName = sub_name(input, i);
						if (variableName == "")
							throw 1; //Что за переменная "" ?

						if (variableName == "ans")
							throw 10; //Зарезервированное имя

						memory[variableName] = ans;
						std::cout << "Значение переменной \"" << variableName
							<< "\" установлено." << std::endl;

					}
					else throw 9; //Переменная "ans" еще не хранит значение
					continue;
				}

				//Все остальные команды
				else
				{

					//<Пасхалка>
					if (smaller(input.substr(1, 11)) == "enablejules")
					{
						if (julesEnabled) std::cout << "Джулс и так enabled" << std::endl;
						else std::cout << "Ккккккк" << std::endl;
						julesEnabled = true;
						continue;
					}
					if (smaller(input.substr(1, 12)) == "disablejules")
					{
						if (!julesEnabled) std::cout << "Джулс и так disabled (в плане пасхалочки)" << std::endl;
						else
						{
							if (!julesOnceDisabled) std::cout << "Это же какой подливой нужно быть, чтобы disable Джулса??" << std::endl;
							else std::cout << "Ну ты и даун конечно" << std::endl;
							julesOnceDisabled = true;
						}
						julesEnabled = false;
						continue;
					}
					//</Пасхалка>

					//Пустой экран
					if (smaller(input.substr(1, 6)) == "vacant")
					{
						system("cls");
						continue;
					}


					//Пустой экран, но с информацией о программе
					if (smaller(input.substr(1, 3)) == "cls")
					{
						system("cls");
						infoOut();
						continue;
					}

					//Вывести все результаты, которые были
					//получены в ходе работы программы
					if (smaller(input.substr(1, 4)) == "list" || smaller(input.substr(1, 4)) == "show")
					{
						for (int i = 0; i < listOfAnswers.size(); i++)
						{
							std::cout << i + 1 << ":\t" << listOfAnswers[i] << std::endl;
						}
						if (listOfAnswers.size() == 0)
							std::cout << "До сих пор не было получено ни одного результата!\n";
						continue;
					}

					//Команда вывода помощи
					if (smaller(input.substr(1, 4)) == "help")
					{
						helpOut();
						continue;
					}

					//Перезагрузка программы
					if (smaller(input.substr(1, 4)) == "init" ||
						smaller(input.substr(1, 7)) == "restart")

					{
						counter = 0;
						input = "";
						ans = 0;

						listOfAnswers.clear();
						memory.clear();
						np = nullptr;
						sp = nullptr;
						for (int i = 0; i < v.size(); i++)
						{
							delete v[i];
						}
						v.clear();
						CBS = 0;
						system("cls");
						infoOut();
						continue;
					}

					//Перезагрузка программы + system("cls")
					if (smaller(input.substr(1, 4)) == "void")
					{
						counter = 0;
						input = "";
						ans = 0;

						listOfAnswers.clear();
						memory.clear();
						np = nullptr;
						sp = nullptr;
						for (int i = 0; i < v.size(); i++)
						{
							delete v[i];
						}
						v.clear();
						CBS = 0;
						system("cls");
						continue;
					}
				}
				throw 8;
			}

			//</Обработка команд>



			//<Парсинг>

			for (int i = 0; i < input.size(); i++)
			{

				//Если тут буква, то это переменная
				if (isalpha(input[i]))
				{
					try
					{
						if (subname_is_ans(input, i) && !counter)
							throw 9; //Запрос переменной ans, когда она еще не хранит значения

						np = new Number(memory.at(sub_name(input, i)));
						v.insert(v.end(), np);
						np = nullptr;
						continue;
					}
					catch (std::out_of_range& e)
					{
						throw 1;
						//Если нет такой переменной, сюда прилетит 
						//такое исключение при попытке найти ее в memory
					}
				}


				//Если цифра, то тут число
				if (isdigit(input[i]))
				{
					np = new Number;
					np->find_num(input, i);
					v.insert(v.end(), np);
					np = nullptr;
					continue;
				}


				//В остальных случаях это оператор

				//Ищем соответствующий оператор
				switch (input[i])
				{

					//Скобки:
				case '(':
					CBS++; //Увеличиваем кол-во скобок
					continue;


				case ')':
					if (--CBS < 0)
						throw 2; //Уменьшаем колво скобок,
								 //проверяя, а можно ли это сделать

					continue;

					//Бинарные операторы:
				case '+':
					sp = new Symbol(_add, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '-':
					sp = new Symbol(_sub, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '*':
					sp = new Symbol(_mlp, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '/':
					sp = new Symbol(_div, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


				case '^':
					sp = new Symbol(_pow, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;

					//Унарный оператор:    
				case '_':
					sp = new Symbol(_root, CBS);
					v.insert(v.end(), sp);
					sp = nullptr;
					continue;


					//Все остальное не определено как оператор        
				default:
					throw 3;
				}
			}

			//</Парсинг>



			//<Вычисление выражения>
			while (v.size())
			{
				//Поиск символа с максимальным приоритетом
				float maxPriority = -1; //Здесь хранится максимальный приоритет
				int it = -1; //А здесь указатель на символ с максимальным приоритетом
				for (int i = 0; i < v.size(); i++)
				{
					//Если текущий элемент - символ, то стоит его проверить
					if (v[i]->elementType() == _symbol)
					{
						if (dynamic_cast<Symbol*>(v[i])->priority > maxPriority)
						{
							maxPriority = dynamic_cast<Symbol*>(v[i])->priority;
							it = i;
						}
					}
				}

				//Случай, когда вообще нет ни одного оператора
				if (it == -1)
				{
					if (v.size() != 1)
						throw 12; //По-моему, такое невозможно, но всё-таки

					ans = dynamic_cast<Number*>(v[0])->value;
					break;
				}

				//Унарный минус (при рефакторинге я стал сомневаться в его работоспособности)
				if (dynamic_cast<Symbol*>(v[it])->otype == _sub)
				{
					if (it + 1 == v.size())
						throw 4; //Нет правого операнда

					//it == 0:
					if (v[it + 1]->elementType() == _number && it == 0)
					{
						//Следующая закомментированная строчка - баг, который есть в приложении:
						//if (dynamic_cast<Number*>(v[it + 1])->value < 0) throw 4;

						np = new Number(0 - dynamic_cast<Number*>(v[it + 1])->value);
						delete v[it];
						delete v[it + 1];
						v[it] = np;
						np = nullptr;
						v.erase(v.begin() + it + 1);
						continue;
					}


					//it != 0:
					if (v[it + 1]->elementType() == _number && v[it - 1]->elementType() == _symbol)
					{
						//Следующая закомментированная строчка - баг, который есть в приложении:
						//if (dynamic_cast<Number*>(v[it + 1])->value < 0) throw 4;


						np = new Number(0 - dynamic_cast<Number*>(v[it + 1])->value);
						delete v[it];
						delete v[it + 1];
						v[it] = np;
						np = nullptr;
						v.erase(v.begin() + it + 1);
						continue;
					}
				}

				//Если неоткуда взять левый/правый операнд
				if (((it == 0) && (dynamic_cast<Symbol*>(v[it])->otype != _root))
					|| it + 1 == v.size()) throw 4;

				//Если квадратный корень справа обнаруживает символ
				if ((dynamic_cast<Symbol*>(v[it])->otype == _root) &&
					(v[it + 1]->elementType() != _number)) throw 4;

				//Если бинарный оператор не находит слева и справа по операнду
				if ((dynamic_cast<Symbol*>(v[it])->otype != _root))
				{
					if (v[it - 1]->elementType() != _number ||
						v[it + 1]->elementType() != _number)
						throw 4;
				}


				//Квадратный корень
				if ((dynamic_cast<Symbol*>(v[it])->otype == _root))
				{
					if (dynamic_cast<Number*>(v[it + 1])->value < 0)
						throw 5; //Извлечение sqrt из отрицательного числа

					np = new Number(sqrt(dynamic_cast<Number*>(v[it + 1])->value));


					delete v[it];
					delete v[it + 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					np = nullptr;
					continue;
				}

				switch (dynamic_cast<Symbol*>(v[it])->otype) {
					//Сложение
				case _add:
					np = new Number(dynamic_cast<Number*>(v[it - 1])->value
						+
						dynamic_cast<Number*>(v[it + 1])->value);


					if (isnan(np->value) || isinf(np->value))
						throw 6; //Вряд ли такое возможно, но все же

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//Вычитание
				case _sub:
					np = new Number(dynamic_cast<Number*>(v[it - 1])->value
						-
						dynamic_cast<Number*>(v[it + 1])->value);


					if (isnan(np->value) || isinf(np->value))
						throw 6; //Аналогично

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//Умножение
				case _mlp:
					np = new Number((dynamic_cast<Number*>(v[it - 1])->value)
						*
						(dynamic_cast<Number*>(v[it + 1])->value));


					if (isnan(np->value) || isinf(np->value))
						throw 6; //Аналогично

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//Деление
				case _div:
					np = new Number((dynamic_cast<Number*>(v[it - 1])->value)
						/
						(dynamic_cast<Number*>(v[it + 1])->value));


					if (isnan(np->value) || isinf(np->value))
						throw 6; //А вот тут может быть деление на ноль!

					delete v[it];
					delete v[it + 1];
					delete v[it - 1];
					v[it] = np;
					v.erase(v.begin() + it + 1);
					v.erase(v.begin() + it - 1);
					np = nullptr;
					break;

					//Возведение в степень
				case _pow:
					np = new Number(pow((dynamic_cast<Number*>(v[it - 1])->value),
						(dynamic_cast<Number*>(v[it + 1])->value)));


					if (isnan(np->value) || isinf(np->value))
						throw 6; //Тут тоже что-нибудь да может произойти

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
			//</Вычисление выражения>
		} //Здесь закончился основной блок try


		//Обрабатываем исключения
		catch (int i)
		{
			err_out(ExceptionMessages[i - 1]);

			for (int i = 0; i < v.size(); i++)
			{
				delete v[i];
				v[i] = nullptr;
			}
			v.clear();
			continue;
		}

		//Если мы получили значение, то можно его вывести и записать в ans
		if (v.size())
		{
			std::cout << "=  " << ans << std::endl;
			memory["ans"] = ans;
			listOfAnswers.insert(listOfAnswers.end(), ans);
			delete v[0];
			if (np != nullptr)
			{
				delete np;
			}
			if (sp != nullptr)
			{
				delete sp;
			}
			counter++;
		}


	} while (true);
}
