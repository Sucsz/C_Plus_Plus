/*
����� ����� ���������� ������ ~4 ����
 
������ ��������� ��������� 3 ����� ���� ����
   ��������� �.�.

������ ��������� ��������� �������� ���������� ����� �������

*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

// ��������� �������
vector<int> get_lengths_code(vector<double>*);
void out_vector(vector<double>);
void out_vector_s(vector<string>);
vector<string> to_2(vector<double>);
vector<string> to_sh(vector<string> q, vector<int>);
bool check_prefix(vector<string>);
bool check_2(vector<string>);
//��������� ������
/*
������ ��������� ������� �������� ���������� ���� �������� ����. ��������  if (is_prefix && is_2) return 0; � ������ main() �������� ������ ���� ��
������� ������������ � ����������, ������� ����� �������, ��� ��� ������������� ��������� ������������ ��������� ��� ��������. 
*/

int main()
{
	system("chcp 1251");  // ��������� �� ������� ���� � �������
	system("cls");
	vector<double>  q; // ����� �������� q
	vector<int> lengths_code = get_lengths_code(&q);
	cout << "\n����� ������������ �������� (2^(-l[i]), ��� l[i] - ������ i-�� ����\n";
	out_vector(q);
	vector<string> imperfect_sh_codes = to_2(q); // ������ ���� ������������, ��� �� �� ������� ������, ����� ������ ������ 0100 �� ����� ������ 0.1
	cout << "\n����� ������������� �����\n";
	out_vector_s(imperfect_sh_codes);
	vector<string> sh_codes = to_sh(imperfect_sh_codes, lengths_code);
	cout << "\n����� �������� ���������� �����\n";
	out_vector_s(sh_codes);
	bool is_prefix = check_prefix(sh_codes);
	bool is_2 = check_2(sh_codes);
	if (is_prefix && is_2)
	{
		system("pause");
		return 0;
	}
	return(-5);
}
// �������, ����������� ������������ ������ ����� ������� ����. ����� ��������� ��������� �������� �� ������������ ������ ����.
// "����������" ��� ��������(���� �������� ����� ���������) ����� ���� � ����� �������� q
vector<int> get_lengths_code(vector<double>*  q)
{
	(*q).push_back(0);
	int count_codes;
	cout << "������� ���������� ������� ����:\n";
	cin >> count_codes;
	if (count_codes < 1)
	{
		cout << "������� �������� ����������\n";
		exit(-1);
	}
	vector<int> lengths_codes;
	int length_code;
	int current_max_length = -1; // �������������� "�����������" ���������, ����� �������� ����� �� ��������� �� �������� ����� ������� ����
	double kraft_condition = 0;
	for (int counter = 1; counter <= count_codes; counter++)
	{
		printf("������� ����� %d-�� ����:\n", counter);
		cin >> length_code;
		if (length_code < 1)
		{
			cout << "������� �������� �����\n";
			exit(-2);
		}
		if (current_max_length > length_code)
		{
			cout << "�� ������������� ������� l1 <= l2 <= l3..., ��� l1,l2,l3... - ����� �����\n";
			exit(-3);
		}
		current_max_length = length_code;
		double current_denominator = pow(2, -length_code);
		kraft_condition += current_denominator;
		(*q).push_back((*q)[counter - 1] + current_denominator);
		if (kraft_condition > 1)
		{
			cout << "�� ������������� ������� ����������� ������\n";
			exit(-4);
		}
		lengths_codes.push_back(length_code);
	}
	(*q).pop_back(); // ��� ��� � ������ �� ��������� 0, �������� �������� n-1 �����, ��� n-���-�� �����, �� ���� ��������� n �����, ��� ��� ��� ������
					 // ��� ������ ������, ������� ������ ������ ��������� n+1 ���
	return lengths_codes;
}

// ����� ������� �� ����� � ����� double
void out_vector(vector<double> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "��������: " << container[counter] << '\n';
	}
}
// ����� ������� �� ����� c ����� string
void out_vector_s(vector<string> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "��������: " << container[counter] << '\n';
	}
}

// ������� ������� ����� �� ���������� ������� ��������� � ��������
vector<string> to_2(vector<double> q)
{
	vector<string> codes;
	codes.push_back("0");
	int size = q.size();
	for (int counter = 1; counter < size; counter++) // ��� ������� ����������� �����, ������� �� �������, �.�. ������ 0
	{
		vector<int> code;
		while (q[counter] != 1) // ��� ���������, ������ ��� q - ������������� ������� ������
		{
			q[counter] *= 2;
			code.push_back(floor(q[counter]));
			if (q[counter] > 1)
			{
				q[counter]--;
			}
		}
		// ��������� � ������
		string result;
		for (int counter2 = 0; counter2 < code.size(); counter2++)
		{
			result += code[counter2] ? '1' : '0';
		}
		codes.push_back(result);
	}
	return codes;
}

// �������, ���������� ���� �������
vector<string> to_sh(vector<string> q, vector<int> lengths)
{
	/*
	����������� �����, ������� ��������� ����������� ���������� ����� �� ����������� ����� ����.
	*/
	vector<string> sh_codes;
	int size = lengths.size(); // � ������ ������ ������� q � lengths ���������
	for (int counter = 0; counter < size; counter++)
	{
		string code = q[counter];
		while (code.size() < lengths[counter])
		{
			code += "0";
		}
		sh_codes.push_back(code);
	}
	return sh_codes;
}

// �������, ����������� ������������ �����
bool check_prefix(vector<string> codes)
{
	int size = codes.size();
	for (int counter = 0; counter < size; counter++) // ������ �� ���� �����
	{
		for (int counter2 = counter + 1; counter2 < size; counter2++) // ������ �� ���� �����, ������� ������� ����� ��������� 
		{
			bool flag = false; // ��������� ���������� �����, ���� ��� �e ������� ������ �������� �� false
			for (int counter3 = 0; counter3 < codes[counter].size(); counter3++) // ������ �� ������ ������� ������������ ����� 
			{
				/*
				����� �� ��������� �������� ������ �� ������� �������-����, �� ���������� ������ ����������� �� ����������
				*/
				if (codes[counter] != codes[counter2])
				{
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "\n������ ���� �� �������� �����������\n";
				return false;
			}
		}
	}
	cout << "\n������ ���� �������� �����������\n";
	return true;
} // �� ����� �� ��������� ������������ ������������ ������, �� ������� ��� � ����� ��������
bool check_2(vector<string> codes)
{
	int size = codes.size();
	for (int counter = 0; counter < size; counter ++) // ��� ������� ����
		for (int counter2 = 0; counter2 < codes[counter].size(); counter2++) // ��� ������� ������� ����
		{
			if ((codes[counter][counter2] != '1') && (codes[counter][counter2] != '0'))
			{
				cout << "\n������ ���� �� �������� ���������\n";
				return false;
			}
		}
	cout << "\n������ ���� �������� ���������\n";
	return true;
}