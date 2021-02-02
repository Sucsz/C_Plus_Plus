#include "header.h"

/*
����� ����� ���������� ������ ~10 �����

������ ��������� ��������� 3 ����� ���� ����
   ��������� �.�.

������ ��������� ��������� �������� ���������� ����� ��������, ����������� ��������� ���������, �������������, ���������� ������ ��������.
*/

int main()
{
	system("chcp 1251");  // ��������� �� ������� ���� � �������
	system("cls");
	cout << "����� �����������:\n";
//	system("pause");
//	tests_encode();
	cout << "����� �������������:\n";
//	system("pause");
//	tests_decode();
//	system("pause");
	cout << "\t\t\t\t\t������ ��������:\n\n"; // �������� - ��� loop-test, � ������ ��������, ����� ���������� ����������
	cout << "������� ���������, ������� �� ������� ����������: \n";
	string input;
	getline(cin, input);
	map<char, int> freq_table = frequency_analysis(input);
	cout << "\n\n������� ������-����������:\n";
	show_freq_table(freq_table);
	cout << "������� ���������� ����������:\n";
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	cout << "\n\n";
	traversal_tree(&table_codes, tree_haffman.top(), "");
	cout << "\n\n������� ������-���:\n";
	show_table_codes(table_codes);
	cout << "\n\n�������� ����������� ������:\n";
	check_kraft(table_codes);
	string code = encoding_to_code(input, table_codes);
	cout << "\n\n\n�������������� �������� ���������: \n" << code;
	string decode = decoding_to_decode(code, table_codes);
	cout << "\n\n�������������� �������������� ���������: \n" << decode;
	if (decode == input)
		cout << "\n\n�������� ������ ������� � ��������������!\n";
	cout << "\n\n";
	system("pause");
	return 0;
}
map<char, int> frequency_analysis(string input) // �������, ����������� ��������� ������ �������� ������
{
	map<char, int> freq_table;
	int size = input.size();
	for (int counter = 0; counter < size; counter++)
		freq_table[input[counter]] += 1;
	return freq_table;
}

void show_freq_table(map<char, int> freq_table)
{
	map<char, int>::iterator it;
	for (it = freq_table.begin(); it != freq_table.end(); it++)
		cout << "������: " << it->first << "\t����������: " << it->second << '\n';
	cout << "\n\n";
}

void show_table_codes(map<char, string> freq_table)
{
	map<char, string>::iterator it;
	for (it = freq_table.begin(); it != freq_table.end(); it++)
		cout << "������: " << it->first << "\t���: " << it->second << '\n';
}

