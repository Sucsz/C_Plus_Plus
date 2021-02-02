/*
����� ����� ���������� ������ ~2.75 �����
 
������ ��������� ��������� 3 ����� ���� ����
   ��������� �.�.

������ ��������� ��������� �������� ���������� ����� ��������-����, ����������� ��������� ���������, �������������.

*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// ��������� �������
vector <pair <char, double> > frequency_analysis(string);
void out_table(vector <pair<char, double> >);
void compute_q_d(vector<double>* q, vector<double>* d, vector <pair <char, double> > freq_table);
void out_vector(vector<double>);
vector <pair<char, string> > to_gilbert_moor(vector <pair <char, double> >, vector<double>);
void out_codes_table(vector<pair<char, string> >);
bool check_prefix(vector<pair<char, string> >);
pair <vector <pair<char, string> >, string> encoding_to_code(string, vector<pair<char, string> >);
pair <vector <pair<char, string> >, string> decoding_to_decode(pair <vector <pair<char, string> >, string>);
void efficiency_coefficient(string input, pair <vector <pair<char, string> >, string>);

//��������� ������
void tests_encode(); // �����������
void test_encode_1();
void test_encode_2();
void test_encode_3();
void test_encode_4();
void test_encode_5();
void tests_decode(); // �������������
void test_decode_1();
void test_decode_2();
void test_decode_3();
void test_decode_4();
void test_decode_5();

int main()
{
	system("chcp 1251");  // ��������� �� ������� ���� � �������
	system("cls");
	cout << "����� �����������:\n";
	cout << "---------------------------------------------------------------------------------------------------------";
	tests_encode();
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "\n����� �������������\n\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
	tests_decode();
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t������ ��������:\n\n"; // �������� �� ����� loop-test � ������ ��������, ����� ���������� ����������
	string input;
	cout << "������� ���������, ������� �� ������� ����������: ";
	getline(cin, input);
	vector <pair <char, double> > freq_table = frequency_analysis(input); // "�������" ������-����������� 
	cout << "\n������� ������������ ��������: \n";
	out_table(freq_table);
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	cout << "\n����� �������� q\n";
	out_vector(q);
	cout << "\n����� �������� d\n";
	out_vector(d);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d);
	cout << "\n������� ������  - ���:\n";
	out_codes_table(gilbert_m_codes);
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(input, gilbert_m_codes);
		cout << "\n�������� ���������: \n" << input << "\n\n�������������� ���������\n" << tables_code_and_code.second;
		cout << "\n\n�������� ���� � �������� ���������:\n";
		tables_code_and_decode = decoding_to_decode(tables_code_and_code);
		cout << "�������� ���������: \n" << tables_code_and_decode.second << "\n\n";
		if (tables_code_and_decode.second == input)
		{
			cout << "�������� ������ ������� � ��������������!\n\n";
		}
		else
		{
			return -2;
		}
	}
	else // ��� �� ����������
	{
		return -1;
	}
	efficiency_coefficient(input, tables_code_and_code);
	system("pause");
	return 0;
}

// ��������� ������
vector <pair <char, double> > frequency_analysis(string input)
{
	/*
	�������, ����������� ��������� ������ �������� ������. ����������� ����� ��� ����-��������, ��� ���� - �����,
	�������� - ����������� ��������� ����� � ������������ ���������.
	*/
	vector <pair <char, double> > freq_table;
	int size = input.size();
	for (int counter = 0; counter < size; counter++) //�������� �� ������� ������� � �����
	{
		//������� ���������� ����
		for (int counter2 = 0; counter2 < freq_table.size(); counter2++)
		{
			if (freq_table[counter2].first == input[counter]) // ���������� ��� � ���������� ��������� � "�������"
			{
				freq_table[counter2].second += 1.0 / input.size(); // ���� �������, ���������� �����������
				goto out_label;
			}
		}
		freq_table.push_back(pair<char, double>(input[counter], 1.0 / input.size()));
		// � ��������� ����������� ��������� goto, ������ else, ����� �� ��������� ������ ������� � ������ ���� �� ����� ��������. 
	out_label:;
	}
	return freq_table;
}

