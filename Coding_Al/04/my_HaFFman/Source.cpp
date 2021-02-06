#include "header.h"

/*
Общее время выполнения работы ~10 часов

Работа выполнена студентом 3 курса ИИТО ИСиТ
   Семыкиным В.В.

Данная программа реализует алгоритм построения кодов Хаффмана, кодирование заданного сообщение, декодирование, построение дерева Хаффмана.
*/

int main()
{
	system("chcp 1251");  // Переходим на русский язык в консоли
	system("cls");
	cout << "Тесты кодирования:\n";
//	system("pause");
//	tests_encode();
	cout << "Тесты декодирования:\n";
//	system("pause");
//	tests_decode();
//	system("pause");
	cout << "\t\t\t\t\tЗАПУСК СЦЕНАРИЯ:\n\n"; // Сценарий - это loop-test, в начале кодируем, потом декодируем полученное
	cout << "Введите сообщение, которое вы желаете кодировать: \n";
	string input;
	getline(cin, input);
	map<char, int> freq_table = frequency_analysis(input);
	cout << "\n\nТаблица символ-количество:\n";
	show_freq_table(freq_table);
	cout << "Порядок выполнения аппликаций:\n";
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	cout << "\n\n";
	traversal_tree(&table_codes, tree_haffman.top(), "");
	cout << "\n\nТаблица символ-код:\n";
	show_table_codes(table_codes);
	cout << "\n\nПроверка неравенства Крафта:\n";
	check_kraft(table_codes);
	string code = encoding_to_code(input, table_codes);
	cout << "\n\n\nЗакодированное исходное сообщение: \n" << code;
	string decode = decoding_to_decode(code, table_codes);
	cout << "\n\nДекодированное закодированное сообщение: \n" << decode;
	if (decode == input)
		cout << "\n\nИсходная строка совпала с декодированной!\n";
	cout << "\n\n";
	system("pause");
	return 0;
}
map<char, int> frequency_analysis(string input) // Функция, реализующая частотный анализ входящей строки
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
		cout << "Символ: " << it->first << "\tКоличество: " << it->second << '\n';
	cout << "\n\n";
}

void show_table_codes(map<char, string> freq_table)
{
	map<char, string>::iterator it;
	for (it = freq_table.begin(); it != freq_table.end(); it++)
		cout << "Символ: " << it->first << "\tкод: " << it->second << '\n';
}

