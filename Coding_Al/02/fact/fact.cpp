
#include <iostream>
#include <cstdio>
using namespace std;


/*
   24.10.2020 17:10 - 24.10.2020 18:12
   Общее время выполнения работы 1.0(3) часа

   Работа выполнена студентом 3 курса ИИТО ИСиТ 
   Семыкиным В.В.
   
   В данной работе реализованы алгоритмы по переводу из десятичной системы счисления в факториальную, а также обратынй алгоритм.
   Данные алгоритмы сопровождаются тестами.
*/


//Сигнатуры функций
unsigned long int to_fact(unsigned long int);
unsigned long int fact_to_dec(unsigned long int);

//Сигнатуры тестов
void test_to_fact();
void test_fact_to_dec();
void test_loop();

int main()
{
	cout << "Test function dec => fact\n\n";
	test_to_fact();
	cout << "\n-------------------------------------------------------------------\n";
	cout << "Test function fact => dec\n\n";
	test_fact_to_dec();
	cout << "\n-------------------------------------------------------------------\n";
	cout << "Test function loop (number == fact_to_dec(to_fact(number)))\n\n";
	test_loop();

	return 0;
}

// Перевод из 10-ичной системы счисления в факториальную
unsigned long int to_fact (unsigned long int number)
{
	/*
	Данная функция принимает на вход десятичное число и перевод его в факториальную систему счисления
	Результат выдается в виде десятичного числа, где цифры в разрядах - есть подряд идущие цифры записи числа в фаакториальной системе счисления
	*/
	unsigned int i = 2; //Счетчик делителя числа
	unsigned long int fact_number = 0 ;
	unsigned long int j = 1; //Счетчик разрядов
	while (number != 0)
	{
		fact_number += (number % i) * j;
		number /= i++;
		j *= 10;
	}
		return fact_number;	
}

// Перевод из факториальной системы счисления в десятичную
unsigned long int fact_to_dec(unsigned long int fact_number)
{
	/*
	Данная функция принимает на вход факториальное число (записанное в десятичной форме записи)
	Т.Е. к примеру ваше число в факториальной системе счисления имеет вид 2121, значит в данную функцию оно передается как 2121
	и перевод его в десятичное число, возвращая число в десятичной С.С.
	*/
	unsigned int i = 1; //Счетчик разряда факториальной С.С.
	unsigned long int dec_number = 0;
	int fact_i = 1;
	while (fact_number != 0)
	{
		dec_number += (fact_number % 10) * (fact_i *= i++);
		fact_number /= 10;
	}
	return dec_number;
}

void test_to_fact()
{
	if (to_fact(59) == 2121)
	{
		cout << "to_fact(59) == 2121 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fact(45) == 1311)
	{
		cout << "to_fact(45) == 1311 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fact(0) == 0)
	{
		cout << "to_fact(0) == 0 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fact(1) == 1)
	{
		cout << "to_fact(1) == 1 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fact(10) == 120)
	{
		cout << "to_fact(10) == 120 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fact(100321) == 23620001)
	{
		cout << "to_fact(100321) == 23620001 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}
}

void test_fact_to_dec()
{
	if (fact_to_dec(2121) == 59)
	{
		cout << "fact_to_dect(2121) == 59 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fact_to_dec(1311) == 45)
	{
		cout << "fact_to_dec(1311) == 45 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fact_to_dec(0) == 0)
	{
		cout << "fact_to_dec(0) == 0 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fact_to_dec(1) == 1)
	{
		cout << "fact_to_dec(1) == 1 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fact_to_dec(120) == 10)
	{
		cout << "fact_to_dec(120) == 10 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fact_to_dec(23620001) == 100321)
	{
		cout << "fact_to_dec(23620001) == 100321 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}
}

void test_loop()
{
	int min = 0;
	int max = 100;
	for (int i = min; i <= max; i++)
	{
		if (i == fact_to_dec(to_fact(i)))
		{
			printf("%d == fact_to_dec(to_fact(%d)) - TRUE\n", i, i);
		}

		else
		{
			cout << "FALSE\n";
		}
	}
}

