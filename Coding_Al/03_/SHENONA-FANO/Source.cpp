/*
Общее время выполнения работы ~10 часов
 
Работа выполнена студентом 3 курса ИИТО ИСиТ
   Семыкиным В.В.

Данная программа реализует алгоритм построения кодов Шеннона-Фано, кодирование заданного сообщение, декодирование.

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
vector <pair <char, double> > sort_vector_desc(vector <pair <char, double> >);
vector<double> sum_frequencies(vector <pair <char, double> >);
void out_vector(vector<double>); 
vector <pair <char, string> > to_sh_f(vector <pair <char, double> >, vector<double>);
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
	cout << "\nПолучившейся таблица вероятностей символов: \n";
	out_table(freq_table);
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table);
	cout << "\nОтсортированная по убыванию таблица: \n";
	out_table(freq_desc);
	vector<double> sum_freq = sum_frequencies(freq_desc);
	cout << "\nКумулятивные вероятности: \n";
	out_vector(sum_freq);
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq);
	cout << "\nТаблица символ  - код: \n";
	out_codes_table(sh_f_codes);
	bool is_prefix = check_prefix(sh_f_codes);
	pair <vector <pair<char, string> >, string> tables_code_and_code;
	pair <vector <pair<char, string> >, string> tables_code_and_decode;
	if (is_prefix)
	{
		tables_code_and_code = encoding_to_code(input, sh_f_codes);
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

	for (int counter = 0; counter < input.size(); counter++) //Проходем по каждому символу в слове
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
		cout << "Ключ: " << container[counter].first << "\tЗначение: " << container[counter].second <<'\n';
	}
}

//Сортировка вектора по убыванию частот
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

//Образование возрастающих сумм частот q
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

// Вывод вектора на экран
void out_vector(vector<double> container)
{
	int size = container.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Значение: " << container[counter]<< '\n';
	}
}


// Образование кодов символов
vector <pair<char, string> > to_sh_f(vector <pair <char, double> > freq_table, vector<double> sum_freq)
{
	// Массив кодовых слов
	vector<pair<char, string> > codes;
	int size = freq_table.size();
	for (int counter = 0; counter < size; counter++) //Для каждой комулятивной вероятности
	{
		vector<int> code; // Под одной буквы
		// Переводим вещественные числа в двоичную систему
		int number_char = ceil(-log2(freq_table[counter].second)); // Ограничение знаков двоичного числа
		for (int counter2 = 0; counter2 < number_char; counter2++)
		{
			sum_freq[counter] *= 2;
			code.push_back(floor(sum_freq[counter]));
			if (sum_freq[counter] >= 1)
			{
				sum_freq[counter]--;
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
void out_codes_table(vector<pair<char, string> > shf)
{
	int size = shf.size();
	for (int counter = 0; counter < size; counter++)
	{
		cout << "Символ: " << shf[counter].first << "\tКод: " << shf[counter].second << '\n';
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
			for (int counter3 = 0; counter3 < codes[counter].second.size(); counter3++) // Проход по буквам текущих сравниваемых кодов 
			{
				/*
				Здесь не возникает проблемы выхода за границы массива-кода, тк изначально сортировка по неубыванию
				*/
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
pair <vector <pair<char, string> >, string> encoding_to_code(string input, vector<pair<char, string> > sh_f_codes)
{
	int size = input.size();
	int size_table = sh_f_codes.size();
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	table_codes_and_code.first = sh_f_codes;
	for (int count = 0; count < size; count++) // Для каждой буквы исходной строки
	{
		for (int count2 = 0; count2 < size_table; count2++) // Рассматриваем все кодовые слова, пока не встретится необходимый код
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
	string answer = "000001010100101110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // Отсортированная по убывания таблица
	vector<double> sum_freq = sum_frequencies(freq_desc); // Кумулятивные вероятности
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //Таблица символ  - код: 
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
	string text = "Код_Шеннона-Фано"; // Задаем сообщение, которое хотим закодировать
	string answer = "100101010101011110011010000010000111110111101100010"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // Отсортированная по убывания таблица
	vector<double> sum_freq = sum_frequencies(freq_desc); // Кумулятивные вероятности
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //Таблица символ  - код: 
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
	string text = "Небеса и земля, также стары, как и я, десять тысяч вещей - суть одна."; // Задаем сообщение, которое хотим закодировать
	string answer = "1100010001111001000011010001010001010010001100110001111001111101001100001001000001100101100111101011001100001000110010111011011010111001000010011010110011000101001000100001001000010110100110100100000110101111000011010101101001000011011110001110001001111100110011111010000011101100000100111100001101011110001111010101101111110001011111110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // Отсортированная по убывания таблица
	vector<double> sum_freq = sum_frequencies(freq_desc); // Кумулятивные вероятности
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //Таблица символ  - код: 
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
	string text = "abcdefghijklmnopqrstuvwxyz"; // Задаем сообщение, которое хотим закодировать
	string answer = "0000000001000100001100100001100011101000010010101101100011010111001111100011001010011101001011010111110001100111011111001110111110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // Отсортированная по убывания таблица
	vector<double> sum_freq = sum_frequencies(freq_desc); // Кумулятивные вероятности
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //Таблица символ  - код: 
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
	string text = "cogito ergo sum"; // Задаем сообщение, которое хотим закодировать
	string answer = "01110000011000100100001010101011001000010110011011110"; // Тут вписываем правильный ответ
	vector <pair <char, double> > freq_table = frequency_analysis(text); // "Таблица" символ-вероятность 
	vector <pair <char, double> > freq_desc = sort_vector_desc(freq_table); // Отсортированная по убывания таблица
	vector<double> sum_freq = sum_frequencies(freq_desc); // Кумулятивные вероятности
	vector<pair<char, string> > sh_f_codes = to_sh_f(freq_desc, sum_freq); //Таблица символ  - код: 
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
	table_codes_and_code.second = "100101010101011110011010000010000111110111101100010";
	// Заполнение код-символ
	pair<char, string> code1('н', "00"); // 1
	table_codes_and_code.first.push_back(code1);
	
	pair<char, string> code2('о', "010"); // 2
	table_codes_and_code.first.push_back(code2);
	
	pair<char, string> code3('а', "011"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('К', "1001"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('д', "1010"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('_', "1011"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('Ш', "1100"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('е', "1101"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('-', "1110"); // 9
	table_codes_and_code.first.push_back(code9);

	pair<char, string> code10('Ф', "1111"); // 10
	table_codes_and_code.first.push_back(code10);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "Код_Шеннона-Фано"; // Тут вписываем правильный ответ
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
	table_codes_and_code.second = "000001010100101110";
	// Заполнение код-символ
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
void test_decode_3()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// Декодируемое сообщение
	table_codes_and_code.second = "0110000100110";
	// Заполнение код-символ
	pair<char, string> code1('p', "00"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('a', "011"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('l', "100"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('e', "110"); // 4
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
void test_decode_4()
{
	pair <vector <pair<char, string> >, string> table_codes_and_code;
	// Декодируемое сообщение
	table_codes_and_code.second = "000000010011010101111000101011001110";
	// Заполнение код-символ
	pair<char, string> code1('а', "0000"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('б', "0001"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('в', "0011"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('г', "0101"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('д', "0111"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('е', "1000"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('ё', "1010"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('ж', "1100"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('з', "1110"); // 9
	table_codes_and_code.first.push_back(code9);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "абвгдеёжз"; // Тут вписываем правильный ответ
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
	table_codes_and_code.second = "1101010110010001101100110000010001110010010001000100101001011101000111100000101001010001101100100001011001000111111100";
	// Заполнение код-символ
	pair<char, string> code1(' ', "000"); // 1
	table_codes_and_code.first.push_back(code1);

	pair<char, string> code2('а', "001"); // 2
	table_codes_and_code.first.push_back(code2);

	pair<char, string> code3('с', "010"); // 3
	table_codes_and_code.first.push_back(code3);

	pair<char, string> code4('ш', "1000"); // 4
	table_codes_and_code.first.push_back(code4);

	pair<char, string> code5('о', "1001"); // 5
	table_codes_and_code.first.push_back(code5);

	pair<char, string> code6('л', "1011"); // 6
	table_codes_and_code.first.push_back(code6);

	pair<char, string> code7('у', "1100"); // 7
	table_codes_and_code.first.push_back(code7);

	pair<char, string> code8('Ш', "11010"); // 8
	table_codes_and_code.first.push_back(code8);

	pair<char, string> code9('С', "11011"); // 9
	table_codes_and_code.first.push_back(code9);

	pair<char, string> code10('п', "11100"); // 10
	table_codes_and_code.first.push_back(code10);

	pair<char, string> code11('е', "11101"); // 11
	table_codes_and_code.first.push_back(code11);

	pair<char, string> code12('и', "11110"); // 12
	table_codes_and_code.first.push_back(code12);

	pair<char, string> code13('к', "11111"); // 13
	table_codes_and_code.first.push_back(code13);

	string text = table_codes_and_code.second; // Cообщение, которое хотим декодировать
	string answer = "Шла Саша по шоссе и сосала сушку"; // Тут вписываем правильный ответ
	if (decoding_to_decode(table_codes_and_code).second == answer)
	{
		printf("decode( %s ) == %s \n\t\tTRUE\n\n", text.c_str(), answer.c_str());
	}
	else
	{
		cout << "\t\tFALSE\n\n";
	}
}