/*
Общее время выполнения работы ~2.75 часов
 
Работа выполнена студентом 3 курса ИИТО ИСиТ
   Семыкиным В.В.

Данная программа реализует алгоритм построения кодов Гилберта-Мура, кодирование заданного сообщение, декодирование.

*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// Сигнатуры функций
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

//Сигнатуры тестов
void tests_encode(); // Кодирование
void test_encode_1();
void test_encode_2();
void test_encode_3();
void test_encode_4();
void test_encode_5();
void tests_decode(); // Декодирование
void test_decode_1();
void test_decode_2();
void test_decode_3();
void test_decode_4();
void test_decode_5();

int main()
{
	system("chcp 1251");  // Переходим на русский язык в консоли
	system("cls");
	cout << "Тесты кодирования:\n";
	cout << "---------------------------------------------------------------------------------------------------------";
	tests_encode();
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "\nТесты декодирования\n\n";
	cout << "---------------------------------------------------------------------------------------------------------\n";
	tests_decode();
	cout << "---------------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\tЗАПУСК СЦЕНАРИЯ:\n\n"; // Сценарий по факту loop-test в начале кодируем, потом декодируем полученное
	string input;
	cout << "Введите сообщение, которое вы желаете кодировать: ";
	getline(cin, input);
	vector <pair <char, double> > freq_table = frequency_analysis(input); // "Таблица" символ-вероятность 
	cout << "\nТаблица вероятностей символов: \n";
	out_table(freq_table);
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	cout << "\nНабор значений q\n";
	out_vector(q);
	cout << "\nНабор значений d\n";
	out_vector(d);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d);
	cout << "\nТаблица символ  - код:\n";
	out_codes_table(gilbert_m_codes);
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(input, gilbert_m_codes);
		cout << "\nИсходное сообщение: \n" << input << "\n\nЗакодированное сообщение\n" << tables_code_and_code.second;
		cout << "\n\nДекодинг кода в исходное сообщение:\n";
		tables_code_and_decode = decoding_to_decode(tables_code_and_code);
		cout << "Исходное сообщение: \n" << tables_code_and_decode.second << "\n\n";
		if (tables_code_and_decode.second == input)
		{
			cout << "Исходная строка совпала с декодированной!\n\n";
		}
		else
		{
			return -2;
		}
	}
	else // Код не префиксный
	{
		return -1;
	}
	efficiency_coefficient(input, tables_code_and_code);
	system("pause");
	return 0;
}

// Частотный анализ
vector <pair <char, double> > frequency_analysis(string input)
{
	/*
	Функция, реализующая частотный анализ заданной строки. Результатом набор пар ключ-значение, где ключ - буква,
	Значение - вероятность встретить букву в передаваемом сообщении.
	*/
	vector <pair <char, double> > freq_table;
	int size = input.size();
	for (int counter = 0; counter < size; counter++) //Проходем по каждому символу в слове
	{
		//считаем количество букв
		for (int counter2 = 0; counter2 < freq_table.size(); counter2++)
		{
			if (freq_table[counter2].first == input[counter]) // Сравниваем его с имеющимися символами в "Таблице"
			{
				freq_table[counter2].second += 1.0 / input.size(); // Если совпали, увличиваем вероятность
				goto out_label;
			}
		}
		freq_table.push_back(pair<char, double>(input[counter], 1.0 / input.size()));
		// К сожеланию приходиться добавлять goto, вместо else, иначе не добавится первый элемент и второй цикл не будет работать. 
	out_label:;
	}
	return freq_table;
}

// Вывод "таблицы" на экран
void out_table(vector <pair <char, double> > container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Ключ: " << container[counter].first << "\tЗначение: " << container[counter].second << '\n';
	}
}

// Образование кумулятивных частот q и d
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

// Вывод вектора на экран
void out_vector(vector<double> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Значение: " << container[counter] << '\n';
	}
}

// Образование кодов символов
vector <pair<char, string> > to_gilbert_moor(vector <pair <char, double> > freq_table, vector<double> d)
{
	// Массив кодовых слов
	vector<pair<char, string> > codes;
	int size = freq_table.size();
	for (int counter = 0; counter < size; counter++) //Для каждой комулятивной вероятности
	{
		vector<int> code; // Код одной буквы
		// Переводим вещественные числа в двоичную систему
		int number_char = ceil(-log2(freq_table[counter].second / 2)); // Ограничение знаков двоичного числа
		for (int counter2 = 0; counter2 < number_char; counter2++)
		{
			d[counter] *= 2;
			code.push_back(floor(d[counter]));
			if (d[counter] >= 1)
			{
				d[counter]--;
			}
		}
		// Переводим в строку
		string result;
		for (int counter2 = 0; counter2 < code.size(); counter2++)
		{
			result += code[counter2] ? '1' : '0';
		}
		codes.push_back(pair<char, string>(freq_table[counter].first, result));
	}
	return codes;
}