// ����� "�������" �� �����
void out_table(vector <pair <char, double> > container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "����: " << container[counter].first << "\t��������: " << container[counter].second << '\n';
	}
}

// ����������� ������������ ������ q � d
void compute_q_d(vector<double>* q, vector<double>* d, vector <pair <char, double> > freq_table)
{
	int size = freq_table.size();
	(*q).push_back(0);
	(*d).push_back(freq_table[0].second / 2);
	for (int counter = 1; counter < size; counter++)
	{
		(*q).push_back((*q)[counter - 1] + freq_table[counter-1].second);
		(*d).push_back((*q)[counter] + freq_table[counter].second / 2);
	}
}

// ����� ������� �� �����
void out_vector(vector<double> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "��������: " << container[counter] << '\n';
	}
}

// ����������� ����� ��������
vector <pair<char, string> > to_gilbert_moor(vector <pair <char, double> > freq_table, vector<double> d)
{
	// ������ ������� ����
	vector<pair<char, string> > codes;
	int size = freq_table.size();
	for (int counter = 0; counter < size; counter++) //��� ������ ������������ �����������
	{
		vector<int> code; // ��� ����� �����
		// ��������� ������������ ����� � �������� �������
		int number_char = ceil(-log2(freq_table[counter].second / 2)); // ����������� ������ ��������� �����
		for (int counter2 = 0; counter2 < number_char; counter2++)
		{
			d[counter] *= 2;
			code.push_back(floor(d[counter]));
			if (d[counter] >= 1)
			{
				d[counter]--;
			}
		}
		// ��������� � ������
		string result;
		for (int counter2 = 0; counter2 < code.size(); counter2++)
		{
			result += code[counter2] ? '1' : '0';
		}
		codes.push_back(pair<char, string>(freq_table[counter].first, result));
	}
	return codes;
}

// ����� ������� ����� �� ����� 
void out_codes_table(vector<pair<char, string> > gilbert_m)
{
	int size = gilbert_m.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "������: " << gilbert_m[counter].first << "\t���: " << gilbert_m[counter].second << '\n';
	}
}

