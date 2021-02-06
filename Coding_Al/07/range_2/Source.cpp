#include "Header.h"
// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 2 часа минут
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
    string code = to_range_2(input);
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
    string result = decode_range_2(alphabet, decode);
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
string to_range_2(string input)
{
    map<char, int> freq_table = frequency_analysis(input);
    map<char, int>::reverse_iterator rit;
    string code;
    for (rit = freq_table.rbegin(); rit != freq_table.rend(); rit++) // Дописываем алфавит в начало строки
        input.insert(input.begin(), rit->first);
    for (int counter = input.size() - 1; counter >= freq_table.size(); counter--)
    {
        map<char,int> num_of_dif; // Считает количество различных символов
        for (int counter2 = counter - 1; counter2 >= 0; counter2--)
        {
            if (input[counter] == input[counter2])
                break;
            num_of_dif[input[counter2]]++;
        }
        code.insert(code.begin(), num_of_dif.size() + '0');
    }
    return code;
}
// Декодирует переданное сообщение, закодированное интервальным кодом 1
string decode_range_2(vector<char> alphabet, string code)
{
    string decode;
    for (int counter = alphabet.size() - 1; counter >= 0; counter--)
        code.insert(code.begin(), alphabet[counter]); // Дописали алфавит
    for (int counter = alphabet.size(); counter < code.size(); counter++)
    {
        int num_of_dif = code[counter] - '0';
        vector<char> dif_chars;
        for (int counter2 = counter - 1; counter2 >= 0; counter2--)
        {
            if (!num_of_dif)
            {
                int counter3 = counter2;
                vector<char>::iterator is_find2;
                is_find2 = find(dif_chars.begin(), dif_chars.end(), code[counter3]);
                while (is_find2 != dif_chars.end())
                {
                    counter3--;
                    is_find2 = find(dif_chars.begin(), dif_chars.end(), code[counter3]);
                }
                decode += code[counter3]; 
                char symbol = code[counter3];
                string res;
                res += symbol;
                code.replace(counter, 1, res);
                break;
            }
            vector<char>::iterator is_find;
            is_find = find(dif_chars.begin(), dif_chars.end(), code[counter2]);
            if (code[counter] != code[counter2] && (is_find == dif_chars.end()))
            {
                dif_chars.push_back(code[counter2]);
                num_of_dif--;
            }
        }
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
    string code = to_range_2(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('a');
    alphabet.push_back('b');
    alphabet.push_back('c');
    string decode = decode_range_2(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_2()
{
    string input = "abcdabcddcba"; // Тут пишем, что хотим закодировать
    string code = to_range_2(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('a');
    alphabet.push_back('b');
    alphabet.push_back('c');
    alphabet.push_back('d');
    string decode = decode_range_2(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем, что хотим закодировать
    string code = to_range_2(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('а');
    alphabet.push_back('б');
    alphabet.push_back('д');
    alphabet.push_back('к');
    alphabet.push_back('р');
    string decode = decode_range_2(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_4()
{
    string input = "артист"; // Тут пишем, что хотим закодировать
    string code = to_range_2(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('а');
    alphabet.push_back('и');
    alphabet.push_back('р');
    alphabet.push_back('с');
    alphabet.push_back('т');
    string decode = decode_range_2(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_5()
{
    string input = "азбука"; // Тут пишем, что хотим закодировать
    string code = to_range_2(input);
    vector<char> alphabet; // Алфавит для декодирования
    alphabet.push_back('а');
    alphabet.push_back('б');
    alphabet.push_back('з');
    alphabet.push_back('к');
    alphabet.push_back('у');
    string decode = decode_range_2(alphabet, code);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}