// Вывод таблицы кодов на экран 
void out_codes_table(vector<pair<char, string> > gilbert_m)
{
	int size = gilbert_m.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Символ: " << gilbert_m[counter].first << "\tКод: " << gilbert_m[counter].second << '\n';
	}
}

// Проверка префиксности получившихся кодов
bool check_prefix(vector<pair<char, string> > codes)
{
	int size = codes.size();
	for (int counter = 0; counter < size; counter++) // Проход по всем кодам
	{
		for (int counter2 = counter + 1; counter2 < size; counter2++) // Проход по всем кодам, которые следует после нынешнего 
		{
			bool flag = false; // Индикатор совпадения кодов, если они не совпали меняем значение на false
			for (int counter3 = 0; (counter3 < codes[counter].second.size()) && counter3 < codes[counter2].second[counter3]; counter3++) // Проход по буквам текущих сравниваемых кодов 
			{
				//Т.К. у нас неосортированный d, counter3 < codes[counter2].second[counter3] данное условие позволяет не выходить за границы кодового слова. 
				if (codes[counter].second[counter3] != codes[counter2].second[counter3])
				{
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "\nДанная таблица кодов не является префиксной\n";
				return false;
			}
		}
	}
	cout << "\nДанная таблица кодов является префиксной\n";
	return true;
}

// Функция, кодирующая исходное сообщение, принимает исходную таблицу кодов и сообщение, возвращает исходную таблицу кодов и закодированное сообщение. 
pair <vector <pair<char, string> >, string> encoding_to_code(string input, vector<pair<char, string> > gilbert_m_codes)
{
	int size = input.size();
	int size_table = gilbert_m_codes.size();
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	table_codes_and_code.first = gilbert_m_codes;
	for (int count = 0; count < size; count++) // Для каждой буквы исходной строки
	{
		for (int count2 = 0; count2 < size_table; count2++) // Рассматриваем все кодовые слова, пока не встретится необходимый код
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

// Функция, декодирующая исходное сообщение, принимает исходную таблицу кодов и сообщение, возвращает исходную таблицу кодов и декодированное сообщение. 
pair <vector <pair<char, string> >, string> decoding_to_decode(pair <vector <pair<char, string> >, string> table_codes_and_code)
{
	int code_size = table_codes_and_code.second.size();
	int size_table = table_codes_and_code.first.size();
	pair <vector <pair<char, string> >, string> table_codes_and_decode;
	table_codes_and_decode.first = table_codes_and_code.first;
	string code;
	for (int count = 0; count < code_size; count++) // Для каждой цифры исходной строки будем формировать кодовое слово, и проверять его на соответсвие таблице кодов, если не нашли
													// То увеличиваем кодовое слово, добавляяя следующую цифру.
	{
		code += table_codes_and_code.second[count];
		for (int count2 = 0; count2 < size_table; count2++) // Рассматриваем все кодовые слова, пока не встретится необходимый код
		{
			if (code == table_codes_and_decode.first[count2].second)
			{
				table_codes_and_decode.second += table_codes_and_decode.first[count2].first;
				code = ""; // Если подходящее кодовое слово найдено, добавляем в декод символ, хранящийся под этим кодом и обнуляем код.
				break;
			}
		}
	}
	return(table_codes_and_decode);
}

// Функция, вычисляющая степень сжатия
void efficiency_coefficient(string input, pair <vector <pair<char, string> >, string> tables_code_and_code)
{
	double size_input = input.size();
	double size_code = tables_code_and_code.second.size();
	cout << "Сжатие исходного сообщения с помощью данного кодирования для данного сообщения составило:\n" << size_input * 8 / size_code << "\n\n\n";
}

void tests_encode() // Функция объединяющая тесты кодирования
{
	test_encode_1();
	test_encode_2();
	test_encode_3();
	test_encode_4();
	test_encode_5();
}

void test_encode_1()
{
	string text = "string"; // Задаем сообщение, которое хотим закодировать
	string answer = "000101000110100111001110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "Таблица" символ-код
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // Кодирование
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
	string text = "abbbbbbccc"; // Задаем сообщение, которое хотим закодировать
	string answer = "00001010101010101110110110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "Таблица" символ-код
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // Кодирование
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
	string text = "Небеса и земля, также стары, как и я, десять тысяч вещей - суть одна."; // Задаем сообщение, которое хотим закодировать
	string answer = "0000000100010000111110001000101001110101011110101011000000000010100000111000011110010010011101011010100111101110110000100001001010010110101001111100011011001101001110101101110001111011100101011110101011001001001110101110100100010001011001001010111011010101101011100110001011001001110000001011110010000010111001110001011101011010111101111010100101111100111010111011010101111101101101001111110100011111111110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "Таблица" символ-код
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // Кодирование
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
	string text = "apple"; // Задаем сообщение, которое хотим закодировать
	string answer = "000101101110111110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "Таблица" символ-код
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // Кодирование
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
	string text = "азбука"; // Задаем сообщение, которое хотим закодировать
	string answer = "0010110100111001110001"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector<double> q, d;
	compute_q_d(&q, &d, freq_table);
	vector <pair<char, string> > gilbert_m_codes = to_gilbert_moor(freq_table, d); // "Таблица" символ-код
	bool is_prefix = check_prefix(gilbert_m_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(text, gilbert_m_codes); // Кодирование
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

void tests_decode() // Функция объединяющая тесты декодирования
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
	// Декодируемое сообщение
	table_codes_and_code.second = "000101000110100111001110";
	// Заполнение код-символ
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

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "string"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	table_codes_and_code.second = "00001010101010101110110110";
	// Заполнение код-символ
	pair<char, string> code1('a', "00001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('b', "01"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('c', "110"); // 3
	table_codes_and_code.first.push_back(code3);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "abbbbbbccc"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	table_codes_and_code.second = "0000000100010000111110001000101001110101011110101011000000000010100000111000011110010010011101011010100111101110110000100001001010010110101001111100011011001101001110101101110001111011100101011110101011001001001110101110100100010001011001001010111011010101101011100110001011001001110000001011110010000010111001110001011101011010111101111010100101111100111010111011010101111101101101001111110100011111111110";
	// Заполнение код-символ
	pair<char, string> code1('Н', "00000001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('е', "00010"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('б', "00011111"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('с', "00101"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('а', "00111"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6(' ', "0101"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('и', "0111101"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('з', "10000000"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('м', "10000011"); // 9
	table_codes_and_code.first.push_back(code9);

	pair<char, string> code10('л', "10000111"); // 10
	table_codes_and_code.first.push_back(code10);

	pair<char, string> code11('я', "100100"); // 11
	table_codes_and_code.first.push_back(code11);

	pair<char, string> code12(',', "100111"); // 12
	table_codes_and_code.first.push_back(code12);

	pair<char, string> code13('т', "10101"); // 13
	table_codes_and_code.first.push_back(code13);

	pair<char, string> code14('к', "101110"); // 14
	table_codes_and_code.first.push_back(code14);

	pair<char, string> code15('ж', "11000010"); // 15
	table_codes_and_code.first.push_back(code15);

	pair<char, string> code16('р', "11000110"); // 16
	table_codes_and_code.first.push_back(code16);

	pair<char, string> code17('ы', "1100110"); // 17
	table_codes_and_code.first.push_back(code17);

	pair<char, string> code18('д', "1101001"); // 18
	table_codes_and_code.first.push_back(code18);

	pair<char, string> code19('ь', "1101101"); // 19
	table_codes_and_code.first.push_back(code19);

	pair<char, string> code20('ч', "11100000"); // 20
	table_codes_and_code.first.push_back(code20);

	pair<char, string> code21('в', "11100100"); // 21
	table_codes_and_code.first.push_back(code21);

	pair<char, string> code22('щ', "11100111"); // 22
	table_codes_and_code.first.push_back(code22);

	pair<char, string> code23('й', "11101011"); // 23
	table_codes_and_code.first.push_back(code23);

	pair<char, string> code24('-', "11101111"); // 24
	table_codes_and_code.first.push_back(code24);

	pair<char, string> code25('у', "11110011"); // 25
	table_codes_and_code.first.push_back(code25);

	pair<char, string> code26('о', "11110110"); // 26
	table_codes_and_code.first.push_back(code26);

	pair<char, string> code27('н', "11111010"); // 27
	table_codes_and_code.first.push_back(code27);

	pair<char, string> code28('.', "11111110"); // 28
	table_codes_and_code.first.push_back(code28);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "Небеса и земля, также стары, как и я, десять тысяч вещей - суть одна."; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	table_codes_and_code.second = "000101101110111110";
	// Заполнение код-символ
	pair<char, string> code1('a', "0001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('p', "011"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('l', "1011"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('e', "1110"); // 4
	table_codes_and_code.first.push_back(code4);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "apple"; // Тут вписываем правильный ответ
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
	// Декодируемое сообщение
	table_codes_and_code.second = "0010110100111001110001";
	// Заполнение код-символ
	pair<char, string> code1('а', "001"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('з', "0110"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('б', "1001"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('у', "1100"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('к', "1110"); // 5
	table_codes_and_code.first.push_back(code5);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "азбука"; // Тут вписываем правильный ответ
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}