// �������� ������������ ������������ �����
bool check_prefix(vector<pair<char, string> > codes)
{
	int size = codes.size();
	for (int counter = 0; counter < size; counter++) // ������ �� ���� �����
	{
		for (int counter2 = counter + 1; counter2 < size; counter2++) // ������ �� ���� �����, ������� ������� ����� ��������� 
		{
			bool flag = false; // ��������� ���������� �����, ���� ��� �� ������� ������ �������� �� false
			for (int counter3 = 0; (counter3 < codes[counter].second.size()) && counter3 < codes[counter2].second[counter3]; counter3++) // ������ �� ������ ������� ������������ ����� 
			{
				//�.�. � ��� ���������������� d, counter3 < codes[counter2].second[counter3] ������ ������� ��������� �� �������� �� ������� �������� �����. 
				if (codes[counter].second[counter3] != codes[counter2].second[counter3])
				{
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "\n������ ������� ����� �� �������� ����������\n";
				return false;
			}
		}
	}
	cout << "\n������ ������� ����� �������� ����������\n";
	return true;
}

// �������, ���������� �������� ���������, ��������� �������� ������� ����� � ���������, ���������� �������� ������� ����� � �������������� ���������. 
pair <vector <pair<char, string> >, string> encoding_to_code(string input, vector<pair<char, string> > gilbert_m_codes)
{
	int size = input.size();
	int size_table = gilbert_m_codes.size();
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	table_codes_and_code.first = gilbert_m_codes;
	for (int count = 0; count < size; count++) // ��� ������ ����� �������� ������
	{
		for (int count2 = 0; count2 < size_table; count2++) // ������������� ��� ������� �����, ���� �� ���������� ����������� ���
		{
			if (input[count] == gilbert_m_codes[count2].first)
			{
				table_codes_and_code.second += gilbert_m_codes[count2].second;
				break;
			}
		}
	}
	return(table_codes_and_code);
}

// �������, ������������ �������� ���������, ��������� �������� ������� ����� � ���������, ���������� �������� ������� ����� � �������������� ���������. 
pair <vector <pair<char, string> >, string> decoding_to_decode(pair <vector <pair<char, string> >, string> table_codes_and_code)
{
	int code_size = table_codes_and_code.second.size();
	int size_table = table_codes_and_code.first.size();
	pair <vector <pair<char, string> >, string> table_codes_and_decode;
	table_codes_and_decode.first = table_codes_and_code.first;
	string code;
	for (int count = 0; count < code_size; count++) // ��� ������ ����� �������� ������ ����� ����������� ������� �����, � ��������� ��� �� ����������� ������� �����, ���� �� �����
													// �� ����������� ������� �����, ��������� ��������� �����.
	{
		code += table_codes_and_code.second[count];
		for (int count2 = 0; count2 < size_table; count2++) // ������������� ��� ������� �����, ���� �� ���������� ����������� ���
		{
			if (code == table_codes_and_decode.first[count2].second)
			{
				table_codes_and_decode.second += table_codes_and_decode.first[count2].first;
				code = ""; // ���� ���������� ������� ����� �������, ��������� � ����� ������, ���������� ��� ���� ����� � �������� ���.
				break;
			}
		}
	}
	return(table_codes_and_decode);
}

// �������, ����������� ������� ������
void efficiency_coefficient(string input, pair <vector <pair<char, string> >, string> tables_code_and_code)
{
	double size_input = input.size();
	double size_code = tables_code_and_code.second.size();
	cout << "������ ��������� ��������� � ������� ������� ����������� ��� ������� ��������� ���������:\n" << size_input * 8 / size_code << "\n\n\n";
}

void tests_encode() // ������� ������������ ����� �����������
{
	test_encode_1();
	test_encode_2();
	test_encode_3();
	test_encode_4();
	test_encode_5();
}

void test_encode_1()
{
	string text = "string"; // ������ ���������, ������� ����� ������������
	string answer = "000101000110100111001110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "�������" ������-���
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // �����������
		if (tables_code_and_code.second == answer)
		{
			printf("code( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
		}
		else
		{
			cout << "\t\tFALSE\n\n";
		}
	}
}

void test_encode_2()
{
	string text = "abbbbbbccc"; // ������ ���������, ������� ����� ������������
	string answer = "00001010101010101110110110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "�������" ������-���
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // �����������
		if (tables_code_and_code.second == answer)
		{
			printf("code( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
		}
		else
		{
			cout << "\t\tFALSE\n\n";
		}
	}
}

void test_encode_3()
{
	string text = "������ � �����, ����� �����, ��� � �, ������ ����� ����� - ���� ����."; // ������ ���������, ������� ����� ������������
	string answer = "0000000100010000111110001000101001110101011110101011000000000010100000111000011110010010011101011010100111101110110000100001001010010110101001111100011011001101001110101101110001111011100101011110101011001001001110101110100100010001011001001010111011010101101011100110001011001001110000001011110010000010111001110001011101011010111101111010100101111100111010111011010101111101101101001111110100011111111110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "�������" ������-���
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // �����������
		if (tables_code_and_code.second == answer)
		{
			printf("code( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
		}
		else
		{
			cout << "\t\tFALSE\n\n";
		}
	}
}

void test_encode_4()
{
	string text = "apple"; // ������ ���������, ������� ����� ������������
	string answer = "000101101110111110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "�������" ������-���
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // �����������
		if (tables_code_and_code.second == answer)
		{
			printf("code( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
		}
		else
		{
			cout << "\t\tFALSE\n\n";
		}
	}
}

void test_encode_5()
{
	string text = "������"; // ������ ���������, ������� ����� ������������
	string answer = "0010110100111001110001"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "�������" ������-���
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // �����������
		if (tables_code_and_code.second == answer)
		{
			printf("code( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
		}
		else
		{
			cout << "\t\tFALSE\n\n";
		}
	}
}

void tests_decode() // ������� ������������ ����� �������������
{
	test_decode_1();
	test_decode_2();
	test_decode_3();
	test_decode_4();
	test_decode_5();
}

void test_decode_1()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "000101000110100111001110";
	// ���������� ���-������
	pair<char, string> code1('s', "0001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('t', "0100"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('r', "0110"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('i', "1001"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('n', "1100"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('g', "1110"); // 6
	table_codes_and_code.first.push_back(code6);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "string"; // ��� ��������� ���������� �����
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}

void test_decode_2()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "00001010101010101110110110";
	// ���������� ���-������
	pair<char, string> code1('a', "00001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('b', "01"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('c', "110"); // 3
	table_codes_and_code.first.push_back(code3);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "abbbbbbccc"; // ��� ��������� ���������� �����
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}

void test_decode_3()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "0000000100010000111110001000101001110101011110101011000000000010100000111000011110010010011101011010100111101110110000100001001010010110101001111100011011001101001110101101110001111011100101011110101011001001001110101110100100010001011001001010111011010101101011100110001011001001110000001011110010000010111001110001011101011010111101111010100101111100111010111011010101111101101101001111110100011111111110";
	// ���������� ���-������
	pair<char, string> code1('�', "00000001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('�', "00010"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('�', "00011111"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('�', "00101"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('�', "00111"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6(' ', "0101"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('�', "0111101"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('�', "10000000"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('�', "10000011"); // 9
	table_codes_and_code.first.push_back(code9);

	pair<char, string> code10('�', "10000111"); // 10
	table_codes_and_code.first.push_back(code10);

	pair<char, string> code11('�', "100100"); // 11
	table_codes_and_code.first.push_back(code11);

	pair<char, string> code12(',', "100111"); // 12
	table_codes_and_code.first.push_back(code12);

	pair<char, string> code13('�', "10101"); // 13
	table_codes_and_code.first.push_back(code13);

	pair<char, string> code14('�', "101110"); // 14
	table_codes_and_code.first.push_back(code14);

	pair<char, string> code15('�', "11000010"); // 15
	table_codes_and_code.first.push_back(code15);

	pair<char, string> code16('�', "11000110"); // 16
	table_codes_and_code.first.push_back(code16);

	pair<char, string> code17('�', "1100110"); // 17
	table_codes_and_code.first.push_back(code17);

	pair<char, string> code18('�', "1101001"); // 18
	table_codes_and_code.first.push_back(code18);

	pair<char, string> code19('�', "1101101"); // 19
	table_codes_and_code.first.push_back(code19);

	pair<char, string> code20('�', "11100000"); // 20
	table_codes_and_code.first.push_back(code20);

	pair<char, string> code21('�', "11100100"); // 21
	table_codes_and_code.first.push_back(code21);

	pair<char, string> code22('�', "11100111"); // 22
	table_codes_and_code.first.push_back(code22);

	pair<char, string> code23('�', "11101011"); // 23
	table_codes_and_code.first.push_back(code23);

	pair<char, string> code24('-', "11101111"); // 24
	table_codes_and_code.first.push_back(code24);

	pair<char, string> code25('�', "11110011"); // 25
	table_codes_and_code.first.push_back(code25);

	pair<char, string> code26('�', "11110110"); // 26
	table_codes_and_code.first.push_back(code26);

	pair<char, string> code27('�', "11111010"); // 27
	table_codes_and_code.first.push_back(code27);

	pair<char, string> code28('.', "11111110"); // 28
	table_codes_and_code.first.push_back(code28);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "������ � �����, ����� �����, ��� � �, ������ ����� ����� - ���� ����."; // ��� ��������� ���������� �����
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) \n\t\t\t\t==\n %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}

void test_decode_4()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "000101101110111110";
	// ���������� ���-������
	pair<char, string> code1('a', "0001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('p', "011"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('l', "1011"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('e', "1110"); // 4
	table_codes_and_code.first.push_back(code4);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "apple"; // ��� ��������� ���������� �����
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}

void test_decode_5()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "0010110100111001110001";
	// ���������� ���-������
	pair<char, string> code1('�', "001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('�', "0110"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('�', "1001"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('�', "1100"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('�', "1110"); // 5
	table_codes_and_code.first.push_back(code5);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "������"; // ��� ��������� ���������� �����
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}