// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 20 минут
// Данная программа реализует алгоритмы кодирования и декодирования стопкой книг 
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
    string alphabet;
    cout << "Введите алфавит кодирования одной строкой без разделителей\n\t\t";
    cin >> alphabet;
    cout << "\nЗакодированное сообщение:\n";
    string code = to_kidling_books(input, alphabet);
    cout << "Декодированное закодированное сообщение:\n";
    string decode = decode_kidling_books(code, alphabet);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode) cout << "Исходное сообщение совпало c декодированным!\n\n";
    else cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}

string to_kidling_books(string input, string alphabet)
{
    string code;
    for (int counter = 0; counter < input.size(); counter++)
    {
        for (int counter2 = 0; counter2 < alphabet.size(); counter2++)
        {
            if (input[counter] == alphabet[counter2])
            {
                code += (counter2 + 1) + '0'; // +1 т.к. в цикле мы идем от 0ля
                alphabet.insert(alphabet.begin(), alphabet[counter2]);
                alphabet.erase(counter2 + 1,1); // +1 т.к. после вставки в начало размерность увеличилась на 1цу
                break;
            }
        }
    }
    return code;
}

string decode_kidling_books(string code, string alphabet)
{
    string decode;
    for (int counter = 0; counter < code.size(); counter++)
    {
        decode += alphabet[(code[counter] - '0') - 1];
        alphabet.insert(alphabet.begin(), alphabet[(code[counter] - 1) - '0']);
        alphabet.erase((code[counter] - '0'), 1); // +1 т.к. после вставки в начало размерность увеличилась на 1цу
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
    string alphabet = "abc"; // Алфавит
    string code = to_kidling_books(input,alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_2()
{
    string input = "abcdabcddcba"; // Тут пишем, что хотим закодировать
    string alphabet = "abcd";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем, что хотим закодировать
    string alphabet = "абдкр";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_4()
{
    string input = "артист"; // Тут пишем, что хотим закодировать
    string alphabet = "аирст";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
void test_5()
{
    string input = "азбука"; // Тут пишем, что хотим закодировать
    string alphabet = "абзку";
    string code = to_kidling_books(input, alphabet);
    string decode = decode_kidling_books(code, alphabet);
    if (decode == input)
        cout << "\nTEST TRUE\n";
    else
        cout << "\nTEST FALSE\n";
}
