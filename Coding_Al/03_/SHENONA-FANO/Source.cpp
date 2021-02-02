/*
����� ����� ���������� ������ ~10 �����
 
������ ��������� ��������� 3 ����� ���� ����
   ��������� �.�.

������ ��������� ��������� �������� ���������� ����� �������-����, ����������� ��������� ���������, �������������.

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
vector <pair <char, double> > sort_vector_desc(vector <pair <char, double> >);
vector<double> sum_frequencies(vector <pair <char, double> >);
void out_vector(vector<double>); 
vector <pair <char, string> > to_sh_f(vector <pair <char, double> >, vector<double>);
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
	cout << "\n������������ ������� ������������ ��������: \n";
	out_table(freq_table);
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table);
	cout << "\n��������������� �� �������� �������: \n";
	out_table(freq_desc);
	vector<double> sum_freq = sum_frequencies(freq_desc);
	cout << "\n������������ �����������: \n";
	out_vector(sum_freq);
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq);
	cout << "\n������� ������  - ���: \n";
	out_codes_table(sh_f_codes);
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(input, sh_f_codes);
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

	for (int counter = 0; counter < input.size(); counter++) //�������� �� ������� ������� � �����
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
		cout << "����: " << container[counter].first << "\t��������: " << container[counter].second <<'\n';
	}
}

//���������� ������� �� �������� ������
vector <pair <char, double> > sort_vector_desc(vector <pair <char, double> > freq_table)
{
	int size = freq_table.size();
	pair<char, double> tmp;
	for (int counter = 0; counter < size - 1; counter++)
	{
		for (int counter2 = 0; counter2 < size - counter - 1; counter2++)
		{
			if (freq_table[counter2].second < freq_table[counter2 + 1].second)
			{
				tmp = freq_table[counter2];
				freq_table[counter2] = freq_table[counter2 + 1];
				freq_table[counter2 + 1] = tmp;
			}
		}
	}
	return freq_table;
}

//����������� ������������ ���� ������ q
vector<double> sum_frequencies(vector <pair <char, double> > freq_table)
{
	vector<double> sum_freq;
	sum_freq.push_back(0);
	int size = freq_table.size();
	for (int counter = 1; counter <= size; counter++)
	{
		sum_freq.push_back(sum_freq[counter - 1] + freq_table[counter - 1].second);
	}
	return sum_freq;
}

// ����� ������� �� �����
void out_vector(vector<double> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "��������: " << container[counter]<< '\n';
	}
}


// ����������� ����� ��������
vector <pair<char, string> > to_sh_f(vector <pair <char, double> > freq_table, vector<double> sum_freq)
{
	// ������ ������� ����
	vector<pair<char, string> > codes;
	int size = freq_table.size();
	for (int counter = 0; counter < size; counter++) //��� ������ ������������ �����������
	{
		vector<int> code; // ��� ����� �����
		// ��������� ������������ ����� � �������� �������
		int number_char = ceil(-log2(freq_table[counter].second)); // ����������� ������ ��������� �����
		for (int counter2 = 0; counter2 < number_char; counter2++)
		{
			sum_freq[counter] *= 2;
			code.push_back(floor(sum_freq[counter]));
			if (sum_freq[counter] >= 1)
			{
				sum_freq[counter]--;
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
void out_codes_table(vector<pair<char, string> > shf)
{
	int size = shf.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "������: " << shf[counter].first << "\t���: " << shf[counter].second << '\n';
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
			for (int counter3 = 0; counter3 < codes[counter].second.size(); counter3++) // ������ �� ������ ������� ������������ ����� 
			{
				/*
				����� �� ��������� �������� ������ �� ������� �������-����, �� ���������� ���������� �� ����������
				*/
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
pair <vector <pair<char, string> >, string> encoding_to_code(string input, vector<pair<char, string> > sh_f_codes)
{
	int size = input.size();
	int size_table = sh_f_codes.size();
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	table_codes_and_code.first = sh_f_codes;
	for (int count = 0; count < size; count++) // ��� ������ ����� �������� ������
	{
		for (int count2 = 0; count2 < size_table; count2++) // ������������� ��� ������� �����, ���� �� ���������� ����������� ���
		{
			if (input[count] == sh_f_codes[count2].first)
			{
				table_codes_and_code.second += sh_f_codes[count2].second;
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
	string answer = "000001010100101110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // ��������������� �� �������� �������
	vector<double> sum_freq = sum_frequencies(freq_desc); // ������������ �����������
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //������� ������  - ���: 
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, sh_f_codes);
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
	string text = "���_�������-����"; // ������ ���������, ������� ����� ������������
	string answer = "100101010101011110011010000010000111110111101100010"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // ��������������� �� �������� �������
	vector<double> sum_freq = sum_frequencies(freq_desc); // ������������ �����������
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //������� ������  - ���: 
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, sh_f_codes);
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
	string answer = "1100010001111001000011010001010001010010001100110001111001111101001100001001000001100101100111101011001100001000110010111011011010111001000010011010110011000101001000100001001000010110100110100100000110101111000011010101101001000011011110001110001001111100110011111010000011101100000100111100001101011110001111010101101111110001011111110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // ��������������� �� �������� �������
	vector<double> sum_freq = sum_frequencies(freq_desc); // ������������ �����������
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //������� ������  - ���: 
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, sh_f_codes);
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
	string text = "abcdefghijklmnopqrstuvwxyz"; // ������ ���������, ������� ����� ������������
	string answer = "0000000001000100001100100001100011101000010010101101100011010111001111100011001010011101001011010111110001100111011111001110111110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // ��������������� �� �������� �������
	vector<double> sum_freq = sum_frequencies(freq_desc); // ������������ �����������
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //������� ������  - ���: 
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, sh_f_codes);
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
	string text = "cogito ergo sum"; // ������ ���������, ������� ����� ������������
	string answer = "01110000011000100100001010101011001000010110011011110"; // ��� ��������� ���������� �����
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "�������" ������-����������� 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // ��������������� �� �������� �������
	vector<double> sum_freq = sum_frequencies(freq_desc); // ������������ �����������
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //������� ������  - ���: 
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, sh_f_codes);
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
	table_codes_and_code.second = "100101010101011110011010000010000111110111101100010";
	// ���������� ���-������
	pair<char, string> code1('�', "00"); // 1
	table_codes_and_code.first.push_back(code1);
	
	pair<char, string> code2('�', "010"); // 2
	table_codes_and_code.first.push_back(code2);
	
	pair<char, string> code3('�', "011"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('�', "1001"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('�', "1010"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('_', "1011"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('�', "1100"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('�', "1101"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('-', "1110"); // 9
	table_codes_and_code.first.push_back(code9);

	pair<char, string> code10('�', "1111"); // 10
	table_codes_and_code.first.push_back(code10);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "���_�������-����"; // ��� ��������� ���������� �����
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
	table_codes_and_code.second = "000001010100101110";
	// ���������� ���-������
	pair<char, string> code1('s', "000"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('t', "001"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('r', "010"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('i', "100"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('n', "101"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('g', "110"); // 6
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
void test_decode_3()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "0110000100110";
	// ���������� ���-������
	pair<char, string> code1('p', "00"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('a', "011"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('l', "100"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('e', "110"); // 4
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
void test_decode_4()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// ������������ ���������
	table_codes_and_code.second = "000000010011010101111000101011001110";
	// ���������� ���-������
	pair<char, string> code1('�', "0000"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('�', "0001"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('�', "0011"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('�', "0101"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('�', "0111"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('�', "1000"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('�', "1010"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('�', "1100"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('�', "1110"); // 9
	table_codes_and_code.first.push_back(code9);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "��������"; // ��� ��������� ���������� �����
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
	table_codes_and_code.second = "1101010110010001101100110000010001110010010001000100101001011101000111100000101001010001101100100001011001000111111100";
	// ���������� ���-������
	pair<char, string> code1(' ', "000"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('�', "001"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('�', "010"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('�', "1000"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('�', "1001"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('�', "1011"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('�', "1100"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('�', "11010"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('�', "11011"); // 9
	table_codes_and_code.first.push_back(code9);

	pair<char, string> code10('�', "11100"); // 10
	table_codes_and_code.first.push_back(code10);

	pair<char, string> code11('�', "11101"); // 11
	table_codes_and_code.first.push_back(code11);

	pair<char, string> code12('�', "11110"); // 12
	table_codes_and_code.first.push_back(code12);

	pair<char, string> code13('�', "11111"); // 13
	table_codes_and_code.first.push_back(code13);

	string text = table_codes_and_code.second; // C��������, ������� ����� ������������
	string answer = "��� ���� �� ����� � ������ �����"; // ��� ��������� ���������� �����
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}