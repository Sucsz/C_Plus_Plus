// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 3 часа
// Данная программа реализует алгоритмы кодирования и декодирования LZ77 
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
    vector<vector<int> > code = to_lz77(input);
    cout << "\nЗакодированное сообщение:\n";
    show_code(code);
    cout << "\nДекодированное закодированное сообщение:\n";
    string decode = decode_lz77(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode)
        cout << "Исходное сообщение совпало c декодированным!\n\n";
    else
        cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}

vector<vector<int> > to_lz77(string input)
{
    // буффера, в привычном плане алгоритма тут нет, в роли него выступает динамически расширяющийся словарь, а строка поступает посимвольно(буффер 1).
    vector<vector<int> > codes; // Кодовые триады, вместо символа будет код символа
    string buffer;
    for (int counter = 0; counter < input.size(); counter++)
    {
        int is_find = buffer.rfind(input[counter]); // Если подстрока не найдена вернется string::npos (-1)
        while (is_find == -1 && counter < input.size())
        {
            codes.push_back({ 0,0,input[counter] }); // Подстрока, не встречавшиеся ранее всегда будет иметь 0,0
            buffer += input[counter];
            is_find = buffer.rfind(input[++counter]);
        }
        if (counter >= input.size()) // без данного условия(в том числе и в while) возможно кодировать только последовательности хотя бы с одним повторением
            return codes;
        string substr;
        do
        {
            substr += input[counter];
            is_find = buffer.rfind(substr + input[++counter]); // также позволит добавить следующую букву, для этого нужен do while
        } while (is_find != -1 && counter < input.size());
        is_find = buffer.rfind(substr);
        codes.push_back({ counter - is_find - (int)substr.size(), (int)substr.size(), input[counter]});
        buffer += substr + input[counter];
    }
    return codes;
}

void show_code (vector<vector<int> > code)
{
    for (int counter = 0; counter < code.size(); counter++)
    {
        cout << '(' << code[counter][0] << ',' << code[counter][1] << ',' << (char)code[counter][2] << ")\n";
    }
}

string decode_lz77(vector<vector<int> > code)
{
    string decode;
    for (int counter = 0; counter < code.size(); counter++)
    {
        decode += decode.substr(decode.size() - code[counter][0], code[counter][1]);
        decode += code[counter][2];
    }
    decode = decode.substr(0, decode.size());
    if (decode[decode.length() - 1] == '\0')
        return decode.substr(0, decode.length() - 1); // Иногда внезапно появляется ненужный \0
    else
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
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_2()
{
    string input = "красная_краска"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_4()
{
    string input = "шла Саша по шоссе и сосала сушку"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_5() // самый интересный тест
{
    string input = "абс\nабс"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz77(to_lz77(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}