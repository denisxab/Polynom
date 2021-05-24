#ifndef _PLCPP_
#define _PLCPP_
#include <iostream>
#include <string>
#include "Polynom.h"

/////////////////////
Polynom::Polynom(const std::string& s)
{
	this->writePolynom(s);
}

Polynom::Polynom()
{
	this->len = 0;
	this->variables = nullptr;
}

// Конструктор копии
Polynom::Polynom(const Polynom& pl)
{
	this->~Polynom();
	this->len = pl.len;
	this->variables = new int[this->len];
	for (size_t i = 0; i < this->len; i++)
	{
		this->variables[i] = pl.variables[i];
	}
}

Polynom::~Polynom()
{
	this->len = 0;
	if (this->variables != nullptr)
	{
		delete[] this->variables;
		this->variables = nullptr;
	}
}

void Polynom::writePolynom(const std::string& str)
{

	this->~Polynom();

	std::string s = str;
	char delimiter = ' ';
	size_t pos = 0;
	for (auto t : s)
	{
		if (t == delimiter)
		{
			this->len++;
		}
	}
	this->len++; // для свободного агрумента

	if (this->len >= this->mainpower) // Проверка полинома до 40 степени
	{
		this->len = this->mainpower - 1;
	}

	this->variables = new int[this->len];
	pos = 0;
	std::string token = "";
	unsigned int index = 0;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		this->variables[index++] = std::stoi(token);
		s.erase(0, pos + 1);
	}
	this->variables[index] = std::stoi(s);
}

Polynom& Polynom::operator=(const Polynom& pl)
{
	if (this != &pl) // защита от неправильного самоприсваивания
	{
		this->len = pl.len;
		delete[] this->variables;
		this->variables = new int[this->len];
		for (size_t i = 0; i < this->len; i++)
		{
			this->variables[i] = pl.variables[i];
		}
	}
	return *this;
}
/////////////////////

void Polynom::add(const Polynom& plB)
{
	if (this->len < plB.len)
	{

		Polynom tmpPl(*this);

		this->len = plB.len;
		delete[] this->variables;
		this->variables = new int[plB.len];

		size_t tmpIndex = 0;
		for (size_t i = this->len - tmpPl.len; i <= this->len - 1; i++)
		{
			this->variables[i] = tmpPl.variables[tmpIndex++];
		}

		for (size_t i = 0; i < this->len - tmpPl.len; i++)
		{
			this->variables[i] = 0;
		}

		for (int i = this->len - 1; i >= 0; i--)
		{
			this->variables[i] += plB.variables[i];
		}
	}
	else if (this->len >= plB.len)
	{
		int tmpIndex = plB.len - 1;
		for (int i = this->len - 1; i >= 0 && tmpIndex >= 0; i--)
		{
			this->variables[i] += plB.variables[tmpIndex--];
		}
	}
}

void Polynom::subtract(const Polynom& plB)
{
	if (this->len < plB.len)
	{

		Polynom tmpPl(*this);

		this->len = plB.len;
		delete[] this->variables;
		this->variables = new int[plB.len];

		size_t tmpIndex = 0;
		for (size_t i = this->len - tmpPl.len; i <= this->len - 1; i++)
		{
			this->variables[i] = tmpPl.variables[tmpIndex++];
		}

		for (size_t i = 0; i < this->len - tmpPl.len; i++)
		{
			this->variables[i] = 0;
		}

		for (int i = this->len - 1; i >= 0; i--)
		{
			this->variables[i] -= plB.variables[i];
		}
	}
	else if (this->len >= plB.len)
	{
		int tmpIndex = plB.len - 1;
		for (int i = this->len - 1; i >= 0 && tmpIndex >= 0; i--)
		{
			this->variables[i] -= plB.variables[tmpIndex--];
		}
	}
}

