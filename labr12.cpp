#include <string>
#include <iostream>
#include <Windows.h>
#include"Polynom.h"


#define _DEBUG



int main()
{

	SetConsoleCP(1251);//установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	/*
	Для всех заданий используйте приватные поля для данных, определите конструктор, который должен содержать значения по умолчанию, напишите методы установки и извлечения значений (set, get), выполнения операций ввода и вывода значения объекта созданного класса. Напишите конструктор копий, оператор присваивания, деструктор.


	метод умножение
	метод

	Создайте класс Polynom (Многочлен), который хранит коэффициенты и степень полинома(Многочлна) степени <= 40. Реализовать операции сложения, вычитания и умножения на скаляр.
	*/


	char sign;
	int scalar;


#ifndef _DEBUG_
	std::cout << "Введите полином в виде: 3 2 -1" << '\n';
	std::string tmp_inp_user;
	getline(std::cin, tmp_inp_user, '\n');

#endif


#ifdef _DEBUG_
	// Проверка записи в класса Polynom
	std::string tmp_inp_user = "3 3 3";
#endif


	Polynom pl;
	pl.writePolynom(tmp_inp_user);
	pl.print_Equation();



#ifndef _DEBUG_
	std::cout << "-----------------------\n";
	std::cout << "Введите одну из операций: +, -, *, %" << '\n';
	std::string consol_sign;
	getline(std::cin, consol_sign, '\n');
	sign = consol_sign[0];



	Polynom userPl;

	if (sign == '%')
	{
		std::cout << "Введите модуль:\n";
		getline(std::cin, consol_sign, '\n');
		int mods = (int)consol_sign[0] - 48;

		std::cout << "-----------------------\n";
		std::string user_consol_polynom;
		std::cout << "Введите скалярную величину или полином: " << '\n';
		getline(std::cin, user_consol_polynom, '\n');


		userPl.writePolynom(user_consol_polynom);
		userPl.print_Equation();


		Polynom unitPl;
		Polynom remainsPl;



		pl.mod(unitPl, remainsPl, userPl, mods);

		std::cout << "Целая часть: ";
		unitPl.print_Equation();
		std::cout << "Остаток: ";
		remainsPl.print_Equation();

	}

	else
	{

		std::cout << "-----------------------\n";
		std::string user_consol_polynom;
		std::cout << "Введите скалярную величину или полином: " << '\n';
		getline(std::cin, user_consol_polynom, '\n');


		userPl.writePolynom(user_consol_polynom);
		userPl.print_Equation();


		if (!pl.logic_mathematical_operations(sign, user_consol_polynom))
		{
			std::cout << "Не корректные данные\n";
			system("pause");
			return 0;
		}


		std::cout << "-----------------------\n";
		std::cout << "Ответ: ";
		pl.print_Equation();
	}






#endif


#ifdef _DEBUG_
	std::cout << "-----------------------\n";
	std::cout << &pl << " = ";
	pl.print_Equation();
	// Копирывание
	Polynom pl1(pl);
	std::cout << &pl1 << " = ";
	pl1.print_Equation();
	// Присваивание
	Polynom pl2;
	pl2 = pl;
	std::cout << &pl2 << " = ";
	pl2.print_Equation();
	std::cout << "-----------------------\n";
#endif


#ifdef _DEBUG_
	// Арифметика




	// Сложение полиномов +
	std::cout << "-----------------------\n";
	pl.~Polynom();
	pl2.~Polynom();
	pl.writePolynom("1 -1 1 0");
	pl2.writePolynom("3 -3 3");
	pl.print_Equation();
	pl2.print_Equation();
	pl.add(pl2);
	std::cout << "Сумма: ";
	pl.print_Equation();
	std::cout << "-----------------------\n";
	// Умножение на скаляр
	std::cout << "-----------------------\n";
	pl.~Polynom();
	pl2.~Polynom();
	pl.writePolynom("1 2 3");
	pl2.writePolynom("3 2 1");
	pl.print_Equation();
	pl2.print_Equation();
	pl.multiplication(pl2);

	std::cout << "Умножение: ";
	pl.print_Equation();
	std::cout << "-----------------------\n";
	// Вычитание полиномов
	std::cout << "-----------------------\n";
	pl1.print_Equation();
	pl2.print_Equation();
	pl1.subtract(pl2);
	std::cout << "Разности: ";
	pl1.print_Equation();
	std::cout << "-----------------------\n";

	// Модуль полиномов
	std::cout << "-----------------------\n";


	pl.~Polynom();
	pl2.~Polynom();

	pl.writePolynom("3 5 32 4 44 2 4");
	pl2.writePolynom("1 2 2 3");

	pl.print_Equation();
	pl2.print_Equation();


	Polynom pl5;
	Polynom pl6;
	unsigned int modal = 0;
	pl.mod(pl5, pl6, pl2, modal);
	std::cout << "Модуль: " << modal << "\n";
	std::cout << "Целая часть: ";
	pl5.print_Equation();
	std::cout << "Остаток: ";
	pl6.print_Equation();
	std::cout << "-----------------------\n";


	// Установка нового полинома
	std::cout << "-----------------------\n";
	pl.print_Equation();
	int testarr[5] = { 5,4,3,2,1 };
	pl.setVariables(testarr, 5);
	pl.print_Equation();
	std::cout << "-----------------------\n";

#endif

	std::cout << "-----------------------\n";

	system("pause");
	return 1;
}