priority_queue<Node*, vector<Node*>, Compare> fill_tree(map<char, int> freq_table) // ������� ��������� ������ ��������
{
	priority_queue<Node*, vector<Node*>, Compare> tree;
	map<char, int>::iterator it;
	for (it = freq_table.begin(); it != freq_table.end(); it++)
	{
		Node* p = new Node(it->first, it->second); // �������� ������ ���� � ��������� ����������
		tree.push(p);
		// cout << "|����������� ����� " << p->symbol << '-' << tree.top()->symbol << " ������� ����� � �������| "; �������� ����������� ���������� �������
	}
	return tree;
}
priority_queue<Node*, vector<Node*>, Compare> to_haffamn(priority_queue<Node*, vector<Node*>, Compare> tree)
{
	if (tree.size() == 1)
	{
		tree.top()->rib = 0; // ��� �������, ����� 1, ����� 0.
		return tree;
	}
	while (tree.size() != 1)
	{
		Node* son_r = tree.top();
		son_r->rib = 0;
		cout << "son_r: " << son_r->symbol << '-' << son_r->amount;
		tree.pop();
		Node* son_l = tree.top();
		son_l->rib = 1;
		cout << " son_l: " << son_l->symbol << '-' << son_l->amount;
		tree.pop();
		Node* parent = new Node(son_l, son_r);
		cout << " parent: " << parent->amount << " apply: " << parent->value << endl;
		tree.push(parent);
	}
	return tree;
}
void traversal_tree(map<char, string>* table_codes, Node* root, string code, unsigned k) // ����� �� �������, ����� � ����������� �����
{
	if (root)
	{

		if (root->rib >= 0 && root->rib <= 1) // � ����� ��� �����, ������� ���������� ������� �������, �������������� ��������� �����
			code += root->rib + '0';
		traversal_tree(table_codes, root->left, code, k + 3);
		for (unsigned i = 0; i < k; i++)
			cout << "  ";
		if (root->symbol)
		{
			(*table_codes)[root->symbol] = code;
			cout << root->amount << " (" << root->symbol << ")" << code << endl;
		}
		else
			cout << root->amount << endl;
		traversal_tree(table_codes, root->right, code, k + 3);
	}
}
void check_kraft(map<char, string> table_codes)
{
	double kraft = 0;
	map<char, string>::iterator it;
	for (it = table_codes.begin(); it != table_codes.end(); it++)
		kraft += 1 / pow(2, it->second.size());
	cout << "KRAFT = " << kraft;
	if (kraft <= 1)
		cout << "\n�������� ��������. ���������� ����� ����� �������� ����������";
	else
		cout << "\n�������� �� ��������, ���������� ����� ����� �� �������� ����������";
}
// �������, ���������� �������� ���������, ��������� ������� ����� � �������� ���������, ����������  �������������� ���������. 
string encoding_to_code(string input, map<char, string> table_codes)
{
	int size = input.size();
	string code;
	map<char, string>::iterator it;
	for (int count = 0; count < size; count++) // ��� ������ ����� �������� ������
	{
		for (it = table_codes.begin(); it != table_codes.end(); it++) // ������������� ��� ������� �����, ���� �� ���������� ����������� ���
		{
			if (input[count] == it->first)
			{
				code += it->second;
				break;
			}
		}
	}
	return code;
}
// �������, ������������ �������� ���������, ��������� ������� ����� � �������������� ���������, ���������� �������������� ���������. 
string decoding_to_decode(string code, map<char, string> table_codes)
{
	int size = code.size();
	string decode;
	string cur_code;
	map<char, string>::iterator it;
	for (int count = 0; count < size; count++) // ��� ������ ����� �������� ������ ����� ����������� ������� �����, � ��������� ��� �� ����������� ������� �����, ���� �� �����
													// �� ����������� ������� �����, ��������� ��������� �����.
	{
		cur_code += code[count];
		for (it = table_codes.begin(); it != table_codes.end(); it++) // ������������� ��� ������� �����, ���� �� ���������� ����������� ���
		{
			if (cur_code == it->second)
			{
				decode += it->first;
				cur_code = ""; // ���� ���������� ������� ����� �������, ��������� � ����� ������, ���������� ��� ���� ����� � �������� ���.
				break;
			}
		}
	}
	return decode;
}
// �������, ����������� ������� ����� �����
double avg(map <char, string> table_codes)
{
	double avg = 0;
	map<char, string>::iterator it;
	for (it = table_codes.begin(); it != table_codes.end(); it++) // ������������� ��� ������� �����, ���� �� ���������� ����������� ���
	{
		avg += it->second.size();
	}
	cout << "\n" << avg << "--" << table_codes.size() << endl;
	avg /= table_codes.size();
	return avg;
}
void test_encode_1()
{
	string input = "abc"; // ����� ����� ������, ������� ����� ������������
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 5. / 3.;
	if (avg_t == avg_h)
	{
		system("cls");
		cout << "TEST 1 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 1 FALSE\n";
	}
}
void test_encode_2()
{
	// ���� �� ������
	string input = "this_is_a_simple_example_of_huffman_encoding"; // ����� ����� ������, ������� ����� ������������
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 77. / 18.; // ��� ���������� ���������� �����, ����� � ������� �������
	if (avg_t == avg_h)
	{
		system("cls");
		cout << "TEST 2 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 2 FALSE\n";
	}
}
void test_encode_3()
{
	// ���� �� ������
	string input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaggggggggggggggggggggrrrrrrrrrrrrrrrooooooooooooooottttttttttcccccccccc"; // ����� ����� ������, ������� ����� ������������
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 16. / 6.; // ��� ���������� ���������� �����, ����� � ������� �������
	if (avg_t == avg_h)
	{
		system("cls");
		cout << "TEST 3 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 3 FALSE\n";
	}
}
void test_encode_4()
{
	// ���� �� ������
	string input = "��� ���� �� ����� � ������ �����"; // ����� ����� ������, ������� ����� ������������
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 53. / 13.; // ��� ���������� ���������� �����, ����� � ������� �������
	if (avg_t == avg_h)
	{
		system("cls");
		cout << "TEST 4 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 4 FALSE\n";
	}
}
void test_encode_5()
{
	// ���� �� ������
	string input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"; // ����� ����� ������, ������� ����� ������������
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 1. / 1.; // ��� ���������� ���������� �����, ����� � ������� �������
	if (avg_t == avg_h)
	{
		system("cls");
		cout << "TEST 5 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 5 FALSE\n";
	}
}
void tests_encode()
{
	// ������ ����� ���������� ������� ����� ������������ ����� �� �������� ������� ��������� �����
	test_encode_1();
	system("pause");
	test_encode_2();
	system("pause");
	test_encode_3();
	system("pause");
	test_encode_4();
	system("pause");
	test_encode_5();
}