void Polynom::__extendPolynom(unsigned int lenNew, const Polynom& plA, const Polynom& plB, Polynom& savePlA, Polynom& savePlB)
{

	size_t tmpIndex;

	// Создаем новый массив с одинаковой длинной
	delete[] savePlA.variables;
	savePlA.variables = new int[lenNew];

	// Заполняем пустоты
	tmpIndex = 0;
	for (size_t i = lenNew - savePlA.len; i <= lenNew - 1; i++)
	{
		savePlA.variables[i] = plA.variables[tmpIndex++];
	}
	for (size_t i = 0; i < lenNew - savePlA.len; i++)
	{
		savePlA.variables[i] = 0;
	}

	// Создаем новый массив с одинаковой длинной
	delete[] savePlB.variables;
	savePlB.variables = new int[lenNew];

	// Заполняем пустоты
	tmpIndex = 0;
	for (size_t i = lenNew - savePlB.len; i <= lenNew - 1; i++)
	{
		savePlB.variables[i] = plB.variables[tmpIndex++];
	}
	for (size_t i = 0; i < lenNew - savePlB.len; i++)
	{
		savePlB.variables[i] = 0;
	}
}

unsigned int Polynom::__midLenPolynom(const Polynom& plA, const Polynom& plB, Polynom& savePlA, Polynom& savePlB)
{

	Polynom* savefh = nullptr;
	const Polynom* savesMain = nullptr;
	unsigned int rlen = 0;

	// Если второстипенный полнином длинее
	if (savePlA.len < savePlB.len)
	{
		rlen = savePlB.len;
		savefh = &savePlA;
		savesMain = &plA;
	}

	// Если главный полнином длинее то меняем длину у второстипенного
	else if (savePlA.len > savePlB.len)
	{
		rlen = savePlA.len;
		savefh = &savePlB;
		savesMain = &plB;
	}

	// Создаем новый массив с одинаковой длинной
	delete[] savefh->variables;
	savefh->variables = new int[rlen];

	// Заполняем пустоты
	size_t tmpIndex = 0;
	for (size_t i = rlen - savefh->len; i <= rlen - 1; i++)
	{
		savefh->variables[i] = savesMain->variables[tmpIndex++];
	}
	for (size_t i = 0; i < rlen - savefh->len; i++)
	{
		savefh->variables[i] = 0;
	}
	return rlen;
}

void Polynom::__fillVariables(unsigned int len, int num)
{
	this->len = len;
	if (this->variables != nullptr)
	{
		delete[] this->variables;
	}
	this->variables = new int[this->len];
	for (size_t i = 0; i < this->len; i++)
	{
		this->variables[i] = num;
	}
}

unsigned int Polynom::__minPower(const Polynom& plA, const Polynom& plB)
{
	unsigned int minPw;
	// Для скалярной величины
	if (plB.len == 1 || plA.len == 1)
	{
		minPw = 1;
	}
	else if (plA.len <= plB.len)
	{
		minPw = plA.len - 1;
	}
	else if (plA.len > plB.len)
	{
		minPw = plB.len - 1;
	}
	else
	{
		minPw = 0;
	}
	return minPw;
}

void Polynom::multiplication(const Polynom& plB)
{
	//https://planetcalc.ru/7743/

	// Хранит весь основной полином
	Polynom re1;
	re1 = *this;

	// Основной полином сумматор
	this->__fillVariables((this->len + plB.len) - 1, 0);

	// Вспомогательный полином
	Polynom re2;
	re2.__fillVariables(this->len, 0);

	// Для корректного сдвига вспомогательно полинома
	unsigned int minPower = __minPower(*this, plB);

	// Сдвиг уменьшения коэффициентов у вспомогательного полинома
	unsigned int step = 0;
	for (size_t i = 0; i < plB.len && plB.variables[i] != 0; i++)
	{
		re2.__fillVariables(re2.len - step, 0);

		// Каждый 3 раз уменьшаем длину вспомогательного полинома
		if (i % minPower == 0)
		{
			step++;
		}

		// Умножаем скобку на коэффициент полинома
		for (size_t z = 0; z < re1.len; z++)
		{
			re2.variables[z] = re1.variables[z] * plB.variables[i];
		}

		//std::cout << "re1: ";
		//re1.print_Equation();
		//std::cout << "re2: ";
		//re2.print_Equation();

		// Складываем полиномы
		this->add(re2);

		std::cout << '[' << i << "] ";
		this->print_Equation();
	}
	//std::cout << std::endl;
}

void Polynom::multiplication(int scalar)
{
	for (size_t i = 0; i < this->len; i++)
	{
		this->variables[i] *= scalar;
	}
}

