
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;


/*
   25.10.2020 17:40 - 25.10.2020 19:10
   ����� ����� ���������� ������ 1.5 ����

   ������ ��������� ��������� 3 ����� ���� ����
   ��������� �.�.

   � ������ ������ ����������� ��������� �� �������� �� ���������� ������� ��������� � ����-�������� ������� ���������, � ����� �������� ��������.
   ������ ��������� �������������� �������.
   ����������� �������, ����������� ������������ ����������� ����� � ����-�������� ������� ���������
*/


//��������� �������
unsigned long long int to_nega2(long long int);
unsigned long long int nega2_to_dec(unsigned long long int);

//��������� ������
void test_to_nega2();
void test_nega2_to_dec();
void test_loop();

int main()
{
	cout << "Test function dec => nega2\n\n";
	test_to_nega2();
	cout << "\n-------------------------------------------------------------------\n";
	cout << "Test function nega2 => dec\n\n";
	test_nega2_to_dec();
	cout << "\n-------------------------------------------------------------------\n";
	cout << "Test function loop (number == nega2_to_dec(to_nega2(number)))\n\n";
	test_loop();
	return 0;
}

// ������� �� 10-����� ����-�������� ������� ���������  
unsigned long long int to_nega2(long long int number)
{
	/*
	������ ������� ��������� �� ���� ���������� ����� � ������� ��� � ����-�������� ������� ���������
	��������� �������� � ���� ����������� �����, ��� ����� � �������� - ���� ������ ������ ����� ������ ����� � ����-�������� ������� ��������� 
	*/
	long long int nega2_number = 0;
	int reminder;
	unsigned long long int j = 1; //������� ��������
	while (number != 0)
	{

		nega2_number += (reminder = abs(number % (-2)))  * j; //abs, ����� ������� ��� ������ 0 ��� 1
		j *= 10;
		number = (number - reminder) / (-2);
		/*
		� ��� ��� �� ������������ � ��������, ����������� ��������� intel � ���� ����������.
		C++ - ������������ ��������������� ����, �� ����� ����������� � �����������.
		� ������ ���������� �����, ������ 15 � � ������ �������� �����������. 
		� �������� ������� �� ���������� ��������� ����� � ��������� ���������� � ������ ���������
		����� ------------ ����� �������� ������� � �������� ��������� ���������
		{
			number = 15
			nega2_number = 0 
			j = 1
			-------------------------------
			reminder = abs(15 % (-2)) = 1
			nega2_number = 0 + 1 * 1= 1
			j = 1 * 10 = 10
			� ������ ����������� number ����� ���������� ��������� ������� number /= (-2)
			number = (-7)
			������� �� ������� + ������� ������ * �� ��������� ������ ������ ���� �����, ��������
			15 = (-7) * (-2) + 1 - True
			��������� � ��������� ���������
		}
		{
			number = (-7)
			nega2_number = 1
			j = 10
			reminder = 1
			-------------------------------
			reminder = abs((-7) % (-2)) = 1
			nega2_number = 1 + 1* 10 = 11
			j = 10 * 10 = 100
			number = 3
			��������
			-7 = 3 * (-2) + 1 - False
			����� ������� �� ������������ � ���������, ������� �������� ��������� �������:
			�� �����, ��� ������� ������ ������ ���� {0,1}
			������� ����� ��������� number ��������� ��������:
			number = (number - reminder) / (-2)
			(������� ������ ������� ������ �������, ���������� �� ����������� ����, ������ ������ 3 ���������� x, ��� � - ����������� ����� �����)
			� ������ ������� number = 4, ��� ��������� � �������������� �������������� ������ ���������, � �� 3�, ��� ��� ����������� � c++
		}
		*/
	}
	return nega2_number;
}

/*
� ������ ����� � ����-�������� �.�. �� ����� ��������� �����, �������� �� '0' � '1'
������� �������, ����������� ������ �������
*/
bool correct_nega2_number(unsigned long long nega2_number)
{
	int last_dig = -1; //����������� ������
	while (nega2_number)
	{
		if (nega2_number % 10 != 0 && nega2_number % 10 != 1) //�������� ���� �����
		{
			return false;
		}

		else
		{
			last_dig = nega2_number % 10;
			nega2_number /= 10;
		}
	}
	return true;
}

// ������� �� ����-�������� ������� ��������� � ����������
unsigned long long int nega2_to_dec(unsigned long long int nega2_number)
{
	/*
	������ ������� ��������� �� ���� ����� � ����-�������� �.�. (���������� � ���������� ����� ������)
	�.�. � ������� ���� ����� � ����-�������� ������� ��������� ����� ��� 10011, ������ � ������ ������� ��� ���������� ��� 10011
	� ������� ��� � ���������� �����, ��������� ����� � ���������� �.�.
	*/
	if (correct_nega2_number(nega2_number))
	{
		long long int dec_number = 0;
		unsigned long long int i = 0; //������� '-2'
		while (nega2_number != 0)
		{
			dec_number += (nega2_number % 10) * pow((-2), i++);
			nega2_number /= 10;
		}
		return dec_number;
	}

	cout << "Uncorrect nega2_number, try again\n";
	return -1;
}

void test_to_nega2()
{
	if (to_nega2(-15) == 110001)
	{
		cout << "to_nega2(-15) == 110001 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_nega2(15) == 10011)
	{
		cout << "to_nega2(25) == 1000101 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_nega2(0) == 0)
	{
		cout << "to_nega2(0) == 0 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_nega2(1) == 1)
	{
		cout << "to_nega2(1) == 1 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_nega2(10) == 11110)
	{
		cout << "to_nega2(10) == 11110 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (to_nega2(3) == 111)
	{
		cout << "to_nega2(3) == 111 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}
}

void test_nega2_to_dec()
{
	if (nega2_to_dec(210001) == -1)
	{
		cout << "nega2_to_dec(11000100) ==  Uncorrect nega2_number, try again - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(20100100) == -1)
	{
		cout << "nega2_to_dec(20100100) ==  Uncorrect nega2_number, try again - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(10011) == 15)
	{
		cout << "nega2_to_dec(10000100) == 37 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(11110) == 10)
	{
		cout << "nega2_to_dec(1000101) == 25 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(0) == 0)
	{
		cout << "nega2_to_dec(0) == 0 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(1) == 1)
	{
		cout << "nega2_to_dec(1) == 1 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(111) == 3)
	{
		cout << "nega2_to_dec(111) == 3 - TRUE\n";
	}
	else
	{
		cout << "FALSE\n";
	}

	if (nega2_to_dec(1110110) == 50)
	{
		cout << "nega2_to_dec(1110110) == 50 - TRUE\n";
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
		if (i == nega2_to_dec(to_nega2(i)))
		{
			printf("%d == nega2_to_dec(to_nega2(%d)) - TRUE\n", i, i);
		}
		else
		{
			cout << "FALSE\n";
		}
	}
}