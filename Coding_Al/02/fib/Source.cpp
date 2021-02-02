
#include <iostream>
#include <cstdio>
using namespace std;


/*
   25.10.2020 1:00 - 25.10.2020 3:00
   ����� ����� ���������� ������ 2 ����

   ������ ��������� ��������� 3 ����� ���� ����
   ��������� �.�.

   � ������ ������ ����������� ��������� �� �������� �� ���������� ������� ��������� �  ������� ��������� ���������, � ����� �������� ��������.
   ������ ��������� �������������� �������.
   ����������� �������, ����������� ������������ ����������� ����� � �.�. ���������
*/


//��������� �������
unsigned long long int to_fib(unsigned long long int);
unsigned long long int fib_to_dec(unsigned long long int);

//��������� ������
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

// ������� �� 10-����� ������� ��������� � ��������� 
unsigned long long int to_fib(unsigned long long int number)
{
	/*
	������ ������� ��������� �� ���� ���������� ����� � ������� ��� � ������� ��������� ��������� 
	��������� �������� � ���� ����������� �����, ��� ����� � �������� - ���� ������ ������ ����� ������ ����� � ������� ��������� ���������
	*/
	unsigned long long int fib_number = 0; 
	while (number != 0)
	{
		unsigned long long int a = 1; //���������� ����� ���������
		unsigned long long int b = 1; //�������� ����� ���������
		unsigned long long int j = 1; //������� �������� ��������� ����� ���������
		while (b <= number)
		{
			a = a ^ b;                //������ ���������� ��� �������������� ����������
			b = b ^ a;
			a = a ^ b;
			b += a;
			j *= 10;
		}
		//����� ����� �� ����� ���������� ����� ��������� ��� ���������
		number -= a;
		fib_number += j == 1 ? 1 : j / 10; //������������� ������������� ��������� ������ ����������� if else
										   //������������ �������� if (j == 1) {fib_number += 1} else {fib_number += j / 10}
										   // j / 10 - ��� "��������������" �������� ��������, ��������� ��������� 1 � ������ �����
	}
	return fib_number;
}

/*
�������� ������� ���������� �� �� ����� ������������ � ������ ����� � �.�. ��������� ��� ������ ������ '1'
����� � ������ ����� � �.�. ��������� �� ����� ��������� �����, �������� �� '0' � '1'
������� �������, ����������� ������ �������
*/
bool correct_fib_number(unsigned long long fib_number)
{
	int last_dig = -1; //����������� ������
	while (fib_number)
	{
		if (
			(fib_number % 10 != 0 && fib_number % 10 != 1) //�������� ���� �����
			||
			(last_dig == 1 && fib_number % 10 == last_dig) //�������� ������� ����� ���� ������
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

// ������� �� ������� ��������� ��������� � ����������
unsigned long long int fib_to_dec(unsigned long long int fib_number)
{
	/*
	������ ������� ��������� �� ���� ����� � �.�. ��������� (���������� � ���������� ����� ������)
	�.�. � ������� ���� ����� � ������� ��������� ��������� ����� ��� 1000101, ������ � ������ ������� ��� ���������� ��� 1000101
	� ������� ��� � ���������� �����, ��������� ����� � ���������� �.�.
	*/

	if (correct_fib_number(fib_number))
	{
		unsigned long int dec_number = 0;
		unsigned long long int a = 1;  //���������� ����� ��������� (�������� ��������� �������)
		unsigned long long int b = 1;  //�������� ����� ��������� 
		while (fib_number != 0)
		{
			dec_number += (fib_number % 10) * b;
			a = a ^ b;                //������ ���������� ��� �������������� ����������
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