void Polynom::mod(Polynom& unitPl, Polynom& remainsPl, const Polynom& plB, int mods)
{
	//https://math.semestr.ru/gauss/factor.php

	unsigned int mixLen = 0;
	unsigned int minLen = 0;
	const Polynom* maxPl = nullptr;
	const Polynom* miniPl = nullptr;

	if (this->len >= plB.len)
	{
		mixLen = this->len;
		minLen = plB.len;
		maxPl = this;
		miniPl = &plB;
	}
	// Если делимое больше чем делитель
	else
	{
		remainsPl = *this;
		unitPl.writePolynom("0");
		return;
	}

	//1) Полином разности степеней для умножения
	Polynom unit;
	//2) Полином для умножения
	Polynom re1;
	re1 = *miniPl;
	//3) Полином для вычитания - Остаток
	Polynom re2;
	re2 = *maxPl;
	//4) Полином целой части - Целая часть
	Polynom re3;
	re3.__fillVariables((mixLen - minLen) + 1, 0);

	for (size_t i = 0; i < re3.len; i++)
	{

		std::cout << '[' << i << "]\n";

		//1) Создаем временный полином целой части для дальнейшего умножение на делитель
		unit.__fillVariables((mixLen - minLen) + 1, 0);
		unit.variables[0] = re2.variables[i];

		std::cout << "re1: ";
		//2) Умножение кофицента целой части на делимое
		re1.multiplication(unit);
		if (mods != 0)
		{
			for (size_t i = 0; i < re1.len; i++)
			{
				// Если остаток отрицательный
				if (re1.variables[i] < 0)
				{
					re1.variables[i] = mods - (re1.variables[i] % mods);
				}
				re1.variables[i] %= mods;
			}
		}

		//3) Вычитание полиномов
		re2.subtract(re1);
		if (mods != 0)
		{
			for (size_t i = 0; i < re1.len; i++)
			{
				// Если остаток отрицательный
				if (re2.variables[i] < 0)
				{
					re2.variables[i] = mods + (re2.variables[i] % mods);
				}
				re2.variables[i] %= mods;
			}
		}
		std::cout << "re2: ";
		re2.print_Equation();

		//4) Сохранение целой части
		re3.variables[i] = unit.variables[0];
		std::cout << "re3: ";
		re3.print_Equation();

		// Нужно умножаем делитель
		re1 = *miniPl;

		// Сокращаем коэффициент у следующего полинома
		mixLen--;
	}
	remainsPl = re2;
	unitPl = re3;
}

bool Polynom::logic_mathematical_operations(char sign, std::string user_consol_polynom)
{

	Polynom tmpPl(user_consol_polynom);

	switch (sign)
	{
	case '+':
		this->add(tmpPl);
		break;

	case '-':
		this->subtract(tmpPl);
		break;

	case '*':
		this->multiplication(tmpPl);
		break;

	default:
		return false;
	}
	return true;
}

/////////////////////
void Polynom::print_Equation()
{

	//for (size_t i = 0; i < this->len; i++)
	//{
	//	std::cout << this->variables[i] << " ";
	//}
	//std::cout << std::endl;

	size_t revers_index = this->len - 1;
	for (size_t i = 0; i < this->len; i++, revers_index--)
	{
		if (this->variables[i] != 0)
		{
			if (this->variables[i] > 0 and i > 0)
			{
				std::cout << '+';
			}
			if (i + 1 < this->len)
			{

				if (this->variables[i] != 1)
				{
					std::cout << variables[i];
				}

				std::cout << "x";
				if (revers_index > 1)
				{
					std::cout << '^' << revers_index;
				}
			}
			else
			{
				std::cout << variables[i];
			}
		}
	}
	std::cout << std::endl;
}

void Polynom::setVariables(const int* arrint, const int lenarr)
{

	this->~Polynom();
	std::string tmpstr = "";
	for (size_t i = 0; i < lenarr; i++)
	{
		tmpstr += std::to_string(arrint[i]);
		if (i + 1 < lenarr)
		{
			tmpstr += " ";
		}
	}
	this->writePolynom(tmpstr);
}
/////////////////////
#endif
