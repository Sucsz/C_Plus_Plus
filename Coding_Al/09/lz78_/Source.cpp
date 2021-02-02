// Работу выполнил студент 3го курса РГПУ им. А. И. Герцена Семыкин В.В.
// Время написания 1 час 10 минут
// Данная программа реализует алгоритмы кодирования и декодирования LZ78 
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
    vector<vector<int>> code = to_lz78(input);
    cout << "\nЗакодированное сообщение:\n";
    show_code(code);
    cout << "\nДекодированное закодированное сообщение:\n";
    string decode = decode_lz78(code);
    cout << "\t\t" << decode << "\n\n";
    if (input == decode)
        cout << "Исходное сообщение совпало c декодированным!\n\n";
    else
        cout << "Исходное сообщение не совпало c декодированным!\n\n";
    system("pause");
    return 0;
}

vector<vector<int>> to_lz78(string input)
{
    // буффера, в привычном плане алгоритма тут нет, в роли него выступает динамически расширяющийся словарь, а строка поступает посимвольно(буффер 1).
    vector<vector<int>> codes; // Кодовые диады, вместо символа будет код символа
    map<string, int> buffer; // просто строка не пройдет, так как теперь целым группам символов необходимо давать позицию, string - подстрока, int - позиция
    for (int counter = 0; counter < input.size(); counter++)
    {
        int is_find = buffer.count(string(1, input[counter])); // find не подходит, потому что find возвращает иттератор, нам подойдет count, count > 0 => is_find иначе !is_find
        while (!is_find && counter < input.size())
        {
            codes.push_back({ 0,input[counter] }); // Подстрока, не встречавшиеся ранее всегда будет иметь 0,0
            buffer.insert(make_pair(string(1, input[counter]), buffer.size() + 1)); // size() + 1, потому что нулевая позиция пуста
            is_find = buffer.count(string(1, input[++counter]));
        }
        if (counter >= input.size()) // без данного условия(в том числе и в while) возможно кодировать только последовательности хотя бы с одним повторением
            return codes;
        string substr;
        do
        {
            substr += input[counter];
            is_find = buffer.count(substr + input[++counter]); // также позволит добавить следующую букву, для этого нужен do while
        } while (is_find && counter < input.size());
        // нет необходимости искать подстроку в буффере, чтобы узгнать номер ее позиции, так как настоящий номер позиции лежит в паре подстрока-позиция
        codes.push_back({ buffer[substr], input[counter] });
        buffer.insert(make_pair(substr + input[counter], buffer.size() + 1));
    }
    return codes;
}

void show_code(vector<vector<int>> code)
{
    for (int counter = 0; counter < code.size(); counter++)
    {
        cout << '(' << code[counter][0] << ',' << (char)code[counter][1] << ")\n";
    }
}

string decode_lz78(vector<vector<int>> code)
{
    string decode;
    map<int, string> buffer;
    for (int counter = 0; counter < code.size(); counter++)
    {
        string substr;
        if (code[counter][0])
        {
            substr = buffer[code[counter][0]];
            decode += substr;
        }
        decode += code[counter][1];
        buffer[buffer.size() + 1] = substr + string(1, code[counter][1]);
    }
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
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_2()
{
    string input = "красная_краска"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_3()
{
    string input = "абракадабра"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_4()
{
    string input = "шла Саша по шоссе и сосала сушку"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}
void test_5() // самый интересный тест
{
    string input = "абс\nабс"; // Тут пишем то, что хотим кодировать
    if (input == decode_lz78(to_lz78(input)))
        cout << "TEST TRUE\n";
    else
        cout << "TEST FALSE\n";
}