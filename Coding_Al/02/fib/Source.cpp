
#include <iostream>
#include <cstdio>
using namespace std;


/*
   25.10.2020 1:00 - 25.10.2020 3:00
   Общее время выполнения работы 2 часа

   Работа выполнена студентом 3 курса ИИТО ИСиТ
   Семыкиным В.В.

   В данной работе реализованы алгоритмы по переводу из десятичной системы счисления в  систему счисления Фибоначчи, а также обратынй алгоритм.
   Данные алгоритмы сопровождаются тестами.
   Реализована функция, проверяющая правильность записанного числа в С.С. Фибоначчи
*/


//Сигнатуры функций
unsigned long long int to_fib(unsigned long long int);
unsigned long long int fib_to_dec(unsigned long long int);

//Сигнатуры тестов
void test_to_fib();
void test_fib_to_dec();
void test_loop();


int main()
{
	cout << "Test function dec => fib\n\n";
	test_to_fib();
	cout << "\n-------------------------------------------------------------------\n";
	cout << "Test function fib => dec\n\n";
	test_fib_to_dec();
	cout << "\n-------------------------------------------------------------------\n";
	cout << "Test function loop (number == fib_to_dec(to_fib(number)))\n\n";
	test_loop();
	
	return 0;
}

// Перевод из 10-ичной системы счисления в Фибоначчи 
unsigned long long int to_fib(unsigned long long int number)
{
	/*
	Данная функция принимает на вход десятичное число и перевод его в систему счисления Фибоначчи 
	Результат выдается в виде десятичного числа, где цифры в разрядах - есть подряд идущие цифры записи числа в системе счисления Фибоначчи
	*/
	unsigned long long int fib_number = 0; 
	while (number != 0)
	{
		unsigned long long int a = 1; //предыдущее число Фибоначчи
		unsigned long long int b = 1; //нынешнее число Фибоначчи
		unsigned long long int j = 1; //Счетчик разрядов нынешнего числа Фибоначчи
		while (b <= number)
		{
			a = a ^ b;                //Замена переменных без дополнительной переменной
			b = b ^ a;
			a = a ^ b;
			b += a;
			j *= 10;
		}
		//После цикла мы имеем актуальное число Фибоначчи для вычитания
		number -= a;
		fib_number += j == 1 ? 1 : j / 10; //использование тернарнорного оператора вместо конструкции if else
										   //Эквивалентно варианту if (j == 1) {fib_number += 1} else {fib_number += j / 10}
										   // j / 10 - это "разворачивание" счетчика разрядов, позволяет поставить 1 в нужном месте
	}
	return fib_number;
}

/*
Согласно теореме Цекендорфа мы не можем использовать в записи числа в С.С. Фибоначии две подряд идущие '1'
Также в записи числа в С.С. Фибоначчи не могут содержать цифры, отличные от '0' и '1'
Добавим функцию, проверяющую данные условия
*/
bool correct_fib_number(unsigned long long fib_number)
{
	int last_dig = -1; //невозможный случай
	while (fib_number)
	{
		if (
			(fib_number % 10 != 0 && fib_number % 10 != 1) //проверка цифр числа
			||
			(last_dig == 1 && fib_number % 10 == last_dig) //проверка наличия рядом двух единиц
			)
		{
			return false;
		}

		else
		{
			last_dig = fib_number % 10;
			fib_number /= 10;
		}
	}
	return true;
}

// Перевод из системы счисления Фибоначчи в десятичную
unsigned long long int fib_to_dec(unsigned long long int fib_number)
{
	/*
	Данная функция принимает на вход число в С.С. Фибоначчи (записанное в десятичной форме записи)
	Т.Е. к примеру ваше число в системе счисления Фибоначчи имеет вид 1000101, значит в данную функцию оно передается как 1000101
	и перевод его в десятичное число, возвращая число в десятичной С.С.
	*/

	if (correct_fib_number(fib_number))
	{
		unsigned long int dec_number = 0;
		unsigned long long int a = 1;  //предыдущее число Фибоначчи (Служащее счетчиком разряда)
		unsigned long long int b = 1;  //нынешнее число Фибоначчи 
		while (fib_number != 0)
		{
			dec_number += (fib_number % 10) * b;
			a = a ^ b;                //Замена переменных без дополнительной переменной
			b = b ^ a;
			a = a ^ b;
			b += a;
			fib_number /= 10;
		}
		return dec_number;
	}

		cout << "Uncorrect fib_number, try again\n";
		return -1;
}

void test_to_fib()
{
	if (to_fib(37) == 10000100)
	{
		cout << "to_fib(37) == 10000100 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fib(25) == 1000101)
	{
		cout << "to_fib(25) == 1000101 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fib(0) == 0)
	{
		cout << "to_fib(0) == 0 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fib(1) == 1)
	{
		cout << "to_fib(1) == 1 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fib(33) == 1010101)
	{
		cout << "to_fib(33) == 1010101 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_fib(47) == 10100000)
	{
		cout << "to_fib(47) == 10100000 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}
}

void test_fib_to_dec()
{
	if (fib_to_dec(11000100) == -1)
	{
		cout << "fib_to_dec(11000100) ==  Uncorrect fib_number, try again - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(20100100) == -1)
	{
		cout << "fib_to_dec(20100100) ==  Uncorrect fib_number, try again - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(10000100) == 37)
	{
		cout << "fib_to_dec(10000100) == 37 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(1000101) == 25)
	{
		cout << "fib_to_dec(1000101) == 25 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(0) == 0)
	{
		cout << "fib_to_dec(0) == 0 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(1) == 1)
	{
		cout << "fib_to_dec(1) == 1 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(1010101) == 33)
	{
		cout << "fib_to_dec(1010101) == 33 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (fib_to_dec(10100000) == 47)
	{
		cout << "fib_to_dec(10100000) == 47 - TRUE\n";
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
		if (i == fib_to_dec(to_fib(i)))
		{
			printf ("%d == fib_to_dec(to_fib(%d)) - TRUE\n", i, i);
		}
		else
		{
			cout << "FALSE\n";
		}
	}
}