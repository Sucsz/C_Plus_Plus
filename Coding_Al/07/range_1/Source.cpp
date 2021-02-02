#include "Header.h"
// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 45 минут
// Данная программа реализует алгоритмы интервального-кодирования(1) и интервального-декодирования(1). 
// Работает для случаев, где интервал между одинаковыми буквами <= 9
// Компилятор mingw-5.2.0

int main()
{
    system("chcp 1251");  // Переходим на русский язык в консоли
    system("cls");
    cout << "\t\tТЕСТИРОВАНИЕ:\n";
    tests();
    string input;
    cout << "\t\tСЦЕНАРИЙ:\n";
    cout << "Введите сообщение, которое вы желаете кодировать: \n\t\t";
    cin >> input;
    cout << "\nЗакодированное сообщение:\n";
    //show_freq_table(frequency_analysis(input));
    string code = to_range_1(input);
    cout << "\t\t" << code << '\n';
    cout << "Введите сообщение, которое вы желаете декодировать: \n\t\t";
    string decode;
    cin >> decode;
    cout << "Введите количество символов алфавита: \n";
    vector<char> alphabet;
    int alphabet_size;
    cin >> alphabet_size;
    for (int counter = 0; counter < alphabet_size; counter++)
    {
        cout << "Введите текущий символ алфавита:\n";
        char symbol;
        cin >> symbol;
        alphabet.push_back(symbol);
    }
    string result = decode_range_1(alphabet, decode);

    cout << "\t\t" << result << "\n\n";
    return 0;
}

// Функция реализует частотный анализ входящей  строки
map<char, int> frequency_analysis(string input) // Функция, реализующая частотный анализ входящей строки
{
    map<char, int> freq_table;
    int size = input.size();
    for (int counter = 0; counter < size; counter++)
        freq_table[input[counter]] += 1;
    return freq_table;
}
// Функция выводит таблицу частот на экран
void show_freq_table(map<char, int> freq_table)
{
    map<char, int>::iterator it;
    for (it = freq_table.begin(); it != freq_table.end(); it++)
        cout << "Символ: " << it->first << "\tКоличество: " << it->second << '\n';
    cout << "\n\n";
}
// Кодирует переданное сообщением интервальным кодом 1
string to_range_1(string input)
{
    map<char, int> freq_table = frequency_analysis(input);
    map<char, int>::reverse_iterator rit;
    string code;
    for (rit = freq_table.rbegin(); rit != freq_table.rend(); rit++) // Дописываем алфавит в начало строки
        input.insert(input.begin(), rit->first);
    for (int counter = input.size() - 1; counter >= freq_table.size(); counter--)
    {
        int range = 0; // Считает расстояние до следующего аналогичного символа
        for (int counter2 = counter - 1; counter2 >= 0; counter2--)
        {
            if (input[counter] == input[counter2])
                break;
            range++;
        }
        code.insert(code.begin(), range + '0');
    }
    return code;
}
// Декодирует переданное сообщение, закодированное интервальным кодом 1
string decode_range_1(vector<char> alphabet, string code)
{
    string decode;
    for (int counter = alphabet.size() - 1; counter >= 0; counter--)
        code.insert(code.begin(), alphabet[counter]); // Дописали алфавит
    for (int counter = alphabet.size(); counter < code.size(); counter++)
    {
        decode += code[counter - (code[counter] - '0') - 1];
        char symbol = code[counter - (code[counter] - '0') - 1];
        string res; // Танцы с бубнами, чтобы заменит символ в строке 
        res += symbol;
        code.replace(counter, 1, res);
    }
    return decode;
}

void tests()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
}
void test_1()
{
    string input = "cabbbabbac"; // Тут пишем, что хотим закодировать
    string code = to_range_1(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('a');
    alphabet.push_back('b');
    alphabet.push_back('c');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_2()
{
    string input = "abcdabcddcba"; // Тут пишем, что хотим закодировать
    string code = to_range_1(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('a');
    alphabet.push_back('b');
    alphabet.push_back('c');
    alphabet.push_back('d');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем, что хотим закодировать
    string code = to_range_1(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('а');
    alphabet.push_back('б');
    alphabet.push_back('д');
    alphabet.push_back('к');
    alphabet.push_back('р');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_4()
{
    string input = "артист"; // Тут пишем, что хотим закодировать
    string code = to_range_1(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('а');
    alphabet.push_back('и');
    alphabet.push_back('р');
    alphabet.push_back('с');
    alphabet.push_back('т');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_5()
{
    string input = "азбука"; // Тут пишем, что хотим закодировать
    string code = to_range_1(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('а');
    alphabet.push_back('б');
    alphabet.push_back('з');
    alphabet.push_back('к');
    alphabet.push_back('у');
    string decode = decode_range_1(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}