void test_decode_1()
{
	map <char, string> table_codes;
	// ������������ ���������
	string code = "10110";
	// ���������� ���-������
	table_codes['a'] = "10";// 1
	table_codes['b'] = "11";// 2
	table_codes['c'] = "0";// 3
	string answer = "abc"; // ��� ��������� ���������� �����
	if (decoding_to_decode(code, table_codes) == answer)
	{
		system("cls");
		cout << "TEST 1 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 1 FALSE\n";
	}
}
void test_decode_2()
{
	map <char, string> table_codes;
	// ������������ ���������
	string code = "0000100011111100011011111000110011111010001111101000100101111011011100100001111010001001011110110001110011100001010011001100110100111101111011101011011000011000001111101101101";
	// ���������� ���-������
	table_codes['_'] = "110";// 1
	table_codes['a'] = "0111";// 2
	table_codes['c'] = "01100";// 3
	table_codes['d'] = "00000";// 4
	table_codes['e'] = "1110";// 5
	table_codes['f'] = "1001";// 6
	table_codes['g'] = "01101";// 7
	table_codes['h'] = "0001";// 8
	table_codes['i'] = "1111";// 9
	table_codes['l'] = "0101";// 10
	table_codes['m'] = "1010";// 11
	table_codes['n'] = "1011";// 12
	table_codes['o'] = "0011";// 13
	table_codes['p'] = "0010";// 14
	table_codes['s'] = "1000";// 15
	table_codes['t'] = "00001";// 16
	table_codes['u'] = "01001";// 17
	table_codes['x'] = "01000";// 18
	string answer = "this_is_a_simple_example_of_huffman_encoding"; // ��� ��������� ���������� �����
	if (decoding_to_decode(code, table_codes) == answer)
	{
		system("cls");
		cout << "TEST 2 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 2 TRUE\n";
	}
}
void test_decode_3()
{
	map <char, string> table_codes;
	// ������������ ���������
	string code = "1111111111111111111111111111111111111111111111111111111111110000000000000000000000000000000000000000101101101101101101101101101101101101101101101100100100100100100100100100100100100100100100011011011011011011011011011011010010010010010010010010010010";
	// ���������� ���-������
	table_codes['a'] = "11";// 1
	table_codes['c'] = "010";// 2
	table_codes['g'] = "00";// 3
	table_codes['o'] = "100";// 4
	table_codes['r'] = "101";// 5
	table_codes['t'] = "011";// 6
	string answer = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaggggggggggggggggggggrrrrrrrrrrrrrrrooooooooooooooottttttttttcccccccccc"; // ��� ��������� ���������� �����
	if (decoding_to_decode(code, table_codes) == answer)
	{
		system("cls");
		cout << "TEST 3 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 3 FALSE\n";
	}
}
void test_decode_4()
{
	map <char, string> table_codes;
	// ������������ ���������
	string code = "00011111110";
	// ���������� ���-������
	table_codes['�'] = "0";// 1
	table_codes['�'] = "11";// 2
	table_codes['�'] = "10";// 3

	string answer = "�������"; // ��� ��������� ���������� �����
	if (decoding_to_decode(code, table_codes) == answer)
	{
		system("cls");
		cout << "TEST 4 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 4 FALSE\n";
	}
}
void test_decode_5()
{
	map <char, string> table_codes;
	// ������������ ���������
	string code = "00";
	// ���������� ���-������
	table_codes['a'] = "0";// 1
	string answer = "aa"; // ��� ��������� ���������� �����
	if (decoding_to_decode(code, table_codes) == answer)
	{
		system("cls");
		cout << "TEST 5 TRUE\n";
	}
	else
	{
		system("cls");
		cout << "TEST 5 FALSE\n";
	}
}
void tests_decode()
{
	test_decode_1();
	system("pause");
	test_decode_2();
	system("pause");
	test_decode_3();
	system("pause");
	test_decode_4();
	system("pause");
	test_decode_5();
}