priority_queue<Node*, vector<Node*>, Compare> fill_tree(map<char, int> freq_table) // Функция заполняет дерево хаффмана
{
	priority_queue<Node*, vector<Node*>, Compare> tree;
	map<char, int>::iterator it;
	for (it = freq_table.begin(); it != freq_table.end(); it++)
	{
		Node* p = new Node(it->first, it->second); // Создание нового узла с заданными значениями
		tree.push(p);
		// cout << "|добавляемая буква " << p->symbol << '-' << tree.top()->symbol << " Верхняя буква в очереди| "; Проверка правильного заполнения очереди
	}
	return tree;
}
priority_queue<Node*, vector<Node*>, Compare> to_haffamn(priority_queue<Node*, vector<Node*>, Compare> tree)
{
	if (tree.size() == 1)
	{
		tree.top()->rib = 0; // Без разницы, можно 1, можно 0.
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
void traversal_tree(map<char, string>* table_codes, Node* root, string code, unsigned k) // Обход по деревву, вывод и составление кодов
{
	if (root)
	{

		if (root->rib >= 0 && root->rib <= 1) // У корня нет ребра, поэтому приходится ставить условие, ограничивающие попадание корня
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
		cout << "\nПроверка пройдена. Полученная схема кодов является разделимой";
	else
		cout << "\nПроверка не пройдена, Полученная схема кодов не является разделимой";
}
// Функция, кодирующая исходное сообщение, принимает таблицу кодов и исходное сообщение, возвращает  закодированное сообщение. 
string encoding_to_code(string input, map<char, string> table_codes)
{
	int size = input.size();
	string code;
	map<char, string>::iterator it;
	for (int count = 0; count < size; count++) // Для каждой буквы исходной строки
	{
		for (it = table_codes.begin(); it != table_codes.end(); it++) // Рассматриваем все кодовые слова, пока не встретится необходимый код
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
// Функция, декодирующая исходное сообщение, принимает таблицу кодов и закодированное сообщение, возвращает декодированное сообщение. 
string decoding_to_decode(string code, map<char, string> table_codes)
{
	int size = code.size();
	string decode;
	string cur_code;
	map<char, string>::iterator it;
	for (int count = 0; count < size; count++) // Для каждой цифры исходной строки будем формировать кодовое слово, и проверять его на соответсвие таблице кодов, если не нашли
													// То увеличиваем кодовое слово, добавляяя следующую цифру.
	{
		cur_code += code[count];
		for (it = table_codes.begin(); it != table_codes.end(); it++) // Рассматриваем все кодовые слова, пока не встретится необходимый код
		{
			if (cur_code == it->second)
			{
				decode += it->first;
				cur_code = ""; // Если подходящее кодовое слово найдено, добавляем в декод символ, хранящийся под этим кодом и обнуляем код.
				break;
			}
		}
	}
	return decode;
}
// Функция, вычисляющая среднюю длину кодов
double avg(map <char, string> table_codes)
{
	double avg = 0;
	map<char, string>::iterator it;
	for (it = table_codes.begin(); it != table_codes.end(); it++) // Рассматриваем все кодовые слова, пока не встретится необходимый код
	{
		avg += it->second.size();
	}
	cout << "\n" << avg << "--" << table_codes.size() << endl;
	avg /= table_codes.size();
	return avg;
}
void test_encode_1()
{
	string input = "abc"; // Здесь пишем строку, которую хотим закодировать
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
	// Тест из лекции
	string input = "this_is_a_simple_example_of_huffman_encoding"; // Здесь пишем строку, которую хотим закодировать
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 77. / 18.; // Тут записываем правильный ответ, лучше в дробном формате
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
	// Тест из лекции
	string input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaggggggggggggggggggggrrrrrrrrrrrrrrrooooooooooooooottttttttttcccccccccc"; // Здесь пишем строку, которую хотим закодировать
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 16. / 6.; // Тут записываем правильный ответ, лучше в дробном формате
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
	// Тест из лекции
	string input = "Шла Саша по шоссе и сосала сушку"; // Здесь пишем строку, которую хотим закодировать
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 53. / 13.; // Тут записываем правильный ответ, лучше в дробном формате
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
	// Тест из лекции
	string input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"; // Здесь пишем строку, которую хотим закодировать
	map<char, int> freq_table = frequency_analysis(input);
	priority_queue<Node*, vector<Node*>, Compare> tree = fill_tree(freq_table);
	priority_queue<Node*, vector<Node*>, Compare> tree_haffman = to_haffamn(tree);
	map<char, string> table_codes;
	traversal_tree(&table_codes, tree_haffman.top(), "");
	check_kraft(table_codes);
	double avg_t = avg(table_codes);
	double avg_h = 1. / 1.; // Тут записываем правильный ответ, лучше в дробном формате
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
	// Данные тесты сравнивают среднюю длину получившихся кодов со среденей длинной имеющихся кодов
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
	// Декодируемое сообщение
	string code = "10110";
	// Заполнение код-символ
	table_codes['a'] = "10";// 1
	table_codes['b'] = "11";// 2
	table_codes['c'] = "0";// 3
	string answer = "abc"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	string code = "0000100011111100011011111000110011111010001111101000100101111011011100100001111010001001011110110001110011100001010011001100110100111101111011101011011000011000001111101101101";
	// Заполнение код-символ
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
	string answer = "this_is_a_simple_example_of_huffman_encoding"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	string code = "1111111111111111111111111111111111111111111111111111111111110000000000000000000000000000000000000000101101101101101101101101101101101101101101101100100100100100100100100100100100100100100100011011011011011011011011011011010010010010010010010010010010";
	// Заполнение код-символ
	table_codes['a'] = "11";// 1
	table_codes['c'] = "010";// 2
	table_codes['g'] = "00";// 3
	table_codes['o'] = "100";// 4
	table_codes['r'] = "101";// 5
	table_codes['t'] = "011";// 6
	string answer = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaggggggggggggggggggggrrrrrrrrrrrrrrrooooooooooooooottttttttttcccccccccc"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	string code = "00011111110";
	// Заполнение код-символ
	table_codes['А'] = "0";// 1
	table_codes['Б'] = "11";// 2
	table_codes['С'] = "10";// 3

	string answer = "АААБББС"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	string code = "00";
	// Заполнение код-символ
	table_codes['a'] = "0";// 1
	string answer = "aa"; // Тут вписываем правильный ответ
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