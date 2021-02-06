// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 10 минут
// Данная программа реализует алгоритмы кодирования и декодирования LZSS 
// Компилятор mingw-5.2.0, необходимо использовать ключ -std=gnu++11

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
    vector<vector<int>> code = to_lzss(input);
    cout << "\nЗакодированное сообщение:\n";
    show_code(code);
    cout << "\nДекодированное закодированное сообщение:\n";
    string decode = decode_lzss(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode)
        cout << "Исходное сообщение совпало c декодированным!\n\n";
    else
        cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}

vector<vector<int>> to_lzss(string input)
{
    // буффера, в привычном плане алгоритма тут нет, в роли него выступает динамически расширяющийся словарь, а строка поступает посимвольно(буффер 1).
    vector<vector<int>> codes; // Кодовые диады, вместо символа будет код символа
    string buffer;
    for (int counter = 0; counter < input.size();)
    {
        int is_find = buffer.rfind(input[counter]); // Если подстрока не найдена вернется string::npos (-1)
        while (is_find == -1 && counter < input.size())
        {
            codes.push_back({ 0,input[counter] }); // Подстрока, не встречавшиеся ранее всегда будет иметь 0,0
            buffer += input[counter];
            is_find = buffer.rfind(input[++counter]);
        }
        if (counter >= input.size()) // без данного условия(в том числе и в while) возможно кодировать только последовательности хотя бы с одним повторением
            return codes;
        string substr;
        do
        {
            substr += input[counter];
            is_find = buffer.rfind(substr + input[++counter]);
        } while (is_find != -1 && counter < input.size());
        is_find = buffer.rfind(substr);
        codes.push_back({ counter - is_find - (int)substr.size(), (int)substr.size()});
        buffer += substr;
    }
    return codes;
}

void show_code(vector<vector<int>> code)
{
    for (int counter = 0; counter < code.size(); counter++)
    {
        cout << '(' << code[counter][0] << ',';
        if (code[counter][0])
            cout << code[counter][1];
        else
            cout << (char)code[counter][1];
        cout << ")\n";
    }
}

string decode_lzss(vector<vector<int>> code)
{
    string decode;
    for (int counter = 0; counter < code.size(); counter++)
    {
        decode += decode.substr(decode.size() - code[counter][0], code[counter][1]);
        if (!code[counter][0])
            decode += code[counter][1];
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
    string input = "abcdef"; // Тут пишем то, что хотим кодировать
    if (input == decode_lzss(to_lzss(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_2()
{
    string input = "красная_краска"; // Тут пишем то, что хотим кодировать
    if (input == decode_lzss(to_lzss(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем то, что хотим кодировать
    if (input == decode_lzss(to_lzss(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_4()
{
    string input = "шла Саша по шоссе и сосала сушку"; // Тут пишем то, что хотим кодировать
    if (input == decode_lzss(to_lzss(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_5() // самый интересный тест
{
    string input = "абс\nабс"; // Тут пишем то, что хотим кодировать
    if (input == decode_lzss(to_lzss(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}