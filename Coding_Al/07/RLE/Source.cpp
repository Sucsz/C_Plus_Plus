// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 15 минут
// Данная программа реализует алгоритмы RLE кодирования и декодирования  
// Компилятор mingw-5.2.0

#include "Header.h"

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
    vector<pair<int, char> > code = to_rle(input);
    cout << "\nЗакодированное сообщение:\n";
    show_code(code);
    cout << "\nДекодированное закодированное сообщение:\n";
    string decode = decode_rle(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode)
        cout << "Исходное сообщение совпало c декодированным!\n\n";
    else
        cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}

vector<pair<int, char> > to_rle(string input)
{
    vector<pair<int, char> > code;
    int num = 1; // количество повторений текущей буквы
    for (int counter = 0; counter < input.size(); counter++)
    {
        if (input[counter] == input[counter + 1])
        {
            num++;
            continue;
        }
        else
        {
            pair<int, char> temp(num, input[counter]);
            code.push_back(temp);
            num = 1;
        }
    }
    return code;
}

void show_code(vector<pair<int, char> > code)
{
    for (int counter = 0; counter < code.size(); counter++)
    {
        cout << "количество: " << code[counter].first << " буква: " << code[counter].second << '\n';
    }
}

string decode_rle(vector<pair<int, char> > code)
{
    string decode;
    for (int counter = 0; counter < code.size(); counter++)
    {
        for (int counter2 = 0; counter2 < code[counter].first; counter2++)
        {
            decode += code[counter].second;
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
    string input = "аааааааааааааааааааааааааааааааааааааааааааааааабббббббббббббббббббббббббббббббббббсссссссссссссссссссссссссссс"; // Тут пишем то, что хотим закодировать
    vector<pair<int, char> > code = to_rle(input);
    string decode = decode_rle(code);
    if (input == decode)
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n\n";
}
void test_2()
{
    string input = "bbbcccddd"; // Тут пишем то, что хотим закодировать
    vector<pair<int, char> > code = to_rle(input);
    string decode = decode_rle(code);
    if (input == decode)
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем то, что хотим закодировать
    vector<pair<int, char> > code = to_rle(input);
    string decode = decode_rle(code);
    if (input == decode)
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n\n";
}
void test_4()
{
    string input = "аааааааааааааааааааааааааааааааааааааааааа"; // Тут пишем то, что хотим закодировать
    vector<pair<int, char> > code = to_rle(input);
    string decode = decode_rle(code);
    if (input == decode)
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n\n";
}
void test_5()
{
    string input = "аабаабаабааб"; // Тут пишем то, что хотим закодировать
    vector<pair<int, char> > code = to_rle(input);
    string decode = decode_rle(code);
    if (input == decode)
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n\n";
}